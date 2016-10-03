//
// Created by cat on 9/25/16.
//
#pragma once
#include "Request.h"
#include <iostream>
#include <vector>
#include <list>
#ifndef CACHE_FLOW_H
#define CACHE_FLOW_H

#define LOW_ADDRESS_BOUND 5000
#define UP_ADDRESS_BOUND 500000

class Flow
{
public:
    Flow();
    ~Flow();

    static void TraceFileFlow(std::vector<Request>& reqList, int count, std::string traceFile);
    static void StackDistancedFlow(std::vector<Request>& reqList, int count, int stack_dist);
};


#endif //CACHE_FLOW_H
