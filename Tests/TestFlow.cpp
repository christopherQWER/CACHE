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

TestFlow::TestFlow(int request_number, ByteSize cache_size)
{
    t_hit_rate = 0;
    t_experiments_count = request_number;
    t_cache = new Lru(cache_size);
    t_logger = Logger::CreateLogger(CONSOLE);
}

void TestFlow::Clear()
{
    t_experiments_count = 0;
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

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    for (int i = 0; i < t_experiments_count; i++)
    {
        request = fl->GetRequest();
#ifdef DEBUG
        pLogger->ShowRequestInfo(t_request_counter, request->_asu, request->_lba, request->_timestamp);
#endif
        t_cache->LRU(*request);
    }

    t_hit_rate = t_cache->CalculateHitRate();
#ifdef DEBUG
    pLogger->ShowHitRate(t_hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();
#ifdef DEBUG
    pLogger->ShowStackDistance(t_stack_dist);
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
    fl._stack_dist_ = t_experiments_count / 2 - 1;

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    for (int i = 0; i < t_experiments_count; i++)
    {
        request = fl.GetRequest();
#ifdef DEBUG
        pLogger->ShowRequestInfo(t_request_counter, request->_asu, request->_lba, request->_timestamp);
#endif
        t_cache->LRU(*request);
    }

    t_hit_rate = t_cache->CalculateHitRate();
#ifdef DEBUG
    pLogger->ShowHitRate(t_hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();
#ifdef DEBUG
    pLogger->ShowStackDistance(t_stack_dist);
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
    fl._stack_dist_ = t_experiments_count;

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    for (int i = 0; i < t_experiments_count; i++)
    {
        request = fl.GetRequest();

#ifdef DEBUG
        pLogger->ShowRequestInfo(t_request_counter, request->_asu, request->_lba, request->_timestamp);
#endif

        t_cache->LRU(*request);
    }

    t_hit_rate = t_cache->CalculateHitRate();

#ifdef DEBUG
    pLogger->ShowHitRate(t_hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();

#ifdef DEBUG
    pLogger->ShowStackDistance(t_stack_dist);
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

void TestFlow::PDFFlow()
{
    double rand_num = 0;
    double new_rand_num = 0;
    double int_part = 0;
    double fract_part = 0;
    double prob = 0;
    Request *request;
    Pareto gen = Pareto(10, 2);
    double experimental_stack_dist = 0;
    StackDistFlow *fl = new StackDistFlow();

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    // Inicialize map with rand values and pdfs (only unical values)
    // Inicialize vector with random values
    for (int i = 0; i < t_experiments_count; i++)
    {
        rand_num = gen.Generate();
        prob = gen.GetPDF(rand_num);

        new_rand_num = gen.GetRandomByPDF(prob);
        fract_part = modf(new_rand_num, &int_part);

        fl->_stack_dist_ = static_cast<int>(int_part);
        request = fl->GetRequest();

        experimental_stack_dist += static_cast<Lba>(int_part);

        t_cache->LRU(*request);
    }

    experimental_stack_dist /= t_experiments_count;

#ifdef DEBUG
    pLogger->ShowStackDistance(experimental_stack_dist);
#endif

    t_hit_rate = t_cache->CalculateHitRate();

#ifdef DEBUG
    pLogger->ShowHitRate(t_hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();

#ifdef DEBUG
    pLogger->ShowStackDistance(t_stack_dist);
    pLogger->EndLog();
#endif
}

void TestFlow::MainTester()
{
    int errorCode = 0;
    ByteSize cache_capasity = _1_GB_IN_BYTES_ / 2;

    // Initialize test environment
    TestFlow tester;
//    tester = TestFlow(200, cache_capasity);
//    tester.DifferentRequests();
//    tester.Clear();
//
//    tester = TestFlow(200, cache_capasity);
//    tester.SameRequests();
//    tester.Clear();
//
//    tester = TestFlow(200, cache_capasity);
//    tester.HalfPartSameRequests();
//    tester.Clear();

    tester = TestFlow(10000, cache_capasity);
    tester.PDFFlow();
    tester.Clear();
}