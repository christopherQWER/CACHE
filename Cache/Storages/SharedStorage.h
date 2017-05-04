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
#include "Storage.h"

class SharedStorage : public Storage {
public:

    SharedStorage(std::string algorithm_dir,
                    double time_step,
                    ByteSize cache_size,
                    int request_number);
    void Clear();
    void RunAlgorithm(Logger* &logger, Flow* &flow, bool with_plots);

private:
    Lru* _cache;
};