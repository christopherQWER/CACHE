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

    SharedStorage(ByteSize commonSize,
                    const std::string &algorithm_dir,
                    double time_step,
                    int experiments_number);
    ~SharedStorage();
    void CreateStorage();
    void Run(ClientMap& clients_map, Logger*& logger, Flow*& flow, bool with_plots);

private:
    Lru* _cache;
};