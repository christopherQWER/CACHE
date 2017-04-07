//
// Created by cat on 10/27/16.
//
#pragma once
#include <iostream>
#include "../Loggers/Logger.h"
#include "Algorithm.h"

class StaticPartial : public Algorithm{
public:
    StaticPartial(std::string algorithm_dir, double time_step, int experiments_number);
    void EqualPartial(const std::string& flow_file_name,
                    LoggerType type,
                    const std::string& log_file_name);
    void PercentPartial();
};