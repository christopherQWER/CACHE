#include "Lru.h"
#include "Flow.h"
using namespace std;

#define DEBUG
#define CONSOLE CONSOLE_LOGGER
//#define FILE FILE_LOGGER
#define _1_GB_IN_BYTES_ 1073741824

int main()
{
    int req_counter = 0;
    HIT_RATE hit_rate = 0;
    STACK_DIST stack_dist = 0;
    list<Request> request_list;
    int request_size = 200;
    Lru cache = Lru(_1_GB_IN_BYTES_ / 2);
    Flow flow = Flow();

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    flow.StackDistancedFlow(request_list, request_size, 150);

    // Add requests to cache
    for (LIST_ITR it = request_list.begin(); it != request_list.end(); it++)
    {
#ifdef DEBUG
        pLogger->ShowRequestInfo(req_counter, it->_asu, it->_lba, it->_timestamp);
#endif
        cache.LRU(*it);
        req_counter++;
    }

    hit_rate = cache.CalculateHitRate();

#ifdef DEBUG
    pLogger->ShowHitRate(hit_rate);
#endif

    stack_dist = cache.CalculateStackDistance();

#ifdef DEBUG
    pLogger->ShowStackDistance(stack_dist);
    pLogger->EndLog();
#endif

    system("pause");
    return 0;
}