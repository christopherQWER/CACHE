//
// Created by cat on 9/25/16.
//
#include "Request.h"
#include <iostream>
#include <vector>
#ifndef CACHE_FLOW_H
#define CACHE_FLOW_H


class Flow
{
public:
    Flow();
    ~Flow();

    static void TraceFileFlow(std::vector<Request>& reqList, int count, std::string traceFile);
    static void StackDistancedFlow(std::vector<Request>& reqList, int count, int stack_dist);
};


#endif //CACHE_FLOW_H
