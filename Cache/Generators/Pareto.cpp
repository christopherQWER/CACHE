//
// Created by cat on 9/25/16.
//

#include "Pareto.h"
using namespace std;

default_random_engine generator;
uniform_real_distribution<double> distribution(0.0, 1.0);

Pareto::Pareto(int location_param, double shape_param)
{
    _location_param = location_param;
    _shape_param = shape_param;
}

Pareto::~Pareto()
{
}

double Pareto::Generate()
{
    double uniform_number = 0;
    double pareto_value = 0;

    while (pareto_value == 0)
    {
        //get uniform number
        while (uniform_number == 0)
        {
            uniform_number = distribution(generator);
        }

        //get pareto value
        pareto_value = static_cast<double>(_location_param) / pow(uniform_number, 1.0 / _shape_param);
    }
    return pareto_value;
}

double Pareto::GetPDF(double random_value)
{
    if (random_value < _location_param)
    {
        return 0.0;
    }
    double probably = _shape_param * pow(_location_param, _shape_param) / pow(random_value, _shape_param + 1);
    return probably;
}

double Pareto::GetCDF(double random_value)
{
    if (random_value < _location_param)
        return 0;
    double cdf = 1 - pow((_location_param / random_value), _shape_param);
    return cdf;
}

double Pareto::GetRandomByPDF(double probably)
{
    double number = distribution(generator);
//    Mmap_itr lower_itr = probabilities.lower_bound(probably);
//    return lower_itr->second;
}

void ParseLine(const string& line, int& rand_value, double& pdf)
{
    string part;
    istringstream origs(line.c_str());
    bool result = getline(origs, part, ',') &&
             (istringstream(part) >> rand_value) &&
             getline(origs, part, ',') &&
             (istringstream(part) >> pdf);
}