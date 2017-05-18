#include "../Utils/GnuPlot.h"
#include "SharedStorage.h"
#define LEVEL INFO
using namespace std;


SharedStorage::SharedStorage(ByteSize commonSize,
                                const std::string &algorithm_dir,
                                double time_step,
                                int experiments_number) :
        Storage(commonSize, algorithm_dir, time_step, experiments_number)
{
    _algorithm_dir = Utils::PathCombine(algorithm_dir, string("Shared"));
    Utils::CreateDirectory(_algorithm_dir);
}

SharedStorage::~SharedStorage()
{
    if (_cache != NULL)
    {
        delete _cache;
    }
}

void SharedStorage::CreateStorage()
{
    _cache = new Lru(_common_size);
}

void SharedStorage::Run(ClientMap& clients_map, Logger*& logger, Flow*& flow, bool with_plots)
{
    logger->StartLog();
    int counter = 0;
    double prev_time = 0;
    Request* request = flow->GetRequest();

    // while we not reach the value of number experiment or trace_file not ended
    while ( flow->GetRequest() != nullptr )
    {
        // Add request to AddToCache cache
        _cache->AddToCache(*request);
        clients_map[request->_asu]._request_counter++;
        clients_map[request->_asu].AddStackDistToMap(request->_stack_distance);

        // It's time for gistogram
        if (with_plots)
        {
            if ( request->_timestamp - prev_time >= _time_step )
            {
                std::string pdf_dir =;
                PreparePDF(clients_map, );
                PrepareCDF(clients_map, );
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