#include "TestStaticPartial.h"

#define TYPE LCONSOLE
using namespace std;


TestStaticPartial::TestStaticPartial()
{
}

TestStaticPartial::~TestStaticPartial()
{
}

void TestStaticPartial::SameRequests(int experiments_count, ByteSize cache_capasity)
{
    double hit_rate = 0;
    StackDist stack_dist = 1;
    Request *request;
    Logger *logger = Logger::CreateLogger(LCONSOLE);

    XmlClient client_1 = XmlClient(0, false);
    client_1.asu = 1;
    client_1.qos = 0.5;
    XmlClient client_2 = XmlClient(0, false);
    client_2.asu = 2;
    client_2.qos = 0.5;
    list<XmlClient> app_list;
    app_list.push_back(client_1);
    app_list.push_back(client_2);

    ClientsManager *manager = new ClientsManager(app_list);

    StaticPartial *cache = new StaticPartial(0.1, "//home//cat//Documents//CACHE//Results//PlotData", 60, 0);
    cache->CreateStorage(BY_QOS, manager->clients_map);

    Flow *flow /*= new StackDistFlow(2, "//home//cat//Documents//CACHE//Inputs//Flows//Same_Requests.txt", 60)*/;
    for (int i = 0; i < experiments_count; i++)
    {
        cache->Run(*manager, logger, flow, true);
    }
    manager->QosComparator(logger);

    if (hit_rate >= 0.995 && stack_dist >= 1)
    {
        cout << "Same requests: OK" << endl;
    }
    else
    {
        cout << "Same requests: FAILED" << endl;
    }
}


void TestStaticPartial::HalfPartSameRequests(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);

    double hit_rate = 0;
    StackDist stack_dist = experiments_count / 2 + 1;
    Request *request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow /*= StackDistFlow(1, _READY_PDF, 30)*/;

    for (int i = 0; i < experiments_count; i++)
    {
        request = flow.GetRequest();
        cache->AddToCache(*request);
    }

//    hit_rate = cache->CalculateHitRate();
//    stack_dist = cache->CalculateAvgStackDistance();

    if (hit_rate >= 0.49 && stack_dist >= experiments_count / 2)
    {
        cout << "Half part requests: OK" << endl;
    }
    else
    {
        cout << "Half part requests: FAILED" << endl;
    }
}


void TestStaticPartial::DifferentRequests(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);
    //pLogger->StartLog();

    double hit_rate = 0;
    StackDist stack_dist = experiments_count;
    Request *request;
    Lru *cache = new Lru(cache_capasity);
    StackDistFlow flow /*= StackDistFlow(1, _READY_PDF, 30)*/;

    for (int i = 0; i < experiments_count; i++)
    {
        request = flow.GetRequest();
        cache->AddToCache(*request);
    }

//    hit_rate = cache->CalculateHitRate();
//    stack_dist = cache->CalculateAvgStackDistance();

    if (hit_rate == 0 && stack_dist == -1)
    {
        cout << "Different requests: OK" << endl;
    }
    else
    {
        cout << "Different requests: FAILED" << endl;
    }
}

void TestStaticPartial::GetPDFFlow(int experiments_count, ByteSize cache_capasity)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);

    double hit_rate = 0;
    StackDist stack_dist = 0;
    string pdf_path = Utils::PathCombine(string(_READY_PDF), string("Uniform_PDF.txt"));
    //StackDistanceGen pdf_generator = StackDistanceGen(pdf_path);
    Request *request;
    Lru *cache = new Lru(cache_capasity);
    list<string> str_list;
    str_list.push_back( pdf_path);
    StackDistFlow flow = StackDistFlow(1, 40000, str_list, experiments_count);

    for (int i = 0; i < experiments_count; i++)
    {
        request = flow.GetRequest();
        cache->AddToCache(*request);
    }

//    hit_rate = cache->CalculateHitRate();
//    stack_dist = cache->CalculateAvgStackDistance();

    flow.SaveTestPdf();
}

void TestStaticPartial::MainTester()
{
    ByteSize cache_capasity = 1000;
    int request_number = 10000;

    // Initialize test environment
    //DifferentRequests(request_number, cache_capasity);
    //SameRequests(request_number, cache_capasity);
    //HalfPartSameRequests(request_number, cache_capasity);
    GetPDFFlow(request_number, cache_capasity);
}