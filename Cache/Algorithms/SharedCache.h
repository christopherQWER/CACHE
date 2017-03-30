//
// Created by cat on 12/4/16.
//

#pragma once
#include <algorithm>
#include <string>
#include "../Modeling/Client.h"
#include "../Caches/Lru.h"
#include "../Generators/Pareto.h"
#include "../Flows/Flow.h"
#include "../Flows/StackDistFlow.h"
#include "../Flows/TraceFileFlow.h"
#include "../Loggers/Logger.h"

#define _1_GB_IN_BYTES_ 1073741824
typedef std::map<Asu, Client>::iterator ClientMap;

class SharedCache {
public:
    /// \brief
    /// \param exp_number
    /// \param cache_size
    SharedCache(int exp_number, ByteSize cache_size);
    ~SharedCache();
    void Clear();

    /// \brief
    /// \param flow_file_name
    /// \param type
    /// \param log_file_name
    void RunAlgorithm(const std::string& flow_file_name, LoggerType type, const std::string& log_file_name);

private:
    ///
    Lru *cache;

    /// Input parameter set number of experiments
    int experiments_number;

    ///
    StackDist stack_dist;
    std::map<Asu, Client> client_map;

    void InsertToClientsMap(Client client);

    void CreatePdfPlot(const std::string& results_dir, int gist_counter, int client_counter);
    void CreateCdfPlot(const std::string& results_dir, int gist_counter, int client_counter);
};