//
// Created by cat on 10/8/16.
//

#pragma once

#include <algorithm>
#include "../Generators/Request.h"
#include "Flow.h"
#ifndef CACHE_STACKDISTFLOW_H
#define CACHE_STACKDISTFLOW_H
typedef std::list<Lba>::iterator buffer_itr;


class StackDistFlow : public Flow
{
public:
    /**
     *
     */
    int _stack_dist_;

    StackDistFlow();
    ~StackDistFlow();

    /**
     *
     * @return [request generated with specified stack distance]
     */
    Request* GetRequest();
private:
    std::list<Lba> _address_buffer;
    bool IsInBuffer(Lba address);
    void MoveForward(int pos);
    void InsertToFront(Lba address);
    int GetBufferSize();
    Lba GetFirst();
};


#endif //CACHE_STACKDISTFLOW_H
