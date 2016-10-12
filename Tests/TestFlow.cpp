//
// Created by cat on 10/6/16.
//

#include "TestFlow.h"
#define CONSOLE CONSOLE_LOGGER
//#define DEBUG
//#define FILE FILE_LOGGER
using namespace std;

TestFlow::TestFlow()
{

}

TestFlow::TestFlow(int request_number, Byte_size cache_size)
{
    t_request_counter = 0;
    t_hit_rate = 0;
    t_request_number = request_number;
    t_cache = new Lru(cache_size);
}

void TestFlow::Clear()
{
    t_request_number = 0;
    t_request_counter = 0;
    t_hit_rate = 0;
    //delete t_cache;
}

TestFlow::~TestFlow()
{
}

void TestFlow::SameRequests()
{
    Request *request;
    StackDistFlow *fl = new StackDistFlow();
    fl->_stack_dist_ = 0;

    for (int i = 0; i < t_request_number; i++)
    {
        request = fl->GetRequest();
#ifdef DEBUG
        pLogger->ShowRequestInfo(req_counter, request->_asu, request->_lba, request->_timestamp);
#endif
        t_cache->LRU(*request);
        t_request_counter++;
    }

    t_hit_rate = t_cache->CalculateHitRate();
#ifdef DEBUG
    pLogger->ShowHitRate(hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();
#ifdef DEBUG
    pLogger->ShowStackDistance(stack_dist);
    pLogger->EndLog();
#endif

    if (t_hit_rate == 0.995 && t_stack_dist == 1)
    {
        cout << "Test for same requests: OK" << endl;
    }
    else
    {
        cout << "Test for same requests: FAILED" << endl;
    }
}


void TestFlow::HalfPartSameRequests()
{
    Request *request;
    StackDistFlow fl = StackDistFlow();
    fl._stack_dist_ = t_request_number / 2 - 1;

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    for (int i = 0; i < t_request_number; i++)
    {
        request = fl.GetRequest();
#ifdef DEBUG
        pLogger->ShowRequestInfo(req_counter, request->_asu, request->_lba, request->_timestamp);
#endif
        t_cache->LRU(*request);
        t_request_counter++;
    }

    t_hit_rate = t_cache->CalculateHitRate();
#ifdef DEBUG
    pLogger->ShowHitRate(hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();
#ifdef DEBUG
    pLogger->ShowStackDistance(stack_dist);
    pLogger->EndLog();
#endif

    if (t_hit_rate == 0.5 && t_stack_dist == 100)
    {
        cout << "Test for half part requests: OK" << endl;
    }
    else
    {
        cout << "Test for half part requests: FAILED" << endl;
    }
}


void TestFlow::DifferentRequests()
{
    Request *request;
    StackDistFlow fl = StackDistFlow();
    fl._stack_dist_ = t_request_number;

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    for (int i = 0; i < t_request_number; i++)
    {
        request = fl.GetRequest();

#ifdef DEBUG
        pLogger->ShowRequestInfo(req_counter, request->_asu, request->_lba, request->_timestamp);
#endif

        t_cache->LRU(*request);
        t_request_counter++;
    }

    t_hit_rate = t_cache->CalculateHitRate();

#ifdef DEBUG
    pLogger->ShowHitRate(hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();

#ifdef DEBUG
    pLogger->ShowStackDistance(stack_dist);
    pLogger->EndLog();
#endif

    if (t_hit_rate == 0 && t_stack_dist == -1)
    {
        cout << "Test for different requests: OK" << endl;
    }
    else
    {
        cout << "Test for different requests: FAILED" << endl;
    }
}


void TestFlow::FileRequests()
{
    Request *request;
    t_flow = new TraceFileFlow(_FINANCIAL_2_);

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    for (int i = 0; i < t_request_number; i++)
    {
        request = t_flow->GetRequest();

#ifdef DEBUG
        pLogger->ShowRequestInfo(req_counter, request->_asu, request->_lba, request->_timestamp);
#endif

        t_cache->LRU(*request);
        t_request_counter++;
    }

    t_hit_rate = t_cache->CalculateHitRate();

#ifdef DEBUG
    pLogger->ShowHitRate(hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();

#ifdef DEBUG
    pLogger->ShowStackDistance(stack_dist);
    pLogger->EndLog();
#endif
}

void TestFlow::MainTester()
{
    int errorCode = 0;
    Byte_size cache_capasity = _1_GB_IN_BYTES_ / 2;

    // Initialize test environment
    TestFlow tester = TestFlow(200, cache_capasity);
    tester.DifferentRequests();
    tester.Clear();

    tester = TestFlow(200, cache_capasity);
    tester.SameRequests();
    tester.Clear();

    tester = TestFlow(200, cache_capasity);
    tester.HalfPartSameRequests();

    tester = TestFlow(200, cache_capasity);
    tester.FileRequests();
    tester.Clear();
}
