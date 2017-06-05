//
// Created by cat on 6/2/17.
//

#pragma once
#include <iostream>
#include <map>
#include "RandomValue.h"

class ChiSquare : public RandomValue {
private:
    std::map<double, int> pdf_map;
    std::default_random_engine generator_1;
    std::chi_squared_distribution<double> distribution;

public:
    ChiSquare(double parameter);
    double GetRandom();
    double GetPDF(int exp_number, const std::string& output_file);
    double GetCDF(int exp_number, const std::string& output_file);
};