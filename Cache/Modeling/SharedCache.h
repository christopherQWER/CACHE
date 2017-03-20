//
// Created by cat on 12/4/16.
//

#pragma once
#include <algorithm>
#include <string>
#include "Client.h"
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
    SharedCache(int exp_number, ByteSize cache_size);
    ~SharedCache();
    void Clear();
    static void MainTester();

private:
    /// [input parameter set number of experiments]
    int t_experiments_number;
    HitRate t_hit_rate;
    StackDist t_stack_dist;
    Lru *t_cache;
    Flow *t_flow;
    Logger *t_logger;
    std::map<Asu, Client> t_client_map;

    void InsertToClientsMap(Client client);
    void FileRequests(const std::string &file_name);
    void CreatePlot(const std::string& results_dir, int gist_counter, int client_counter);
};