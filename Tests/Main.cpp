//
// Created by cat on 9/25/16.
//

#include <iostream>
#include "TestConfig.h"

using namespace std;


int main ()
{
//    TestFlow flow_tester = TestFlow();
//    flow_tester.MainTester();

//    SharedCache ff_tester = SharedCache();
//    ff_tester.MainTester();

//    TestDistribution distr_tester = TestDistribution();
//    distr_tester.MainTester();

//    TestFlow::MainTester();

    TestConfig *cnf = new TestConfig();
    cnf->MainTester();

    cin.get();
    return 0;
}