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
#include "Algorithm.h"

class SharedCache : public Algorithm {
public:
    /// \brief
    /// \param algorithm_dir
    /// \param cache_size
    /// \param request_number
    SharedCache(std::string algorithm_dir,
                double time_step,
                ByteSize cache_size,
                int request_number);
    void Clear();

    /// \brief
    /// \param flow_file_name
    /// \param type
    /// \param log_file_name
    void RunAlgorithm(const std::string& flow_file_name,
                    LoggerType type,
                    const std::string& log_file_name);

private:
    Lru* _cache;
};