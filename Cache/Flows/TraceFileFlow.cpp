//
// Created by cat on 10/8/16.
//

#include "TraceFileFlow.h"
using namespace std;


TraceFileFlow::TraceFileFlow(const std::string& source_path, Limit limit_type,
        ByteSize limit_value)
{
    _specified_limit = limit_type;
    _limit_value = limit_value;

    _current_request_num = 0;
    _current_time = 0;

    flow_dir_name = Utils::GetFileNameWithoutExt(source_path);
    trace_file.open(source_path.c_str());
    File = source_path;
    _is_eof = !(trace_file.is_open());
}

TraceFileFlow::~TraceFileFlow()
{
    trace_file.close();
    _request_queue.clear();
    _current_request_num = 0;
    _current_time = 0;
    _limit_value = 0;
    _is_eof = false;
}

Request* TraceFileFlow::GetRequest()
{
    string buffer = "";
    Request *request = new Request();

    if (_request_queue.empty())
    {
        if (getline(trace_file, buffer))
        {
            RequestParser::ParseRequest(buffer, _request_queue);
            _current_time = _request_queue.front()._timestamp;
        }
        else
        {
            _is_eof = true;
            return nullptr;
        }
    }

    *request = _request_queue.front();
    _request_queue.pop_front();
    _current_request_num++;
    return request;
}

bool TraceFileFlow::IsEndOfFlow()
{
    if (_specified_limit == TIME)
    {
        if ((_current_time > _limit_value) || _is_eof)
            return true;
    }
    else if (_specified_limit == REQUEST_NUMBER)
    {
        if ( (_current_request_num > _limit_value) || _is_eof)
            return true;
    }
}
