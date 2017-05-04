//
// Created by cat on 10/8/16.
//

#pragma once
#include <iostream>
#include <algorithm>
#include "../Generators/Request.h"
#include "../Utils/Types.h"
#include "Flow.h"

typedef std::list<Lba>::iterator Buffer_itr;

class StackDistFlow : public Flow
{
public:

    StackDistFlow(const std::string& flow_name);
    StackDistFlow(const std::string& flow_name, StackDist stack_dist);
    ~StackDistFlow();

    void SetStackDistance(StackDist required);
    Request* GetRequest();

private:
    /// Needed stack distance
    StackDist _stack_dist_;
    ByteSize curr_buffer_size;
    std::list<Lba> _address_buffer;

    Request* GenerateForApp();
    bool IsInBuffer(Lba address);
    void MoveForward(int pos);
    void InsertToFront(Lba address);
    ByteSize GetBufferSize();
    Lba GetFirst();
};