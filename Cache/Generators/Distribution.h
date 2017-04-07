//
// Created by cat on 11/19/16.
//
#pragma once
#include <random>
#include <iostream>

class Distribution {
public:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
    Distribution();
    double GetRandom();
    double GetPDF(double random_value);
    double GetCDF(double random_value);
    double GetRandomByPDF(double probably);
};