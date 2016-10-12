//
// Created by cat on 9/25/16.
//

#include "Generator.h"
using namespace std;

default_random_engine generator;
uniform_real_distribution<double> distribution(0.0, 1.0);

Generator::Generator()
{
}

Generator::~Generator()
{
}

bool Generator::IsInMap(int value)
{
    return !(_stack_dist.find(value) == _stack_dist.end());
}

int Generator:: ParetoGenerator(int k, double a)
{
    //get uniform number
    double number = distribution(generator);

    //get pareto value
    double value = static_cast<double>(k) / pow(number, 1.0 / a);
    int integer_value = static_cast<int>(value);
    return integer_value;
}

void Generator::GetPDF(vector<int>& values, int value_count)
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

    for (Map_itr it = _stack_dist.begin(); it != _stack_dist.end(); ++it)
    {
        it->second /= static_cast<double>(value_count);
    }
}

void Generator::GetRandomByPDF(vector<int>& values, int value_count)
{
    Map_itr it = _stack_dist.begin();
    _probabilities.insert(pair<double, int>(it->second, it->first));
    ++it;
    for (; it != _stack_dist.end(); ++it)
    {
        _probabilities.insert(pair<double, int>( (--(it))->second + it->second, it->first));
    }

    //get uniform number
    Multimap_itr lower_itr;
    double number = 0;
    for (int i = 0; i < value_count; i++)
    {
        number = distribution(generator);
        lower_itr = _probabilities.lower_bound(number);
        values.push_back(lower_itr->second);
    }
}
