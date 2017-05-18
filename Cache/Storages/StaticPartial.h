//
// Created by cat on 10/27/16.
//
#pragma once
#include <iostream>
#include "../Loggers/Logger.h"
#include "../Clients/ClientsManager.h"
#include "Storage.h"
typedef std::map<Asu, Lru>StorageMap;

enum DivisionType {
    EQUAL = 0,
    BY_QOS
};

class StaticPartial : public Storage {
public:
    StaticPartial(ByteSize commonSize,
                    const std::string &algorithm_dir,
                    double time_step,
                    int experiments_number);
    ~StaticPartial();
    void CreateStorage(DivisionType type, ClientMap client_map);
    void Run(Logger*& logger, Flow*& flow, bool with_plots);

private:
    StorageMap _inner_storage;
};