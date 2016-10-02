//
// Created by cat on 9/25/16.
//

#include "DistributionGenerator.h"
using namespace std;

default_random_engine generator;
uniform_real_distribution<double> distribution(0.0, 1.0);

DistributionGenerator::DistributionGenerator()
{
}

DistributionGenerator::~DistributionGenerator()
{
}

bool DistributionGenerator::IsInMap(int value)
{
    return !(_stack_dist.find(value) == _stack_dist.end());
}

void DistributionGenerator::Pareto(vector<int>& values, int value_count, int k, double a)
{
    for (int i = 0; i < value_count; i++)
    {
        //get uniform number
        double number = distribution(generator);

        //get pareto value
        double value = static_cast<double>(k) / pow(number, 1.0 / a);
        int integer_value = static_cast<int>(value);
        values.push_back(integer_value);
    }
}

void DistributionGenerator::GetPDF(vector<int>& values, int value_count, string output_file)
{
    for (int i = 0; i < value_count; i++)
    {
        if (IsInMap(values[i]))
        {
            _stack_dist[values[i]]++;
        }
        else
        {
            _stack_dist.insert(pair<int, double>(values[i], 1));
        }
    }

    for (int i = 0; i < value_count; i++)
    {
        _stack_dist[values[i]] /= static_cast<double>(value_count);
    }
    Utils::WriteFile(output_file, _stack_dist);
}

void DistributionGenerator::GetRandomByPDF(vector<int>& values, int value_count)
{
    MAP_ITR it = _stack_dist.begin();
    _probabilities.insert(pair<double, int>(it->second, it->first));
    ++it;
    for (; it != _stack_dist.end(); ++it)
    {
        _probabilities.insert(pair<double, int>( (--(it))->second + it->second, it->first));
    }

    //get uniform number
    MULTIMAP_ITR lower_itr;
    double number = 0;
    for (int i = 0; i < value_count; i++)
    {
        number = distribution(generator);
        lower_itr = _probabilities.lower_bound(number);
        values.push_back(lower_itr->second);
    }
}
