//
// Created by cat on 12/4/16.
//
#pragma once
#include "../Caches/Lru.h"
#include "../Generators/Pareto.h"
#include "../Flows/Flow.h"
#include "../Flows/StackDistFlow.h"
#include "../Flows/TraceFileFlow.h"
#include "../Utils/TraceAnalyzer.h"
#define _1_GB_IN_BYTES_ 1073741824
#ifndef PROJECT_FILEFLOWTEST_H
#define PROJECT_FILEFLOWTEST_H


class SharedCache {
public:
    SharedCache();
    SharedCache(int request_number, ByteSize cache_size);
    ~SharedCache();
    void Clear();

    void TestStat(const std::string &file_name);
    void MainTester();

private:
    /**
     * [input parameter set number of experiments]
     */
    int t_experiments_number;
    HitRate t_hit_rate;
    StackDist t_stack_dist;
    Lru *t_cache;
    TraceFileFlow *t_flow;
    Logger *t_logger;

    void FileRequests(const std::string &file_name);
};


#endif //PROJECT_FILEFLOWTEST_H
