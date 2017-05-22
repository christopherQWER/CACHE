//
// Created by cat on 5/17/17.
//

#include "UniformInt.h"
using namespace std;

UniformInt::UniformInt(int min, int max)
{
    random_device rd;
    mt19937 gen(rd());
    distribution = uniform_int_distribution<int>(min, max);
}

int UniformInt::GetRandomValue()
{
    return distribution(generator);
}
