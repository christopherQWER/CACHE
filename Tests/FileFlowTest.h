//
// Created by cat on 12/4/16.
//
#pragma once
#include "../Cache/Caches/Lru.h"
#include "../Cache/Generators/Pareto.h"
#include "../Cache/Flows/Flow.h"
#include "../Cache/Flows/StackDistFlow.h"
#include "../Cache/Flows/TraceFileFlow.h"
#include "Paths.h"
#include "TraceAnalyzer.h"
#define _1_GB_IN_BYTES_ 1073741824
#ifndef PROJECT_FILEFLOWTEST_H
#define PROJECT_FILEFLOWTEST_H


class FileFlowTest {
public:
    FileFlowTest();
    FileFlowTest(int request_number, ByteSize cache_size);
    ~FileFlowTest();
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
