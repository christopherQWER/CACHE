#include "Request.h"
#include <iostream>
#include <vector>

class Flow
{
public:
	Flow();
	~Flow();

	static void TraceFileFlow(std::vector<Request>& reqList, int count, std::string traceFile);
	static void StackDistancedFlow(std::vector<Request>& reqList, int count, int stack_dist);
};

