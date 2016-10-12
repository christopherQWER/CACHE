//
// Created by cat on 10/8/16.
//

#pragma once

#include "Request.h"
#include "Flow.h"
#ifndef CACHE_STACKDISTFLOW_H
#define CACHE_STACKDISTFLOW_H


class StackDistFlow : public Flow
{
public:
    int _stack_dist_;

    StackDistFlow();
    ~StackDistFlow();
    Request* GetRequest();
private:
    std::list<Request> _address_space;
};


#endif //CACHE_STACKDISTFLOW_H
