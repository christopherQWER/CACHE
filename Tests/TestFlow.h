//
// Created by cat on 10/6/16.
//

#pragma once
#include "../CACHE/Caches/Lru.h"
#include "../CACHE/Generators/Pareto.h"
#include "../CACHE/Flows/Flow.h"
#include "../CACHE/Flows/StackDistFlow.h"
#include "../CACHE/Flows/TraceFileFlow.h"
#include "Paths.h"
#ifndef TESTS_TESTFLOW_H
#define TESTS_TESTFLOW_H
#define _1_GB_IN_BYTES_ 1073741824

class TestFlow
{
public:
    TestFlow();
    TestFlow(int request_number, ByteSize cache_size);
    ~TestFlow();
    void Clear();

    void MainTester();

private:
    /**
     * [input parameter set number of experiments]
     */
    int t_experiments_count;
    HitRate t_hit_rate;
    StackDist t_stack_dist;
    Lru *t_cache;
    Flow *t_flow;
    Logger *t_logger;

    void SameRequests();
    void DifferentRequests();
    void HalfPartSameRequests();
    void PDFFlow();
};


#endif //TESTS_TESTFLOW_H
