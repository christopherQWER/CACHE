//
// Created by cat on 10/8/16.
//

#pragma once
#include <iostream>
#include <algorithm>
#include "../Requests/RequestGenerator.h"
#include "../Utils/Types.h"
#include "Flow.h"

class StackDistFlow : public Flow
{
public:
    StackDistFlow();
    StackDistFlow(int clients_count,
                  const std::string& input_pdf_path,
                  Timestamp time = 0);
    ~StackDistFlow();
    Request* GetRequest();
    Request* GetArtificialRequest(Asu asu, StackDist stack_dist);

private:
    int _common_request_num;
    int _curr_request_num;

    Timestamp _common_time;
    Timestamp _curr_request_time;

    int _app_count;
    std::string _input_pdf;
    std::deque<Request> _request_queue;

    static Asu GenerateAsu();
    static StackDist GenerateStackDistance();
    bool IsEndOfFlow();
};