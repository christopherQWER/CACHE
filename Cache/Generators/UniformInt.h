//
// Created by cat on 5/17/17.
//

#pragma once
#include "RandomValue.h"

class UniformInt : public RandomValue {
private:
    std::uniform_int_distribution<int> distribution;

public:

    UniformInt(int min, int max);
    int GetRandomValue();
};