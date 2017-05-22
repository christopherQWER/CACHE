//
// Created by cat on 4/12/17.
//

#pragma once
#include <string>
#include <cstring>
#include "../Clients/ClientsManager.h"
#include "../Caches/Lru.h"
#define _1_GB_IN_BYTES_ 1073741824
enum StorageType{SHARED=0, PARTIAL};

class Storage {
public:

    Storage(ByteSize commonSize,
            const std::string &algorithm_dir,
            double _time_step,
            int experiments_number);
    virtual ~Storage();

    void PreparePDF(const ClientMap& clients_map, const std::string& pdf_dir_path);
    void PrepareCDF(const ClientMap& clients_map, const std::string& cdf_dir_path);

    void GetOutputDirs(const Flow* &flow, std::string& pdf_dir, std::string& cdf_dir);

    static inline const char* toString(StorageType type)
    {
        switch (type)
        {
            case SHARED:          return "SHARED";
            case PARTIAL:         return "PARTIAL";
            default:              return "Unknown storage stor_type";
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
    ///
    int             _experiments_number;

    /// Counter of created
    int             _hist_counter;

    /// Time distance between histogram's values saving (per 60 sec, per 10 minutes, etc.)
    double          _time_step;

    /// The common size of cache for all application classes
    ByteSize        _common_size;

    /// Absolute path to directory what named as current storage type.
    /// It constructs from input parameter 'algorithm_dir' and name of current
    /// using storage.
    /// Example:
    /// //
    std::string     _algorithm_dir;
};
