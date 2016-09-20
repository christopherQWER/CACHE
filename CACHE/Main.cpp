#include <ctime>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <sys/stat.h>
#include "Lru.h"
#include "ConsoleLogger.h"
#include "Flow.h"
using namespace std;

#define DEBUG
#define _1_GB_IN_BYTES_ 1073741824

/* Trace log paths */
string financial_2 = "Stats//SPC-1//Financial2.spc";
string web_search_1 = "Stats//WebSearch//WebSearch1.spc";

int main()
{
	int req_counter = 0;
	double hit_rate = 0;
	unsigned long long stack_dist = 0;
	vector<Request> requests;
	Lru cache = Lru(_1_GB_IN_BYTES_ / 2);

#ifdef DEBUG
	ConsoleLogger::StartLog();
#endif

	Flow::StackDistancedFlow(requests, 200, 0);


	// Add requests to cache
	for each (Request request in requests)
	{
#ifdef DEBUG
		ConsoleLogger::ShowRequestInfo(req_counter, request._asu, request._lba);
#endif
		cache.LRU(request);
		req_counter++;
	}

	hit_rate = cache.CalculateHitRate();
	ConsoleLogger::ShowHitRate(hit_rate);

	stack_dist = cache.CalculateStackDistance();
	ConsoleLogger::ShowStackDistance(stack_dist);

#ifdef DEBUG
	ConsoleLogger::EndLog();
#endif
	system("pause");
	return 0;
}