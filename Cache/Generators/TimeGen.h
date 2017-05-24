//
// Created by cat on 5/18/17.
//
#pragma once
#include "Exponential.h"
#include "../Utils/Types.h"

class TimeGen : public RandomValue {
public:
    TimeGen();
    Timestamp GetRandom();
private:
    /// Time since begin of experiment
    Timestamp _beginning_time;
};
