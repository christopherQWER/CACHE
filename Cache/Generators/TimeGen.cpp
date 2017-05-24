//
// Created by cat on 5/18/17.
//
#include "TimeGen.h"
Exponential exp_gen = Exponential(3.5);
using namespace std;

TimeGen::TimeGen()
{
    _beginning_time = 0;
}

Timestamp TimeGen::GetRandom()
{
    _beginning_time += exp_gen.GetRandom();
    return _beginning_time;
}


