//
// Created by cat on 10/27/16.
//

#include "StaticPartial.h"
using namespace std;

StaticPartial::StaticPartial(double commonSize,
                                const string &algorithm_dir,
                                double time_step,
                                int experiments_number) :
        Storage(commonSize, algorithm_dir, time_step, experiments_number)
{
    _algorithm_dir = Utils::PathCombine(algorithm_dir, string("Static partial"));
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
    logger->StartLog();

    double prev_time = 0;
    Request *request = flow->GetRequest();
    GetOutputDirs((const Flow*&) flow, clients_manager.pdf_dir, clients_manager.cdf_dir);

    while ( !flow->IsEndOfFlow() )
    {
        // Add request to AddToCache cache
        _inner_storage[request->_asu]->AddToCache(*request);
        _inner_storage[request->_asu]->_request_counter++;

        clients_manager.clients_map[request->_asu]->request_counter++;
        clients_manager.clients_map[request->_asu]->avg_hit_rate =
                _inner_storage[request->_asu]->CalculateHitRate();
        logger->ShowHitRate(INFO, clients_manager.clients_map[request->_asu]->avg_hit_rate);
        clients_manager.clients_map[request->_asu]->AddStackDistToMap(request->_stack_distance);

        // It's time for histogram
        if (with_plots)
        {
            if ( request->_timestamp - prev_time >= _time_step )
            {
                PreparePDF(clients_manager.clients_map, clients_manager.pdf_dir);
                PrepareCDF(clients_manager.clients_map, clients_manager.cdf_dir);
                _hist_counter++;
                clients_manager.common_hist_counter++;
                prev_time = request->_timestamp;
            }
            clients_manager.clients_map[request->_asu]->result_hist_counter++;
        }
        request = flow->GetRequest();
    }

    Utils::CreateDirectory(path_to_hr_vs_size);
    for (ClientMap::iterator it = clients_manager.clients_map.begin();
         it != clients_manager.clients_map.end(); ++it)
    {
        it->second->experimental_qos = _inner_storage[it->first]->CalculateHitRate();
        string path_for_file = Utils::PathCombine(path_to_hr_vs_size, string("App_") +
                to_string(it->first) + string(".txt"));
        Utils::AppendToFile(path_for_file, BytesToGb(_common_size), it->second->experimental_qos);
    }
    logger->EndLog();
}