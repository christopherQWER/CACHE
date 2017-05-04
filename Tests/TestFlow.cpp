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
    //pLogger->StartLog();

    double hit_rate = 0;
    StackDist stack_dist = 1;
    Request *request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow = StackDistFlow(<#initializer#>, stack_dist);

    for (int i = 0; i < experiments_count; i++)
    {
        flow.SetStackDistance(stack_dist);
        request = flow.GetRequest();
        cache->LRU(*request);
        delete request;
    }

    hit_rate = cache->CalculateHitRate();
    //pLogger->ShowHitRate(DEBUG, hit_rate);

    stack_dist = cache->CalculateAvgStackDistance();
    //pLogger->ShowStackDistance(DEBUG, stack_dist);

    if (hit_rate >= 0.995 && stack_dist >= 1)
    {
        cout << "Same requests: OK" << endl;
    }
    else
    {
        cout << "Same requests: FAILED" << endl;
    }
    FreeResources(pLogger, cache, request);
    //pLogger->EndLog();
}


void TestFlow::HalfPartSameRequests(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);
    //pLogger->StartLog();

    double hit_rate = 0;
    StackDist stack_dist = experiments_count / 2 + 1;
    Request *request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow = StackDistFlow(<#initializer#>, <#initializer#>);

    for (int i = 0; i < experiments_count; i++)
    {
        flow.SetStackDistance(stack_dist);
        request = flow.GetRequest();
        cache->LRU(*request);
        delete request;
    }

    hit_rate = cache->CalculateHitRate();
    //pLogger->ShowHitRate(DEBUG, hit_rate);

    stack_dist = cache->CalculateAvgStackDistance();
    //pLogger->ShowStackDistance(DEBUG, stack_dist);

    if (hit_rate >= 0.49 && stack_dist >= experiments_count / 2)
    {
        cout << "Half part requests: OK" << endl;
    }
    else
    {
        cout << "Half part requests: FAILED" << endl;
    }
    FreeResources(pLogger, cache, request);
    //pLogger->EndLog();
}


void TestFlow::DifferentRequests(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);
    //pLogger->StartLog();

    double hit_rate = 0;
    StackDist stack_dist = experiments_count;
    Request *request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow = StackDistFlow(<#initializer#>, <#initializer#>);

    for (int i = 0; i < experiments_count; i++)
    {
        flow.SetStackDistance(stack_dist);
        request = flow.GetRequest();
        cache->LRU(*request);
        delete request;
    }

    hit_rate = cache->CalculateHitRate();
    //pLogger->ShowHitRate(DEBUG, hit_rate);

    stack_dist = cache->CalculateAvgStackDistance();
    //pLogger->ShowStackDistance(DEBUG, stack_dist);

    if (hit_rate == 0 && stack_dist == -1)
    {
        cout << "Different requests: OK" << endl;
    }
    else
    {
        cout << "Different requests: FAILED" << endl;
    }
    FreeResources(pLogger, cache, request);
    //pLogger->EndLog();
}

void TestFlow::GetPDFFlow(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);
    //pLogger->StartLog();

    double hit_rate = 0;
    StackDist stack_dist = 0;
    string pdf_path = Utils::PathCombine(string(_READY_PDF), string("pdf.txt"));
    PdfFlow pdf_generator = PdfFlow(pdf_path);
    Request *request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow = StackDistFlow(<#initializer#>, <#initializer#>);

    for (int i = 0; i < experiments_count; i++)
    {
        StackDist st_dst = pdf_generator.GetRandomValue();
        flow.SetStackDistance(st_dst);
        request = flow.GetRequest();
        cache->LRU(*request);
    }

    hit_rate = cache->CalculateHitRate();
    //pLogger->ShowHitRate(DEBUG, hit_rate);

    stack_dist = cache->CalculateAvgStackDistance();
    //pLogger->ShowStackDistance(DEBUG, stack_dist);

    pdf_generator.GetPdf(Utils::PathCombine(string(_READY_PDF), string("pdf_test.txt")));
    FreeResources(pLogger, cache, request);
    //pLogger->EndLog();
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

void TestFlow::FreeResources(Logger* &pLogger, Lru* &cache, Request* &request)
{
//    if(request != NULL)
//    {
//        delete request;
//    }
//    if (cache != NULL)
//    {
//        delete cache;
//    }
//    if (pLogger != NULL)
//    {
//        delete pLogger;
//    }
}