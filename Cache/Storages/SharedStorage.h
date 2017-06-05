//
// Created by cat on 12/4/16.
//

#pragma once
#include <algorithm>
#include <string>
#include "../Caches/Lru.h"
#include "../Flows/Flow.h"
#include "../Flows/StackDistFlow.h"
#include "../Flows/TraceFileFlow.h"
#include "../Loggers/Logger.h"
#include "Storage.h"

class SharedStorage : public Storage {
public:

    SharedStorage(double commonSize,
                    const std::string &algorithm_dir,
                    double time_step,
                    ByteSize experiments_number);
    ~SharedStorage();
    void CreateStorage();
    void Run(ClientsManager& clients_manager, Logger*& logger, Flow*& flow, bool with_plots);

private:
    Lru* _cache;
};