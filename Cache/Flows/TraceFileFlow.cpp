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
}

Request* TraceFileFlow::GetRequest()
{
    string buffer = "";
    Request *request = new Request();

    if (_request_queue.empty())
    {
        if (getline(trace_file, buffer))
        {
            if (!RequestParser::ParseRequest(buffer, _request_queue))
            {
                return nullptr;
            }
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
    _current_time += request->_timestamp;
    return request;
}

bool TraceFileFlow::IsEndOfFlow()
{
    if (_specified_limit == TIME)
    {
        return ( (_current_time > _limit_value) || _is_eof  );
    }
    if (_specified_limit == REQUEST_NUMBER)
    {
        return ((_current_request_num > _limit_value) && _is_eof );
    }
}
