#include "TestFlow.h"
#define TYPE LCONSOLE
#define _1_GB_IN_BYTES_ 1073741824
using namespace std;


TestFlow::TestFlow()
{
}

TestFlow::~TestFlow()
{
}

void TestFlow::SameRequests(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);

    double hit_rate = 0;
    StackDist stack_dist = 1;
    Request request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow = StackDistFlow(1, _READY_PDF, 30);

    for (int i = 0; i < experiments_count; i++)
    {
        request = flow.GetRequest();
        cache->AddToCache(request);
    }

    hit_rate = cache->CalculateHitRate();
    stack_dist = cache->CalculateAvgStackDistance();

    if (hit_rate >= 0.995 && stack_dist >= 1)
    {
        cout << "Same requests: OK" << endl;
    }
    else
    {
        cout << "Same requests: FAILED" << endl;
    }
}


void TestFlow::HalfPartSameRequests(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);

    double hit_rate = 0;
    StackDist stack_dist = experiments_count / 2 + 1;
    Request request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow = StackDistFlow(1, _READY_PDF, 30);

    for (int i = 0; i < experiments_count; i++)
    {
        request = flow.GetRequest();
        cache->AddToCache(request);
    }

    hit_rate = cache->CalculateHitRate();
    stack_dist = cache->CalculateAvgStackDistance();

    if (hit_rate >= 0.49 && stack_dist >= experiments_count / 2)
    {
        cout << "Half part requests: OK" << endl;
    }
    else
    {
        cout << "Half part requests: FAILED" << endl;
    }
}


void TestFlow::DifferentRequests(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);
    //pLogger->StartLog();

    double hit_rate = 0;
    StackDist stack_dist = experiments_count;
    Request request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow = StackDistFlow(1, _READY_PDF, 30);

    for (int i = 0; i < experiments_count; i++)
    {
        request = flow.GetRequest();
        cache->AddToCache(request);
    }

    hit_rate = cache->CalculateHitRate();
    stack_dist = cache->CalculateAvgStackDistance();

    if (hit_rate == 0 && stack_dist == -1)
    {
        cout << "Different requests: OK" << endl;
    }
    else
    {
        cout << "Different requests: FAILED" << endl;
    }
}

void TestFlow::GetPDFFlow(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);

    double hit_rate = 0;
    StackDist stack_dist = 0;
    string pdf_path = Utils::PathCombine(string(_READY_PDF), string("pdf.txt"));
    StackDistanceGen pdf_generator = StackDistanceGen(pdf_path);
    Request request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow = StackDistFlow(1, _READY_PDF, 30);

    for (int i = 0; i < experiments_count; i++)
    {
        request = flow.GetRequest();
        cache->AddToCache(request);
    }

    hit_rate = cache->CalculateHitRate();
    stack_dist = cache->CalculateAvgStackDistance();

    pdf_generator.WritePairsToFile(Utils::PathCombine(string(_READY_PDF),
            string("pdf_test.txt")));
}

void TestFlow::MainTester()
{
    ByteSize cache_capasity = _1_GB_IN_BYTES_ / 2;
    int request_number = 400;

    // Initialize test environment
    DifferentRequests(request_number, cache_capasity);
    SameRequests(request_number, cache_capasity);
    HalfPartSameRequests(request_number, cache_capasity);
    GetPDFFlow(request_number, cache_capasity);
}