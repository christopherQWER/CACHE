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
    if (_cache != nullptr)
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
    double prev_time = 0;
    Request request = flow->GetRequest();

    std::string pdf_dir = "", cdf_dir = "";
    GetOutputDirs((const Flow*&) flow, pdf_dir, cdf_dir);

    // while we not reach the value of number experiment or trace_file not ended
    while ( !flow->IsEndOfFlow() )
    {
        // Add request to AddToCache cache
        _cache->AddToCache(request);
        clients_map[request._asu]->request_counter++;
        clients_map[request._asu]->AddStackDistToMap(request._stack_distance);
        clients_map[request._asu]->hits++;
        clients_map[request._asu]->avg_hit_rate =
                clients_map[request._asu]->hits / clients_map[request._asu]->request_counter;

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

    logger->EndLog();
}