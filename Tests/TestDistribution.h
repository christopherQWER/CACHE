//
// Created by cat on 10/9/16.
//

#pragma once
#include <vector>
#include <algorithm>
#include "../CACHE/Generators/Pareto.h"
#ifndef TESTS_TESTDISTRIBUTION_H
#define TESTS_TESTDISTRIBUTION_H


class TestDistribution
{
public:
    TestDistribution();
    ~TestDistribution();

    int MainTester();

private:
    void PDFTest();
    void GeneratingRandomTest();
};


#endif //TESTS_TESTDISTRIBUTION_H