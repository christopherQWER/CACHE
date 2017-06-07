//
// Created by cat on 9/25/16.
//

#include "Pareto.h"
#include "UniformReal.h"
using namespace std;
UniformReal *uniform_gen;

Pareto::Pareto(int location_param, double shape_param)
{
    _location_param = location_param;
    _shape_param = shape_param;
    uniform_gen = new UniformReal(0.0, 1.0);
}

Pareto::~Pareto()
{
    if(uniform_gen != nullptr)
    {
        delete uniform_gen;
    }
}

double Pareto::GetRandom()
{
    double uniform_number = 0;
    double pareto_value = 0;

    while (pareto_value == 0)
    {
        //get uniform number
        uniform_number = uniform_gen->GetRandom();
        //get pareto value
        pareto_value = static_cast<double>(_location_param) / pow(uniform_number, 1.0 / _shape_param);
    }
    return pareto_value;
}

void Pareto::GetPDF(int exp_number, const string& output_file)
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

void Pareto::GetCDF(int exp_number, const string& output_file)
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