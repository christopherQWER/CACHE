//
// Created by cat on 5/17/17.
//

#include "LbaGen.h"
using namespace std;

LbaGen::LbaGen()
{
    curr_buffer_size = 0;
}

Lba LbaGen::GetRandomValue(StackDist stack_dist, Lba low_address_bound)
{
    Lba lba = 0;
    if ( (stack_dist < curr_buffer_size) && (curr_buffer_size != 0))
    {
        MoveForward(stack_dist);
        lba = GetFirst();
    }
    else
    {
        lba = (Lba) (low_address_bound + stack_dist);
        while ( IsInBuffer(lba) )
        {
            lba++;
        }
        InsertToFront(lba);
    }
    return lba;
}

bool LbaGen::IsInBuffer(Lba address)
{
    return (find( std::begin(_address_buffer),
            std::end(_address_buffer),
            address) != std::end(_address_buffer));
}

void LbaGen::MoveForward(StackDist pos)
{
    AddressList::iterator it = _address_buffer.begin();
    advance(it, pos);
    Lba founded = *it;
    _address_buffer.erase(it);
    _address_buffer.push_front(founded);
}

ByteSize LbaGen::GetBufferSize()
{
    return curr_buffer_size;
}

Lba LbaGen::GetFirst()
{
    return _address_buffer.front();
}

void LbaGen::InsertToFront(Lba address)
{
    _address_buffer.push_front(address);
    curr_buffer_size++;
}