//
// Created by cat on 5/15/17.
//

#pragma once
#include "RandomValue.h"

class UniformReal : public RandomValue
{
private:
    std::uniform_real_distribution<double> distribution;

public:
    UniformReal(double min, double max);
    double GetRandom();
};