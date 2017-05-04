//
// Created by cat on 10/8/16.
//

#include "TraceFileFlow.h"
using namespace std;

TraceFileFlow::TraceFileFlow(string flow_name)
        :Flow(flow_name)
{
    trace_file.open(flow_dir.c_str());
    _is_eof = trace_file.is_open();
}

TraceFileFlow::~TraceFileFlow()
{
    trace_file.close();
}

Request* TraceFileFlow::GetRequest()
{
    string buffer = "";
    Request *request = new Request();

    while (_request_queue.empty())
    {
        if (getline(trace_file, buffer))
        {
            Request::ParseRequest(buffer, _request_queue);
        }
        else
        {
            _is_eof = true;
            return nullptr;
        }
    }

    *request = _request_queue.front();
    _request_queue.pop_front();
    return request;
}