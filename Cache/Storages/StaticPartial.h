//
// Created by cat on 10/27/16.
//
#pragma once
#include <iostream>
#include "../Loggers/Logger.h"
#include "Storage.h"

class StaticPartial : public Storage{
public:
    StaticPartial(std::string algorithm_dir, double time_step, int experiments_number);
    void EqualPartial();
    void PercentPartial();
};