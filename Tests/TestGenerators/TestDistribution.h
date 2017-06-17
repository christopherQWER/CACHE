//
// Created by cat on 10/9/16.
//

#pragma once
#include <vector>
#include <algorithm>
#include "Utils/Utils.h"


class TestDistribution
{
public:
    TestDistribution();
    ~TestDistribution();

    int MainTester();

private:
    void GetCDFTest();
    void GetPDFTest();
    void GetRandByPDFTest();
};