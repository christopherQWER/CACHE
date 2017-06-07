//
// Created by cat on 9/25/16.
//

#pragma once
#include <map>
#include "../Utils/Utils.h"
#include "RandomValue.h"

class Pareto : public RandomValue
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
    void GetPDF(int exp_number, const std::string& output_file);

    /// \brief                  [Calculates cumulative distribution function]
    /// \param random_value     [random value Pareto distributed]
    /// \return                 [cdf value]
    void GetCDF(int exp_number, const std::string& output_file);

private:
     /// [parameter for indentation of distribution]
    int _location_param;

    /// [parameter for shape of distribution]
    double _shape_param;
};