//
// Created by cat on 3/26/17.
//

#pragma once
#include "StaticPartial.h"


class DynamicPartial : public StaticPartial
{
public:

    DynamicPartial(double commonSize,
                        const std::string &algorithm_dir,
                        double time_step,
                        ByteSize experiments_number);
    ~DynamicPartial();
    void Run(ClientsManager& clients_manager, Logger*& logger, Flow*& flow, bool with_plots);

private:
    bool IsAllSatisfied(ClientsManager& clients_manager, ClientMap::iterator &itr);
    bool IsSitisfied(const Client& client);
};