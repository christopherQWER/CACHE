//
// Created by cat on 11/19/16.
//
#pragma once
#include <random>
#include <iostream>

class RandomValue {
public:
    std::default_random_engine generator;

    //virtual RandomValue() = 0;
    //virtual double GetRandomValue() = 0;
    //virtual double GetPDF(double random_value) = 0;
    //virtual double GetCDF(double random_value) = 0;
    //virtual double GetRandomByPDF(double probably) = 0;
};