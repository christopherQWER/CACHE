//
// Created by cat on 5/11/17.
//
#pragma once
#include "RandomValue.h"

class Exponential : public RandomValue {
private:
    std::exponential_distribution<double> distribution;

public:
    Exponential(double lambda);
    double GetRandom();
};
