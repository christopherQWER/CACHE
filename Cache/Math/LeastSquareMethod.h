//
// Created by cat on 5/17/17.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <gsl/gsl_fit.h>

class LeastSquareMethod {
public:

    /// \brief          Method finds the closest line equation for set of points (xi, yi)
    ///                 with method least square fitting
    /// \param x        Vector with all x values
    /// \param y        Vector with all y values appropriates to x
    /// \param a        Evaluated coefficient for line equation y = kx + b
    /// \param b        Evaluated coefficient for line equation y = kx + b
    void LinearRegression(std::vector<double> x, std::vector<double> y, double& a, double& b);
};
