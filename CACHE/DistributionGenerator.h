//
// Created by cat on 9/25/16.
//
#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#ifndef CACHE_DISTRIBUTIONGENERATOR_H
#define CACHE_DISTRIBUTIONGENERATOR_H


class DistributionGenerator
{
public:
    DistributionGenerator();
    ~DistributionGenerator();

    /*
        k - is a location parameter (specifies minimal possible value)
        a - is a shape parameter (defines the tail of the distribution)
    */
    static void Pareto(std::vector<double>& values, int value_count, int k, double a);
    static void ShowDistributionDensity(std::vector<double>& values, int value_count, int interval_count);
};


#endif //CACHE_DISTRIBUTIONGENERATOR_H
