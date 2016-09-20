#include <iostream>
#include <vector>
#include "../CACHE/Flow.h"

using namespace std;

void SameRequests_Test(int req_count)
{
	vector<Request> requests;
	Flow::StackDistancedFlow(requests, req_count, 0);
}

void HalfPartSameRequests_Test(int req_count)
{
	vector<Request> requests;
	Flow::StackDistancedFlow(requests, req_count, req_count / 2);
}

void DifferentRequests_Test(int req_count)
{
	vector<Request> requests;
	Flow::StackDistancedFlow(requests, req_count, req_count + 1);
}

void TraceFileRequests_Test(int req_count, string path_to_file)
{
	vector<Request> requests;
	Flow::TraceFileFlow(requests, req_count, path_to_file);
}

int main()
{
	SameRequests_Test(200);
	HalfPartSameRequests_Test(200);
	DifferentRequests_Test(200);
	TraceFileRequests_Test(200, "Stats//SPC-1//Financial2.spc");
	system("pause");
	return 0;
}