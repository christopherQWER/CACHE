//
// Created by cat on 10/27/16.
//
#pragma once

#include <iostream>
#include "../Modeling/AppClass.h"

class StaticPartial {
public:
    void EqualPartial(std::list<AppClass> clientList, const std::string& file_name);
    void PercentPartial();
};