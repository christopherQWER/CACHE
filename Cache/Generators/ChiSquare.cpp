//
// Created by cat on 6/2/17.
//

#include "ChiSquare.h"
#include "../Utils/Utils.h"
using namespace std;

ChiSquare::ChiSquare(double parameter)
{
//    random_device rd;
//    mt19937 gen(rd());
    distribution = chi_squared_distribution<double>(parameter);
}

double ChiSquare::GetRandom()
{
    return distribution(generator_1);
}

double ChiSquare::GetPDF(int exp_number, const string& output_file)
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

double ChiSquare::GetCDF(int exp_number, const string& output_file)
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