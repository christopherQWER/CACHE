//
// Created by cat on 11/19/16.
//

class Distribution {
    virtual double Generate() = 0;
    virtual double GetPDF(double random_value) = 0;
    virtual double GetCDF(double random_value) = 0;
    virtual double GetRandomByPDF(double probably) = 0;
};