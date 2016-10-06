//
// Created by cat on 9/25/16.
//

#include <iostream>
#include <vector>
#include "../CACHE/Flow.h"
#include "../CACHE/Generator.h"
#include "../CACHE/Lru.h"
using namespace std;

void SameRequests_Test(int req_count)
{
    int req_counter = 0;
    HIT_RATE hit_rate = 0;
    STACK_DIST stack_dist = 0;
    list<Request> output_flow;
    int request_size = 200;
    Lru cache = Lru(_1_GB_IN_BYTES_ / 2);
    Flow flow = Flow();

    flow.StackDistancedFlow(output_flow, req_count, 0);

    for (LIST_ITR it = output_flow.begin(); it != output_flow.end(); it++)
    {
        cache.LRU(*it);
        req_counter++;
    }

    hit_rate = cache.CalculateHitRate();
    stack_dist = cache.CalculateStackDistance();

    if (hit_rate > 0.95 && stack_dist == 1)
    {
        cout << "Test for same requests: OK" << endl;
    }
    else
    {
        cout << "Test for same requests: FAILED" << endl;
    }
}

void HalfPartSameRequests_Test(int req_count)
{
    int req_counter = 0;
    HIT_RATE hit_rate = 0;
    STACK_DIST stack_dist = 0;
    list<Request> output_flow;
    int request_size = 200;
    Lru cache = Lru(_1_GB_IN_BYTES_ / 2);
    Flow flow = Flow();

    flow.StackDistancedFlow(output_flow, req_count, req_count / 2);

    for (LIST_ITR it = output_flow.begin(); it != output_flow.end(); it++)
    {
        cache.LRU(*it);
        req_counter++;
    }

    hit_rate = cache.CalculateHitRate();
    stack_dist = cache.CalculateStackDistance();

    if (hit_rate > 0.45 && stack_dist == 101)
    {
        cout << "Test for half part requests: OK" << endl;
    }
    else
    {
        cout << "Test for half part requests: FAILED" << endl;
    }
}

void DifferentRequests_Test(int req_count)
{
    int req_counter = 0;
    HIT_RATE hit_rate = 0;
    STACK_DIST stack_dist = 0;
    list<Request> output_flow;
    int request_size = 200;
    Lru cache = Lru(_1_GB_IN_BYTES_ / 2);
    Flow flow = Flow();

    flow.StackDistancedFlow(output_flow, req_count, req_count + 1);

    for (LIST_ITR it = output_flow.begin(); it != output_flow.end(); it++)
    {
        cache.LRU(*it);
        req_counter++;
    }

    hit_rate = cache.CalculateHitRate();
    stack_dist = cache.CalculateStackDistance();

    if (hit_rate == 0 && stack_dist == -1)
    {
        cout << "Test for different requests: OK" << endl;
    }
    else
    {
        cout << "Test for different requests: FAILED" << endl;
    }
}

void TraceFileRequests_Test(int req_count, string path_to_file)
{
    list<Request> output_flow;
    Flow flow = Flow();
    flow.TraceFileFlow(output_flow, req_count, path_to_file);
}

void Distribution_Test()
{
    int count_experiments = 1000000;
    int k = 10;
    double a = 2;
    vector<int> values;
    vector<int> new_values;
    Generator gen = Generator();

    gen.Pareto(values, count_experiments, k, a);
    gen.GetPDF(values, count_experiments, "/home/cat/Documents/CACHE/Tests/Results/PDF.txt");

    gen.GetRandomByPDF(new_values, count_experiments);
    gen.GetPDF(new_values, count_experiments, "/home/cat/Documents/CACHE/Tests/Results/PDF_test.txt");
}

int main ()
{
    int errorCode = 0;

    SameRequests_Test(200);
    HalfPartSameRequests_Test(200);
    DifferentRequests_Test(200);
    //TraceFileRequests_Test(200, "Stats//SPC-1//Financial2.spc");
    //Distribution_Test();


    system("pause");
    return 0;
}