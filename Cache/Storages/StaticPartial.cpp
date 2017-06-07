//
// Created by cat on 10/27/16.
//

#include "StaticPartial.h"
#define LEVEL DEBUG
using namespace std;

StaticPartial::StaticPartial(double commonSize,
                                const string &algorithm_dir,
                                double time_step,
                                ByteSize experiments_number) :
        Storage(commonSize, algorithm_dir, time_step, experiments_number)
{
    _algorithm_dir = Utils::PathCombine(algorithm_dir, string("Static_Partial"));
    Utils::CreateDirectory(_algorithm_dir);
}

StaticPartial::~StaticPartial()
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

void StaticPartial::CreateStorage(DivisionType type, ClientMap client_map)
{
    size_t clients_num = client_map.size();
    if (clients_num > 0)
    {
        switch (type)
        {
            case EQUAL:
            {
                _algorithm_dir = Utils::PathCombine(_algorithm_dir, string("EQUAL"));
                for (const auto &client : client_map)
                {
                    // equal partitioning between application units
                    ByteSize part_size = _common_size / clients_num;
                    Lru* cache = new Lru(part_size);
                    _inner_storage.insert(pair<Asu, Lru*>(client.first, cache));
                }
                break;
            }
            case BY_QOS:
            {
                _algorithm_dir = Utils::PathCombine(_algorithm_dir, string("BY_QOS"));
                double sum = 0;
                for (const auto &client : client_map)
                {
                    sum += client.second->required_qos;
                }

                double x = _common_size / sum;
                for (const auto &client : client_map)
                {
                    ByteSize part_size = x * client.second->required_qos;
                    Lru* cache = new Lru(part_size);
                    _inner_storage.insert(pair<Asu, Lru*>(client.first, cache));
                }
                break;
            }
        }
    }
}

void StaticPartial::Run(ClientsManager& clients_manager,
                        Logger*& logger,
                        Flow*& flow,
                        bool with_plots)
{
    logger->ShowLogText(LEVEL, "Cache simulation ran.");

    double prev_time = 0;
    Request *request = flow->GetRequest();
    GetOutputDirs((const Flow*&) flow, clients_manager.pdf_dir, clients_manager.cdf_dir);

    while ((request != NULL ) && (!flow->IsEndOfFlow()) )
    {
        // Add request to AddToCache cache
        if (! (_inner_storage.find(request->_asu) == _inner_storage.end()) )
        {
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

            // It's time for histogram
            if (with_plots)
            {
                if ( request->_timestamp - prev_time >= _time_step )
                {
                    PreparePDF(clients_manager.clients_map, clients_manager.pdf_dir);
                    PrepareCDF(clients_manager.clients_map, clients_manager.cdf_dir);
                    //PrepareQoS(clients_manager.clients_map, clients_manager.pdf_dir);
                    logger->ShowLogText(LEVEL, "Saving histograms...");

                    _hist_counter++;
                    logger->ShowLogText(LEVEL, "Histograms: " + to_string(_hist_counter));

                    clients_manager.common_hist_counter++;
                    prev_time = request->_timestamp;
                    logger->ShowLogText(LEVEL, "Current time pasted: " + to_string(prev_time));
                }
                clients_manager.clients_map[request->_asu]->result_hist_counter++;
            }
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

        Utils::AppendToFile(path_for_file, _common_size, it->second->avg_hit_rate);
        Utils::AppendToFile(path_for_qos, _common_size, it->second->required_qos);
    }
}