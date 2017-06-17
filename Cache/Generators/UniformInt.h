//
// Created by cat on 5/17/17.
//

#pragma once
#include "RandomValue.h"

class UniformInt : public RandomValue {
private:
    std::uniform_int_distribution<int> distribution;

public:

    UniformInt(int min, int max);
    int GetRandomValue();

    /// \brief              [Calculates probability of density function theoretically]
    /// \param random_value [random value Pareto distributed]
    /// \return             [pdf value]
    void GetPDF(int exp_number, const std::string& output_file);

    /// \brief                  [Calculates cumulative distribution function]
    /// \param random_value     [random value Pareto distributed]
    /// \return                 [cdf value]
    void GetCDF(int exp_number, const std::string& output_file);

};