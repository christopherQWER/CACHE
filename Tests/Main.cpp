//
// Created by cat on 9/25/16.
//

#include <iostream>
#include "TestFlow.h"
#include "TestDistribution.h"
using namespace std;


int main ()
{
//    TestFlow flow_tester = TestFlow();
//    flow_tester.MainTester();

    TestDistribution distr_tester = TestDistribution();
    distr_tester.MainTester();
    system("pause");
    return 0;
}