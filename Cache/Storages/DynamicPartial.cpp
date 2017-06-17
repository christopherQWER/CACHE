//
// Created by cat on 3/26/17.
//

#include "../Utils/Types.h"
#include "DynamicPartial.h"
#define LEVEL DEBUG
using namespace std;

DynamicPartial::DynamicPartial(ByteSize commonSize,
                                        const string& algorithm_dir,
                                        double time_step,
                                        ByteSize experiments_number) :
        StaticPartial(commonSize, algorithm_dir, time_step, experiments_number)
{
    _algorithm_dir = Utils::PathCombine(algorithm_dir, string("Dynamic partial"));
    Utils::CreateDirectory(_algorithm_dir);
}

DynamicPartial::~DynamicPartial()
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

void DynamicPartial::Run(ClientsManager& clients_manager,
                                Logger*& logger,
                                Flow*& flow,
                                bool with_plots)
{
    logger->ShowLogText(LEVEL, "Cache simulation ran.");

    double prev_time = 0;
    Request *request = flow->GetRequest();
    GetOutputDirs((const Flow*&) flow, clients_manager.pdf_dir, clients_manager.cdf_dir);


    while ( (!flow->IsEndOfFlow()) || (request != nullptr ) )
    {
        if (! (_inner_storage.find(request->_asu) == _inner_storage.end()) )
        {
            // Add request to AddToCache cache
            _inner_storage[request->_asu]->AddToCache(*request);

            // All that need to client's map
            clients_manager.clients_map[request->_asu]->request_counter++;
            clients_manager.clients_map[request->_asu]->AddStackDistToMap(request->_stack_distance);
            if (request->_is_Hit)
            {
                clients_manager.clients_map[request->_asu]->hits++;
            }
            clients_manager.clients_map[request->_asu]->avg_stack_dist += request->_stack_distance;
            clients_manager.clients_map[request->_asu]->CalculateHitRate();

            ClientMap::iterator sad_it;
            if (!IsAllSatisfied(clients_manager, sad_it))
            {

            }


            // It's time for histogram
//        if (with_plots)
//        {
            if ( request->_timestamp - prev_time >= _time_step )
            {
                PreparePDF(clients_manager.clients_map, clients_manager.pdf_dir);
                PrepareCDF(clients_manager.clients_map, clients_manager.cdf_dir);
                //PrepareQoS(clients_manager.clients_map, clients_manager.pdf_dir);
                _hist_counter++;
                clients_manager.common_hist_counter++;
                prev_time = request->_timestamp;
            }
            clients_manager.clients_map[request->_asu]->result_hist_counter++;
            //}
        }
        request = flow->GetRequest();
    }

    Utils::CreateDirectory(path_to_hr_vs_size);
    for (ClientMap::iterator it = clients_manager.clients_map.begin();
         it != clients_manager.clients_map.end(); ++it)
    {
        it->second->avg_hit_rate = it->second->CalculateHitRate();
        it->second->avg_stack_dist = it->second->CalculateAvgStackDistance();

        logger->ShowHitRate(LEVEL, it->second->avg_hit_rate);
        logger->ShowStackDistance(LEVEL, it->second->avg_stack_dist);

        string path_for_file = Utils::PathCombine(path_to_hr_vs_size, string("App_") +
                to_string(it->first) + string(".txt"));
        string path_for_qos = Utils::PathCombine(path_to_hr_vs_size, string("QoS_") +
                to_string(it->first) + string(".txt"));

        Utils::AppendToFile(path_for_file, BytesToGb(_common_size), it->second->avg_hit_rate);
        Utils::AppendToFile(path_for_qos, BytesToGb(_common_size), it->second->required_qos);
    }
}


bool DynamicPartial::IsAllSatisfied(ClientsManager& clients_manager, ClientMap::iterator &itr)
{
    for (ClientMap::iterator it = clients_manager.clients_map.begin();
         it != clients_manager.clients_map.end(); ++it)
    {
        if (!IsSitisfied(*(it->second)))
        {
            itr = it;
            return false;
        }
    }
    return true;
}


bool DynamicPartial::IsSitisfied(const Client& client)
{
    if (client.avg_hit_rate < client.required_qos)
    {
        return false;
    }
    return true;
}