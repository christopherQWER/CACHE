//
// Created by cat on 4/12/17.
//

#pragma once
#include <string>
#include <cstring>
#include "../Modeling/Client.h"
#include "../Caches/Lru.h"
#define _1_GB_IN_BYTES_ 1073741824
typedef std::map<Asu, Client> ClientMap;

enum StorageType{SHARED=0, PARTIAL};

class Storage {
public:

    Storage(ByteSize commonSize, std::string algorithm_dir, double _time_step, int experiments_number);
    ~Storage();
    void InsertToClientsMap(Asu asu, const Client& application);
    bool IsInMap(Asu asu);
    void PreparePDF();
    void PrepareCDF();
    void DrawPDFPlot(const std::string &trace_name);
    void DrawCDFPlot(const std::string &trace_name);
    void CommonPlot(const std::string &flow_file_name);

    static inline const char* toString(StorageType type)
    {
        switch (type)
        {
            case SHARED:          return "SHARED";
            case PARTIAL:         return "PARTIAL";
            default:              return "Unknown storage type";
        }
    }
    static inline StorageType toType(const char* str_repr)
    {
        if (strcmp(str_repr, "SHARED") == 0)
            return SHARED;
        else if (strcmp(str_repr, "PARTIAL") == 0)
            return PARTIAL;
    }

protected:
    /// Input parameter set number of experiments
    int             _experiments_number;
    int             _gist_counter;
    double          _time_step;
    ByteSize        _common_size;
    std::string     _algorithm_dir;

    StackDist       _stack_dist;
    ClientMap       _client_map;
};
