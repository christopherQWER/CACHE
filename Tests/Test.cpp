#include <iostream>
#include <vector>
#include "../CACHE/Flow.h"

using namespace std;

void SameRequests_Test(int req_count)
{
	vector<Request> requests;
	Flow::SameRequestsFlow(requests, req_count);
}

void HalfPartSameRequests_Test(int req_count)
{
	vector<Request> requests;
	Flow::HalfPartSameRequestsFlow(requests, req_count);
}

void DifferentRequests_Test(int req_count)
{
	vector<Request> requests;
	Flow::DifferentRequestsFlow(requests, req_count);
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