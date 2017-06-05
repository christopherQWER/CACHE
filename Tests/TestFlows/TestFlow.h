//
// Created by cat on 10/6/16.
//

#pragma once
#include "Caches/Lru.h"
#include "Flows/Flow.h"
//#include "Generators/StackDistanceGen.h"
#include "Flows/StackDistFlow.h"
#include "Utils/Paths.h"
#include "Loggers/Logger.h"
#include "Utils/Utils.h"

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
};