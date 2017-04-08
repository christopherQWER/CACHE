//
// Created by cat on 10/27/16.
//
#pragma once
#include <iostream>
#include "Storage.h"
#include "../Utils/Enums.h"
typedef std::map<Asu, Lru*>StorageMap;

class StaticPartial : public Storage {
public:
    StaticPartial(double commonSize,
                    const std::string &algorithm_dir,
                    double time_step,
                    int experiments_number);
    ~StaticPartial();
    void CreateStorage(DivisionType type, ClientMap client_map);
    void Run(ClientsManager& clients_manager, Logger*& logger, Flow*& flow, bool with_plots);

    static inline const char* toString(DivisionType type)
    {
        switch (type)
        {
            case EQUAL:          return "EQUAL";
            case BY_QOS:         return "BY_QOS";
            default:             return "Unknown division type.";
        }
    }

    static inline DivisionType toType(const char* str_repr)
    {
        if (strcmp(str_repr, "EQUAL") == 0)
            return EQUAL;
        else if (strcmp(str_repr, "BY_QOS") == 0)
            return BY_QOS;
    }

private:
    StorageMap _inner_storage;
};