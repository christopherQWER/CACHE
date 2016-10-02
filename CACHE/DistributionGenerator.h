//
// Created by cat on 9/25/16.
//
#pragma once
#include <random>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include "Utils.h"
#ifndef CACHE_DISTRIBUTIONGENERATOR_H
#define CACHE_DISTRIBUTIONGENERATOR_H

typedef std::map<int, double>::iterator MAP_ITR;
typedef std::multimap<double, int>::const_iterator MULTIMAP_ITR;


class DistributionGenerator
{
public:
    std::map<int, double> _stack_dist;
    std::multimap<double, int> _probabilities;


    DistributionGenerator();
    ~DistributionGenerator();

    /*
        k - is a location parameter (specifies minimal possible value)
        a - is a shape parameter (defines the tail of the distribution)
    */
    void Pareto(std::vector<int>& values, int value_count, int k, double a);
    void GetPDF(std::vector<int>& values, int value_count, std::string output_file);
    void GetRandomByPDF(std::vector<int>& values, int value_count);
private:
    bool IsInMap(int value);
};


#endif //CACHE_DISTRIBUTIONGENERATOR_H
