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
#include "../Loggers/Logger.h"
#include "../Utils/Utils.h"
#include "../Utils/TraceAnalyzer.h"
#ifndef CACHE_TRACEFILEFLOW_H
#define CACHE_TRACEFILEFLOW_H

class TraceFileFlow : public Flow
{
public:
    std::string File;
    bool _is_eof;

    TraceFileFlow();
    TraceFileFlow(const std::string& file_name);
    ~TraceFileFlow();
    Request* GetRequest();
    void AnalyzeFlow();

private:
    std::deque<Request> _request_queue;
    std::ifstream file;
};


#endif //CACHE_TRACEFILEFLOW_H
