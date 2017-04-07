//
// Created by cat on 4/12/17.
//

#pragma once
#include <string>
#include "../Modeling/Client.h"
#include "../Caches/Lru.h"
#define _1_GB_IN_BYTES_ 1073741824
typedef std::map<Asu, Client> ClientMap;

class Algorithm {
public:

    Algorithm(std::string algorithm_dir, double _time_step, int experiments_number);
    ~Algorithm();
    void InsertToClientsMap(Asu asu, const Client& application);
    bool IsInMap(Asu asu);
    void PreparePDF();
    void PrepareCDF();
    void DrawPDFPlot(const std::string &trace_name);
    void DrawCDFPlot(const std::string &trace_name);
    void CommonPlot(const std::string &flow_file_name);

protected:
    /// Input parameter set number of experiments
    int             _experiments_number;
    int             _gist_counter;
    double          _time_step;
    std::string     _algorithm_dir;

    StackDist       _stack_dist;
    ClientMap       _client_map;
};
