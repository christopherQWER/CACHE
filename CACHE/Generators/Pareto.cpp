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

void Pareto::Clear()
{
    rand_storage.clear();
    _location_param = 0;
    _shape_param = 0;
    _common_counter = 0;
}

double Pareto:: Generate()
{
    double uniform_number = 0;
    double pareto_value = 0;

    while (pareto_value == 0)
    {
        //get uniform number
        while (uniform_number == 0)
            uniform_number = distribution(generator);

        //get pareto value
        pareto_value = static_cast<double>(_location_param) / pow(uniform_number, 1.0 / _shape_param);
    }
    UpdateGeneratorState(pareto_value);
    return pareto_value;
}

void Pareto::UpdateGeneratorState(double rand_num)
{
    if (!IsInStorage(rand_num))
    {
        double pdf = ;
        Mmap_itr it = probabilities.insert(pair<double, double>(pdf, rand_num));
        rand_storage.insert(pair<double, Mmap_itr>(rand_num, it));
    }
}

double Pareto::GetPDFTheor(double random_value)
{
    if (random_value < _location_param)
        return 0.0;
    double probably = _shape_param * pow(_location_param, _shape_param) / pow(random_value, _shape_param + 1);
    return probably;
}

double Pareto::GetCDFTheor(double random_value)
{
    if (random_value < _location_param)
        return 0;
    double cdf = 1 - pow((_location_param / random_value), _shape_param);
    return cdf;
}

double Pareto::GetRandomByPDF(double probably)
{
    double number = distribution(generator);
    Mmap_itr lower_itr = probabilities.lower_bound(probably);
    return lower_itr->second;
}

bool Pareto::IsInStorage(double rand_value)
{
    return !(rand_storage.find(rand_value) == rand_storage.end());
}