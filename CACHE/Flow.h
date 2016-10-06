//
// Created by cat on 9/25/16.
//
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Request.h"
#ifndef CACHE_FLOW_H
#define CACHE_FLOW_H

class Flow
{
public:
    Flow();
    ~Flow();

    void TraceFileFlow(std::list<Request>& output_flow, int count, std::string traceFile);
    void StackDistancedFlow(std::list<Request>& output_flow, int count, int stack_dist);

private:
    std::list<Request> _address_space;
};


#endif //CACHE_FLOW_H
