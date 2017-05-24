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