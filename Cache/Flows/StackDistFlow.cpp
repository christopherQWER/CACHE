//
// Created by cat on 10/8/16.
//

#include "StackDistFlow.h"
using namespace std;

StackDistFlow::StackDistFlow(const string& flow_name)
        :Flow(flow_name)
{
    curr_buffer_size = 0;
    _stack_dist_ = 0;
    _address_buffer = list<Lba>();
}

StackDistFlow::StackDistFlow(const string& flow_name, StackDist stack_dist)
        :Flow(flow_name)
{
    StackDistFlow(flow_name);
    _stack_dist_ = stack_dist;
}

StackDistFlow::~StackDistFlow()
{
    _address_buffer.clear();
    _stack_dist_ = 0;
    curr_buffer_size = 0;
}

Request *StackDistFlow::GetRequest()
{
    return GenerateForApp();
}

Request* StackDistFlow::GenerateForApp()
{
    Request *request = new Request();
    Request::GenerateRequest(*request);
    Lba needed_lba = 0;
    //int size = GetBufferSize();

    if ( (_stack_dist_ < curr_buffer_size) && (curr_buffer_size != 0))
    {
        MoveForward(_stack_dist_);
        request->_lba = GetFirst();
    }
    else
    {
        needed_lba = (Lba) (LOW_ADDRESS_BOUND + _stack_dist_);
        while (IsInBuffer(needed_lba))
        {
            needed_lba++;
        }
        InsertToFront(needed_lba);
        request->_lba = needed_lba;
    }
    return request;
}

bool StackDistFlow::IsInBuffer(Lba address)
{
    return (find( std::begin(_address_buffer),
                  std::end(_address_buffer),
                  address) != std::end(_address_buffer));
}

void StackDistFlow::MoveForward(int pos)
{
    Buffer_itr it = _address_buffer.begin();
    advance(it, pos);
    Lba founded = *it;
    _address_buffer.erase(it);
    _address_buffer.push_front(founded);
}

ByteSize StackDistFlow::GetBufferSize()
{
    //return (int) _address_buffer.size();
    return curr_buffer_size;
}

Lba StackDistFlow::GetFirst()
{
    Lba address = _address_buffer.front();
    return address;
}

void StackDistFlow::InsertToFront(Lba address)
{
    _address_buffer.push_front(address);
    curr_buffer_size++;
}

void StackDistFlow::SetStackDistance(StackDist required)
{
    _stack_dist_ = required;
}
