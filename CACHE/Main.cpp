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
	vector<Request> requests;
	Lru cache = Lru(_1_GB_IN_BYTES_ / 2);

#ifdef DEBUG
	ConsoleLogger::StartLog();
#endif

	Flow::HalfPartSameRequestsFlow(requests, 200);


	// Add requests to cache
	for each (Request request in requests)
	{
#ifdef DEBUG
		ConsoleLogger::ShowRequestInfo(req_counter, request._asu, request._lba);
#endif
		cache.LRU(request);
		req_counter++;
	}

	double hit_rate = cache.CalculateHitRate();
	unsigned long long stack_dist = cache.CalculateStackDistance();
	ConsoleLogger::ShowHitRate(hit_rate);

#ifdef DEBUG
	ConsoleLogger::EndLog();
#endif
	system("pause");
	return 0;
}