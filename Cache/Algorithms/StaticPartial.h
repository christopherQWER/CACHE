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
    static void EqualPartial(const std::string& flow_file_name,
                      std::map<Asu, AppClass> client_map,
                      LoggerType type,
                      const std::string& log_file_name);
    static void PercentPartial();

private:
    /// Input parameter set number of experiments
    int experiments_number;

    ///
    StackDist stack_dist;
    AppMap client_map;

    void CreatePdfPlot(const std::string& results_dir, int gist_counter, int client_counter);
    void CreateCdfPlot(const std::string& results_dir, int gist_counter, int client_counter);
};