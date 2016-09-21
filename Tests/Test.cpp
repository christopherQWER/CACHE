#include <iostream>
#include <vector>
#include "../CACHE/Flow.h"
#include "../CACHE/DistributionGenerator.h"

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

void Distribution_Test()
{
	int count_experiments = 10000;
	int k = 10;
	double a = 2;
	int intervals = 100;
	vector<double> values;
	DistributionGenerator::Pareto(values, count_experiments, k, a);
	DistributionGenerator::ShowDistributionDensity(values, count_experiments, intervals);
}

int main()
{
	Distribution_Test();
	SameRequests_Test(200);
	HalfPartSameRequests_Test(200);
	DifferentRequests_Test(200);
	TraceFileRequests_Test(200, "Stats//SPC-1//Financial2.spc");

	system("pause");
	return 0;
}