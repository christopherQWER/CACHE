#include "Request.h"
#include <iostream>
#include <vector>

class Flow
{
public:
	Flow();
	~Flow();

	static void TraceFileFlow(std::vector<Request>& reqList, int count, std::string traceFile);
	static void SameRequestsFlow(std::vector<Request>& reqList, int count);
	static void DifferentRequestsFlow(std::vector<Request>& reqList, int count);
	static void HalfPartSameRequestsFlow(std::vector<Request>& reqList, int count);

	static void StackDistancedFlow(std::vector<Request>& reqList, int count, int stack_dist);
};

