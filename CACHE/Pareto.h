//
// Created by cat on 9/25/16.
//
#pragma once
#include <random>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include "Utils/Utils.h"
#include "Utils/Types.h"
#ifndef CACHE_DISTRIBUTIONGENERATOR_H
#define CACHE_DISTRIBUTIONGENERATOR_H
typedef std::multimap<double, int>::iterator Multimap_itr;


class Pareto
{
public:
    Pareto(int location_param, double shape_param);
    ~Pareto();
    void Clear();

    /**
     * [Generates random value distributed by Pareto]
     *
     * @return                  [random value]
     **/
    double Generate();

    /**
     * [Calculates probability of density function]
     *
     * @param random_value      [random value Pareto distributed]
     *
     * @return                  [pdf value]
     **/
    double GetPDF(double random_value);

    /**
     * [Calculates cumulative distribution function]
     *
     * @param random_value      [random value Pareto distributed]
     *
     * @return                  [cdf value]
     **/
    double GetCDF(double random_value);

    /**
     * [Generates random value by distribution pdf]
     *
     * @return  [random value]
     **/
    double GetRandomByPDF(double probably);

private:
    /**
     * [parameter for indentation of distribution]
     **/
    int _location_param;

    /**
     * [parameter for shape of distribution]
     **/
    double _shape_param;
    std::map<double, Mmap_itr> rand_storage;
    std::multimap<double, double> probabilities;

    bool IsInStorage(double rand_value);
    void UpdateGeneratorState(double rand_num);
};


#endif //CACHE_DISTRIBUTIONGENERATOR_H
