//
// Created by cat on 10/6/16.
//

#pragma once
#include "../Cache/Caches/Lru.h"
#include "../Cache/Flows/Flow.h"
#include "Generators/StackDistanceGen.h"
#include "../Cache/Flows/StackDistFlow.h"
#include "../Cache/Utils/Paths.h"
#include "../Cache/Loggers/Logger.h"
#include "../Cache/Utils/Utils.h"

class TestFlow
{
public:
    TestFlow();
    ~TestFlow();

    void MainTester();

private:

    void SameRequests(int experiments_count, ByteSize cache_capasity);
    void DifferentRequests(int experiments_count, ByteSize cache_capasity);
    void HalfPartSameRequests(int experiments_count, ByteSize cache_capasity);
    void GetPDFFlow(int experiments_count, ByteSize cache_capasity);

    void FreeResources(Logger* &pLogger, Lru* &cache, Request &request);
};