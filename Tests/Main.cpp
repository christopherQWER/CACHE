//
// Created by cat on 9/25/16.
//

#include <iostream>
#include <vector>
#include "../CACHE/Flow.h"
#include "../CACHE/DistributionGenerator.h"
using namespace std;

void SameRequests_Test(int req_count)
{
    vector<Request> requests;
    Flow::StackDistancedFlow(requests, req_count, 0);
}

void HalfPartSameRequests_Test(int req_count)
{
    vector<Request> requests;
    Flow::StackDistancedFlow(requests, req_count, req_count / 2);
}

void DifferentRequests_Test(int req_count)
{
    vector<Request> requests;
    Flow::StackDistancedFlow(requests, req_count, req_count + 1);
}

void TraceFileRequests_Test(int req_count, string path_to_file)
{
    vector<Request> requests;
    Flow::TraceFileFlow(requests, req_count, path_to_file);
}

void Distribution_Test()
{
    int count_experiments = 1000000;
    int k = 10;
    double a = 2;
    vector<int> values;
    vector<int> new_values;
    DistributionGenerator gen = DistributionGenerator();

    gen.Pareto(values, count_experiments, k, a);
    gen.GetPDF(values, count_experiments, "/home/cat/Documents/CACHE/Tests/Results/PDF.txt");

    gen.GetRandomByPDF(new_values, count_experiments);
    gen.GetPDF(new_values, count_experiments, "/home/cat/Documents/CACHE/Tests/Results/PDF_test.txt");
}

int main ()
{
    int errorCode = 0;

//    SameRequests_Test(200);
//    HalfPartSameRequests_Test(200);
//    DifferentRequests_Test(200);
//    TraceFileRequests_Test(200, "Stats//SPC-1//Financial2.spc");
    Distribution_Test();


    system("pause");
    return 0;
}