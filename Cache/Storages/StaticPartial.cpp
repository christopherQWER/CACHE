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
    _algorithm_dir = Utils::PathCombine(algorithm_dir, "Partial");
    Utils::CreateDirectory(_algorithm_dir);
}

StaticPartial::~StaticPartial()
{
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
                    _inner_storage.insert(pair<Asu, Lru>(client.first, Lru(part_size)));
                }
                break;
            }
            case BY_QOS:
            {
                for (const auto &client : client_map)
                {
                    ByteSize part_size = (_common_size * client.second._QoS) / 100;
                    _inner_storage.insert(pair<Asu, Lru>(client.first, Lru(part_size)));
                }
                break;
            }
        }
    }
}

void StaticPartial::Run(Logger*& logger, Flow*& flow, bool with_plots)
{
    logger->StartLog();

    // Counts number of requests for all time
    int counter = 0;
    double prev_time = 0;
    Request *request;

    request = flow->GetRequest();
    prev_time = request->_timestamp;

    while ( request != nullptr )
    {
        // Add request to AddToCache cache
        _inner_storage[request->_asu].AddToCache(*request);
        // Increment request counter for application class
        _inner_storage[request->_asu]._request_counter++;

        // It's time for gistogram
        if (with_plots)
        {
            if ( request->_timestamp - prev_time >= _time_step )
            {
                PreparePDF();
                PrepareCDF();
                _gist_counter++;
                prev_time = request->_timestamp;
            }
        }

        delete request;
        request = flow->GetRequest();
        counter++;
    }
    logger->EndLog();
}