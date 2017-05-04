//
// Created by cat on 10/8/16.
//

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <deque>

#include "Flow.h"
#include "../Generators/Request.h"


class TraceFileFlow : public Flow
{
public:
    std::string File;
    bool _is_eof;

    TraceFileFlow(std::string flow_dir);
    ~TraceFileFlow();
    Request* GetRequest();

private:
    std::deque<Request> _request_queue;
    std::ifstream trace_file;
};