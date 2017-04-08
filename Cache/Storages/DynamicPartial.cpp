//
// Created by cat on 3/26/17.
//

#include "../Utils/Types.h"
#include "DynamicPartial.h"

DynamicPartialCache::DynamicPartialCache(double commonSize, const std::string& algorithm_dir, double time_step,
        int experiments_number)
        :StaticPartial(commonSize, algorithm_dir, time_step, experiments_number)
{
}

DynamicPartialCache::~DynamicPartialCache()
{
}

void DynamicPartialCache::Run(ClientMap& clients_map, Logger*& logger, Flow*& flow, bool with_plots)
{
    logger->StartLog();

    double prev_time = 0;
    Request *request = flow->GetRequest();

    std::string pdf_dir = "", cdf_dir = "";
    GetOutputDirs((const Flow*&) flow, pdf_dir, cdf_dir);


}
