//
// Created by cat on 10/8/16.
//

#include "TraceFileFlow.h"
using namespace std;

TraceFileFlow::TraceFileFlow(const string& file_name)
{
    file.open(file_name.c_str());
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

    if (request_queue.empty())
    {
        if (getline(file, buffer))
        {
            Request::ParseRequest(buffer, request_queue);
        }
    }
    *request = request_queue.front();
}