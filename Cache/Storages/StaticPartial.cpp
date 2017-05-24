//
// Created by cat on 10/27/16.
//

#include "StaticPartial.h"
using namespace std;

StaticPartial::StaticPartial(ByteSize commonSize,
                                const string &algorithm_dir,
                                double time_step,
                                int experiments_number) :
        Storage(commonSize, algorithm_dir, time_step, experiments_number)
{
    _algorithm_dir = Utils::PathCombine(algorithm_dir, string("Partial"));
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
                for (const auto &client : client_map)
                {
                    ByteSize part_size = (_common_size * client.second->required_qos) / 100;
                    Lru* cache = new Lru(part_size);
                    _inner_storage.insert(pair<Asu, Lru*>(client.first, cache));
                }
                break;
            }
        }
    }
}

void StaticPartial::Run(ClientMap& clients_map, Logger*& logger, Flow*& flow, bool with_plots)
{
    logger->StartLog();

    double prev_time = 0;
    Request request = flow->GetRequest();

    std::string pdf_dir = "", cdf_dir = "";
    GetOutputDirs((const Flow*&) flow, pdf_dir, cdf_dir);

    while ( !flow->IsEndOfFlow() )
    {
        // Add request to AddToCache cache
        _inner_storage[request._asu]->AddToCache(request);
        _inner_storage[request._asu]->_request_counter++;
        clients_map[request._asu]->AddStackDistToMap(request._stack_distance);

        // It's time for histogram
        if (with_plots)
        {
            if ( request._timestamp - prev_time >= _time_step )
            {
                PreparePDF(clients_map, pdf_dir);
                PrepareCDF(clients_map, cdf_dir);
                _hist_counter++;
                prev_time = request._timestamp;
            }
            clients_map[request._asu]->result_hist_counter++;
        }
        request = flow->GetRequest();
    }

    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        it->second->experimental_qos = _inner_storage[it->first]->CalculateHitRate();
    }
    logger->EndLog();
}