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

		for each (Request request in parsed_buffer)
		{
			req_list.push_back(request);
			req_counter++;
		}
	}
}

void Flow::SameRequestsFlow(vector<Request>& reqList, int count)
{
	Request rq = Request();
	Request::GenerateRequest(rq);
	for (int i = 0; i < count; i++)
	{
		reqList.push_back(rq);
	}
}

void Flow::DifferentRequestsFlow(vector<Request>& reqList, int count)
{
	for (int i = 0; i < count; i++)
	{
		Request rq = Request();
		Request::GenerateRequest(rq);
		reqList.push_back(rq);
	}
}

void Flow::HalfPartSameRequestsFlow(vector<Request>& reqList, int count)
{
	for (int i = 0; i < count / 2; i++)
	{
		Request rq = Request();
		Request::GenerateRequest(rq);
		reqList.push_back(rq);
	}
	for (int i = 0; i < count / 2; i++)
	{
		reqList.push_back(reqList[i]);
	}
}