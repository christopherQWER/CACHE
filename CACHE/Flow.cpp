//
// Created by cat on 9/25/16.
//

#include "Flow.h"
using namespace std;


Flow::Flow()
{
}


Flow::~Flow()
{
}


void Flow::TraceFileFlow(vector<Request>& req_list, int count, string trace_file)
{
    string buffer = "";
    int req_counter = 0;
    ifstream infile(trace_file.c_str());
    while ((req_counter < count) && (getline(infile, buffer)))
    {
        // Turn string to REQUEST object's collection
        vector<Request> parsed_buffer;
        Request::ParseRequest(buffer, parsed_buffer);

        for (Request request : parsed_buffer)
        {
            req_list.push_back(request);
            req_counter++;
        }
    }
}

void Flow::StackDistancedFlow(vector<Request>& reqList, int count, int stack_dist)
{
    //Add first request
    Request rq = Request();
    Request::GenerateRequest(rq);
    reqList.push_back(rq);
    if (stack_dist < count)
    {
        for (int j = 1; j < stack_dist; j++)
        {
            rq = Request();
            Request::GenerateRequest(rq);
            reqList.push_back(rq);
        }

        for (int j = reqList.size(), i = 0; j < count; j++, i++)
        {
            Request tmp = reqList[i];
            tmp.SetCurrentTime();
            reqList.push_back(tmp);
        }
    }
    else
    {
        for (int j = 1; j < count; j++)
        {
            Request rq = Request();
            Request::GenerateRequest(rq);
            reqList.push_back(rq);
        }
    }
}