//
// Created by cat on 5/15/17.
//

#include "UniformReal.h"
using namespace std;

UniformReal::UniformReal(double min, double max)
{
    random_device rd;
    mt19937 gen(rd());
    distribution = uniform_real_distribution<double>(min, max);
}

double UniformReal::GetRandom()
{
    double uniform_number = 0;
    while (uniform_number == 0)
    {
        uniform_number = distribution(generator);
    }
    return uniform_number;
}
