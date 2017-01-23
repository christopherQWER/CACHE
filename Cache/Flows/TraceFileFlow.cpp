//
// Created by cat on 10/8/16.
//

#include "TraceFileFlow.h"
using namespace std;

TraceFileFlow::TraceFileFlow(const string& file_name)
{
    file.open(file_name.c_str());
    _is_eof = file.is_open();
}

TraceFileFlow::TraceFileFlow()
{

}

TraceFileFlow::~TraceFileFlow()
{
    file.close();
}

Request* TraceFileFlow::GetRequest()
{
    string buffer = "";
    Request *request = new Request();

    while (_request_queue.empty())
    {
        if (getline(file, buffer))
        {
            Request::ParseRequest(buffer, _request_queue);
        }
        else
        {
            _is_eof = true;
            return nullptr;
        }
    }
//    if (!_request_queue.empty())
//    {
        *request = _request_queue.front();
        _request_queue.pop_front();
        return request;
//    }
    //return nullptr;
}

void TraceFileFlow::AnalyzeFlow()
{
    TraceAnalyzer* a = new TraceAnalyzer(File);
    a->GetStat();
    a->AppendToFile(File);
}
