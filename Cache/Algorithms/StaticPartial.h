//
// Created by cat on 10/27/16.
//
#pragma once

#include <iostream>
#include "../Modeling/AppClass.h"
#include "../Loggers/Logger.h"
typedef std::map<Asu, AppClass> AppMap;

class StaticPartial {
public:
    StaticPartial(std::map<Asu, AppClass> client_map);
    void EqualPartial(const std::string& flow_file_name,
                            LoggerType type,
                            const std::string& log_file_name);
    void PercentPartial();

private:
    /// Input parameter set number of experiments
    int experiments_number;

    ///
    int _gist_counter;
    StackDist _stack_dist;
    AppMap _client_map;

    void CreatePdfPlot(const std::string& results_dir, int client_counter);
    void CreateCdfPlot(const std::string& results_dir, int client_counter);

    void CommonPlot(const std::string& flow_file_name);
};