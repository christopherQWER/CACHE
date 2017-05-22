//
// Created by cat on 10/8/16.
//

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include "Flow.h"
#include "../Requests/RequestParser.h"


class TraceFileFlow : public Flow
{
public:
    std::string File;

    TraceFileFlow(const std::string& source_path);
    ~TraceFileFlow();
    Request GetRequest();
    bool IsEndOfFlow();

private:
    bool _is_eof;
    std::deque<Request> _request_queue;
    std::ifstream trace_file;
};