//
// Created by cat on 5/17/17.
//

#include "UniformInt.h"
#include <map>
#include "../Utils/Utils.h"
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

void UniformInt::GetPDF(int exp_number, const string& output_file)
{
    map<int, int> number_probability;
    map<int, int>::iterator it;

    for (int i = 0; i < exp_number; ++i)
    {
        double rand = GetRandomValue();
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

void UniformInt::GetCDF(int exp_number, const string& output_file)
{
    map<int, int> number_probability;
    map<int, int>::iterator it;

    for (int i = 0; i < exp_number; ++i)
    {
        double rand = GetRandomValue();
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