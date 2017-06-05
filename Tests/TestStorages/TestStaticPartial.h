//
// Created by cat on 10/6/16.
//

#pragma once

#include "../../Cache/Storages/StaticPartial.h"
#include "../../Cache/Flows/StackDistFlow.h"
#include "../../Cache/Clients/ClientsManager.h"

class TestStaticPartial
{
public:
    TestStaticPartial();
    ~TestStaticPartial();

    void MainTester();

private:

    void SameRequests(int experiments_count, ByteSize cache_capasity);
    void DifferentRequests(int experiments_count, ByteSize cache_capasity);
    void HalfPartSameRequests(int experiments_count, ByteSize cache_capasity);
    void GetPDFFlow(int experiments_count, ByteSize cache_capasity);
};