//
// Created by cat on 5/15/17.
//
#include <map>
#include "UniformReal.h"
#include "../Utils/Utils.h"
using namespace std;

UniformReal::UniformReal(double min, double max)
{
//    random_device rd;
//    mt19937 gen(rd());
    distribution = uniform_real_distribution<double>(min, max);
}

double UniformReal::GetRandom()
{
//    double uniform_number = 0;
//    while (uniform_number == 0)
//    {
//        uniform_number = distribution(generator);
//    }
//    return uniform_number;

    return distribution(generator);
}

double UniformReal::GetPDF(int exp_number, const string& output_file)
{
    map<int, int> number_probability;
    map<int, int>::iterator it;

    for (int i = 0; i < exp_number; ++i)
    {
        double rand = GetRandom();
        it = number_probability.find(static_cast<int>(rand));
        if (it == number_probability.end())
        {
            number_probability.insert(pair<int, int>(rand, 1));
        }
        else
        {
            it->second++;
        }
    }

    for (map<int, int>::iterator it = number_probability.begin();
         it != number_probability.end(); ++it)
    {
        double probably = static_cast<float>(it->second) / static_cast<float>(exp_number);
        Utils::AppendToFile(output_file, it->first, probably);
    }
}

double UniformReal::GetCDF(int exp_number, const string& output_file)
{
    map<int, int> number_probability;
    map<int, int>::iterator it;

    for (int i = 0; i < exp_number; ++i)
    {
        double rand = GetRandom();
        it = number_probability.find(static_cast<int>(rand));
        if (it == number_probability.end())
        {
            number_probability.insert(pair<int, int>(rand, 1));
        }
        else
        {
            it->second++;
        }
    }

    double common_val = 0;
    for (map<int, int>::iterator it = number_probability.begin();
         it != number_probability.end(); ++it)
    {
        double probably = static_cast<float>(it->second) / static_cast<float>(exp_number);
        common_val += probably;
        Utils::AppendToFile(output_file, it->first, common_val);
    }
}