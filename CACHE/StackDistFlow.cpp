//
// Created by cat on 10/8/16.
//

#include "StackDistFlow.h"
using namespace std;

StackDistFlow::StackDistFlow()
{

}

StackDistFlow::~StackDistFlow()
{
    _address_space.clear();
}

Request *StackDistFlow::GetRequest()
{
    Request *request = new Request();
    if (_address_space.size() <= _stack_dist_)
    {
        Request::GenerateRequest(*request);
        request->_lba = (Lba) (LOW_ADDRESS_BOUND + _stack_dist_ + _address_space.size());
        _address_space.push_front(*request);
    }
    else if (_address_space.size() > _stack_dist_)
    {
        list_itr it_begin = _address_space.begin();
        list_itr it_current = next(it_begin, _stack_dist_);
        *request = *it_current;
        request->GetCurrentTime();
        _address_space.erase(it_current);
        _address_space.push_front(*request);
    }
    return request;
}