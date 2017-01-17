//
// Created by cat on 9/25/16.
//

#include <iostream>
#include "TestFlow.h"
#include "TestDistribution.h"
#include "FileFlowTest.h"
#include "Paths.h"
using namespace std;


int main ()
{
//    TestFlow flow_tester = TestFlow();
//    flow_tester.MainTester();

    FileFlowTest ff_tester = FileFlowTest();
    ff_tester.MainTester();

//    TestDistribution distr_tester = TestDistribution();
//    distr_tester.MainTester();
    system("pause");
    return 0;
}