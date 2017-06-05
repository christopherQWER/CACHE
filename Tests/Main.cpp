//
// Created by cat on 9/25/16.
//

#include <iostream>
#include "XmlTest/TestConfig.h"
#include "TestStorages/TestStaticPartial.h"
#include "TestGenerators/TestDistribution.h"
using namespace std;

int main (void)
{
    TestStaticPartial flow_tester = TestStaticPartial();
    TestDistribution distr_tester = TestDistribution();
    TestConfig cnf_tester = TestConfig();

    flow_tester.MainTester();
    //distr_tester.MainTester();
//    cnf_tester.MainTester();

    cin.get();
    return 0;
}