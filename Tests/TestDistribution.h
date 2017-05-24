//
// Created by cat on 10/9/16.
//

#pragma once
#include <vector>
#include <algorithm>
#include "../Cache/Utils/Utils.h"


class TestDistribution
{
public:
    TestDistribution();
    ~TestDistribution();

    int MainTester();

private:
    void GetPDFTest();
    void GetRandByPDFTest();
};