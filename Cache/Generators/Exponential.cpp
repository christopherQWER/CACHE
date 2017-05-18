//
// Created by cat on 5/11/17.
//

#include "Exponential.h"
using namespace std;

Exponential::Exponential(double lambda)
{
    random_device rd;
    mt19937 gen(rd());
    distribution = exponential_distribution<double>(lambda);
}

double Exponential::GetRandom()
{
    return distribution(generator);
}


