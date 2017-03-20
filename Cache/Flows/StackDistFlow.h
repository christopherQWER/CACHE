//
// Created by cat on 10/8/16.
//

#pragma once
#include <iostream>
#include <algorithm>

#include "../Generators/Request.h"
#include "../Utils/Types.h"
#include "Flow.h"

typedef std::list<Lba>::iterator buffer_itr;

class StackDistFlow : public Flow
{
public:
    /// [Needed stack distance]
    int _stack_dist_;

    StackDistFlow();
    ~StackDistFlow();

    ///
    /// \return [request generated with specified stack distance]
    Request* GetRequest();

private:
    ByteSize curr_buffer_size;
    std::list<Lba> _address_buffer;

    bool IsInBuffer(Lba address);
    void MoveForward(int pos);
    void InsertToFront(Lba address);
    ByteSize GetBufferSize();
    Lba GetFirst();
};