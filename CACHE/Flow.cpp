//
// Created by cat on 9/25/16.
//

#include "Flow.h"
using namespace std;
/* Trace log paths */
std::string financial_2 = "Stats//SPC-1//Financial2.spc";
std::string web_search_1 = "Stats//WebSearch//WebSearch1.spc";

Flow::Flow()
{
    for (LBA i = LOW_ADDRESS_BOUND; i < UP_ADDRESS_BOUND; i++)
    {
        Request rq = Request();
        rq._asu = Request::GetRandomAsu();
        rq._lba = i;
        rq._opcode = Request::GetReadOpCode();
        rq._size = _CELL_SIZE_;
        rq._timestamp = Request::GetCurrentTime();
        _address_space.push_back(rq);
    }
}


Flow::~Flow()
{
}


void Flow::TraceFileFlow(list<Request>& output_flow, int count, string trace_file)
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
            output_flow.push_back(request);
            req_counter++;
        }
    }
}

void Flow::StackDistancedFlow(list<Request>& output_flow, int required_count, int stack_dist)
{
    LIST_ITR it_begin = _address_space.begin();
    LIST_ITR it_current;

    for (int i = 0; i < required_count; i++)
    {
        it_current = next(it_begin, stack_dist);
        (*it_current)._timestamp = Request::GetCurrentTime();
        output_flow.push_back(*it_current);
        _address_space.erase(it_current);
        _address_space.push_front(*it_current);
        it_begin = _address_space.begin();
    }
}