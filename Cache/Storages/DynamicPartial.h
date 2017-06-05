//
// Created by cat on 3/26/17.
//

#pragma once
#include "StaticPartial.h"


class DynamicPartialCache : public StaticPartial
{
public:

    DynamicPartialCache(double commonSize,
                        const std::string &algorithm_dir,
                        double time_step,
                        ByteSize experiments_number);
    ~DynamicPartialCache();
    void Run(ClientsManager& clients_manager, Logger*& logger, Flow*& flow, bool with_plots);
};