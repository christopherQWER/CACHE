//
// Created by cat on 9/25/16.
//

#include "Flow.h"
#include "Cache.h"

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

void Flow::StackDistancedFlow(vector<Request>& reqList, int required_count, int stack_dist)
{
    //Add first request
    list<Request> address_list;
    for (LBA i = LOW_ADDRESS_BOUND; i < UP_ADDRESS_BOUND; i++)
    {
        Request rq = Request();
        rq._asu = Request::GetRandomAsu();
        rq._lba = i;
        rq._opcode = Request::GetReadOpCode();
        rq._size = _CELL_SIZE_;
        address_list.push_back(rq);
    }

    LIST_ITR it_begin = address_list.begin();
    LIST_ITR it_end = address_list.end();
    LIST_ITR it_current = address_list.begin();
    for (int i = 0; i < required_count; i++)
    {
        //TODO: add to output massive
        it_current = next(it_begin, stack_dist);
    }
}