//
// Created by cat on 4/7/17.
//

#include "Distribution.h"
using namespace std;

Distribution::Distribution() {
    distribution = uniform_real_distribution<double>(0.0, 1.0);
}
