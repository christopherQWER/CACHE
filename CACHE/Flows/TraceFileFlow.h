//
// Created by cat on 10/8/16.
//
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include "Flow.h"
#include "../Generators/Request.h"
#ifndef CACHE_TRACEFILEFLOW_H
#define CACHE_TRACEFILEFLOW_H

class TraceFileFlow : public Flow
{
public:
    std::string File;

    TraceFileFlow();
    TraceFileFlow(const std::string& file_name);
    ~TraceFileFlow();
    Request* GetRequest();

private:
    std::deque<Request> request_queue;
    std::ifstream file;
};


#endif //CACHE_TRACEFILEFLOW_H
