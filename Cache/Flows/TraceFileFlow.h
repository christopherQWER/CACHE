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

    TraceFileFlow(const std::string& source_path, Limit limit_type,
            ByteSize limit_value);
    ~TraceFileFlow();
    Request* GetRequest();
    bool IsEndOfFlow();

private:
    bool _is_eof;
    Limit _specified_limit;
    ByteSize _limit_value;

    Timestamp _current_time;
    ByteSize _current_request_num;

    std::deque<Request> _request_queue;
    std::ifstream trace_file;
};