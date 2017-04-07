//
// Created by cat on 9/25/16.
//

#pragma once
#include <map>
#include "../Utils/Utils.h"
#include "Distribution.h"

class Pareto : public Distribution
{
public:

    /// \brief                [Constructor]
    /// \param location_param [location parameter of distribution]
    /// \param shape_param    [shape parameter of distribution]
    /// \return               []
    Pareto(int location_param, double shape_param);
    ~Pareto();

    /// \brief
    /// \return
    double GetRandom();


    /// \brief              [Calculates probability of density function theoretically]
    /// \param random_value [random value Pareto distributed]
    /// \return             [pdf value]
    double GetPDF(double random_value);


    /// \brief                  [Calculates cumulative distribution function]
    /// \param random_value     [random value Pareto distributed]
    /// \return                 [cdf value]
    double GetCDF(double random_value);


    /// \brief          [Generates random value by distribution pdf]
    /// \param probably
    /// \return         [random value]
    double GetRandomByPDF(double probably);

private:
     /// [parameter for indentation of distribution]
    int _location_param;

    /// [parameter for shape of distribution]
    double _shape_param;

    /// [commone counter of generated values]
    int _common_counter;

    /// [storage with random value as key and number of occurences as value]
    std::map<int, int> _counter_map;
};