//
// Created by cat on 3/2/17.
//

#ifndef PROJECT_TESTCONFIG_H
#define PROJECT_TESTCONFIG_H

#include <iostream>
#include <string>
#include "../Cache/Xml/pugixml.hpp"
#include "Xml/MainConfig.h"
#include "../Cache/Utils/Paths.h"

class TestConfig {
public:
    TestConfig();
    ~TestConfig();

     void MainTester();
};

#endif //PROJECT_TESTCONFIG_H
