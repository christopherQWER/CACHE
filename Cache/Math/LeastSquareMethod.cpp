//
// Created by cat on 5/17/17.
//

#include "LeastSquareMethod.h"
using namespace std;

void LeastSquareMethod::LinearRegression(vector<double> x,
                                        vector<double> y,
                                        double& a,
                                        double& b)
{
    int n = (int) x.size();
    double *pointer_x = &x[0];
    double *pointer_y = &y[0];

    double c0 = 0, c1 = 0, cov00 = 0, cov01 = 0, cov11 = 0, chisq = 0;

//    int error_code = gsl_fit_linear(pointer_x, 1, pointer_y, 1, n,
//                                    &b, &a, &cov00, &cov01, &cov11,
//                                    &chisq);
}
