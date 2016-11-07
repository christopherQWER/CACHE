//
// Created by cat on 10/6/16.
//

#pragma once
#include "../CACHE/Caches/Lru.h"

#include "../CACHE/Generators/Pareto.h"

#include "../CACHE/Flows/Flow.h"
#include "../CACHE/Flows/StackDistFlow.h"
#include "../CACHE/Flows/TraceFileFlow.h"
#ifndef TESTS_TESTFLOW_H
#define TESTS_TESTFLOW_H
#define _1_GB_IN_BYTES_ 1073741824

/* Trace log paths */
#define _FINANCIAL_2_ "Stats//SPC-1//Financial2.spc"
#define _WEB_SEARCH_1_ "Stats//WebSearch//WebSearch1.spc"

enum FlowType{STACK_DIST_FLOW = 0, FILE_FLOW};

class TestFlow
{
public:
    TestFlow();
    TestFlow(int request_number, Byte_size cache_size);
    ~TestFlow();
    void Clear();

    void MainTester();

private:
    int t_request_number;
    int t_request_counter;
    Hit_rate t_hit_rate;
    Stack_dist t_stack_dist;
    Lru *t_cache;
    Flow *t_flow;
    Logger *t_logger;

    void SameRequests();
    void DifferentRequests();
    void HalfPartSameRequests();
    void FileRequests();
    void PDFFlow();
};


#endif //TESTS_TESTFLOW_H
