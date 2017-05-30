//
// Created by cat on 3/26/17.
//

#pragma once
#include "StaticPartial.h"


class DynamicPartialCache : public StaticPartial
{
public:

    DynamicPartialCache(ByteSize commonSize,
                        const std::string &algorithm_dir,
                        double time_step,
                        int experiments_number);
    ~DynamicPartialCache();
    void Run(ClientMap& clients_map, Logger*& logger, Flow*& flow, bool with_plots);
};