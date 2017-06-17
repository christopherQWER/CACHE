//
// Created by cat on 10/8/16.
//

#pragma once
#include <iostream>
#include <deque>
#include <algorithm>
#include "../Requests/RequestGenerator.h"
#include "../Utils/Types.h"
#include "Flow.h"


class StackDistFlow : public Flow
{
public:
    ByteSize _common_request_num;
    StackDistFlow();
    StackDistFlow(Asu asu,
                  Lba low_address,
                  const std::list<std::string>& input_pdf_paths,
                  ByteSize limit_value,
                  double switcher = 0);

    ~StackDistFlow();
    Request* GetRequest();
    void SaveTestPdf();

private:

    ByteSize _curr_request_num;

    StackDistanceGen *dist_gen;
    UniformInt *uni_int_asu;
    RequestGenerator* gen;

    int counter;
    Asu _client_asu;
    Lba _low_address_bound;

    Limit _specified_limit;

    Timestamp _common_time;
    Timestamp _curr_request_time;

    /// This parameter used when you want get mixed logs from different generators.
    /// It shows when you must switch on the different source of requests.
    double _switcher;

    std::deque<Request> _request_queue;

    int _app_count;

    //Asu GenerateAsu();
    StackDist GenerateStackDistance();

    Request* ReqNumberBasedGeneration();

    bool IsEndOfFlow();
};