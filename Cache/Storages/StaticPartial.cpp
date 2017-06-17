//
// Created by cat on 10/27/16.
//

#include "StaticPartial.h"
#define LEVEL DEBUG
using namespace std;

StaticPartial::StaticPartial(ByteSize commonSize,
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
    _algorithm_dir = Utils::PathCombine(_algorithm_dir, toString(type));
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
            case STATISTICAL:
            {
                DevideStatistically(client_map);
            }
        }
    }
}

void StaticPartial::DevideStatistically(ClientMap client_map)
{
    // Map for store new sizes values for clients
    map<Asu, ByteSize> new_sizez;

    ByteSize sum_or_required_caches = 0;
    for (const auto &client : client_map)
    {
        sum_or_required_caches += client.second->required_cache_size;

        // initialize map with client's id and null value of cache size
        new_sizez.insert(pair<Asu, ByteSize>(client.first, 0));
    }
    double x1 = _common_size / static_cast<double>(sum_or_required_caches);

    // If needed sum bigger than all cache space
    if (sum_or_required_caches > _common_size)
    {
        for (const auto &client : client_map)
        {
            ByteSize part_size = x1 * client.second->required_cache_size;
            new_sizez[client.first] = part_size;
//            Lru *cache = new Lru(part_size);
//            _inner_storage.insert(pair<Asu, Lru *>(client.first, cache));
        }
    }
    else
    {
        // If needed space lower than all cache
        // set cache from previous experience
        for (const auto &client : client_map)
        {
            new_sizez[client.first] = client.second->required_cache_size;
//            Lru *cache = new Lru(client.second->required_cache_size);
//            _inner_storage.insert(pair<Asu, Lru *>(client.first, cache));
        }

        //If we have surpluses
        ByteSize diff = _common_size - sum_or_required_caches;
        double sum_of_qoses = 0;
        for (const auto &client : client_map)
        {
            sum_of_qoses += client.second->required_qos;
        }

        double x2 = _common_size / sum_of_qoses;
        for (const auto &client : client_map)
        {
            ByteSize part_size = x2 * client.second->required_qos;
            new_sizez[client.first] += part_size;
//            Lru* cache = new Lru(part_size);
//            _inner_storage.insert(pair<Asu, Lru*>(client.first, cache));
        }
    }

    for (const auto &client_sizez : new_sizez)
    {
        Lru *cache = new Lru(client_sizez.second);
        _inner_storage.insert(pair<Asu, Lru *>(client_sizez.first, cache));
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
            clients_manager.InitAllRequiredFields(request);
        }
        request = flow->GetRequest();
    }
    // It's time for histogram
    if (with_plots)
    {
        SaveForPlots(clients_manager, logger);
    }
    PrepareHrVSSize(clients_manager.clients_map, logger);
}
