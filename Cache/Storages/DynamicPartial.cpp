//
// Created by cat on 3/26/17.
//

#include "../Utils/Types.h"
#include "DynamicPartial.h"
#define LEVEL DEBUG
using namespace std;

DynamicPartialCache::DynamicPartialCache(double commonSize,
                                        const string& algorithm_dir,
                                        double time_step,
                                        ByteSize experiments_number) :
        StaticPartial(commonSize, algorithm_dir, time_step, experiments_number)
{
    _algorithm_dir = Utils::PathCombine(algorithm_dir, string("Dynamic partial"));
    Utils::CreateDirectory(_algorithm_dir);
}

DynamicPartialCache::~DynamicPartialCache()
{
    for (auto storage : _inner_storage)
    {
        if (storage.second != nullptr)
        {
            delete storage.second;
        }
    }
    _inner_storage.clear();
}

void DynamicPartialCache::Run(ClientsManager& clients_manager,
                                Logger*& logger,
                                Flow*& flow,
                                bool with_plots)
{
    double prev_time = 0;
    Request *request = flow->GetRequest();
    GetOutputDirs((const Flow*&) flow, clients_manager.pdf_dir, clients_manager.cdf_dir);

    while ( !flow->IsEndOfFlow() )
    {
        // Add request to AddToCache cache
        _inner_storage[request->_asu]->AddToCache(*request);
        _inner_storage[request->_asu]->_request_counter++;

        clients_manager.clients_map[request->_asu]->request_counter++;
        clients_manager.clients_map[request->_asu]->CalculateHitRate();
        logger->ShowHitRate(LEVEL, clients_manager.clients_map[request->_asu]->avg_hit_rate);
        clients_manager.clients_map[request->_asu]->AddStackDistToMap(request->_stack_distance);

        // It's time for histogram
//        if (with_plots)
//        {
            if ( request->_timestamp - prev_time >= _time_step )
            {
                PreparePDF(clients_manager.clients_map, clients_manager.pdf_dir);
                PrepareCDF(clients_manager.clients_map, clients_manager.cdf_dir);
                _hist_counter++;
                clients_manager.common_hist_counter++;
                prev_time = request->_timestamp;
            }
            clients_manager.clients_map[request->_asu]->result_hist_counter++;
        //}
        request = flow->GetRequest();
    }

    Utils::CreateDirectory(path_to_hr_vs_size);
    for (ClientMap::iterator it = clients_manager.clients_map.begin();
         it != clients_manager.clients_map.end(); ++it)
    {
        it->second->avg_hit_rate = it->second->CalculateHitRate();
        string path_for_file = Utils::PathCombine(path_to_hr_vs_size, string("App_") +
                to_string(it->first) + string(".txt"));
        Utils::AppendToFile(path_for_file, _common_size, it->second->avg_hit_rate);
    }
}
