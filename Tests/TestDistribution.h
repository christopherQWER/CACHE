//
// Created by cat on 10/9/16.
//

#pragma once
#include <vector>
#include <algorithm>
#include "../Cache/Generators/Pareto.h"
#include "../Cache/Utils/Utils.h"
#ifndef TESTS_TESTDISTRIBUTION_H
#define TESTS_TESTDISTRIBUTION_H


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


#endif //TESTS_TESTDISTRIBUTION_H
