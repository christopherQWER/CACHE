#include "../Utils/GnuPlot.h"
#include "SharedStorage.h"
#define LEVEL INFO
using namespace std;


SharedStorage::SharedStorage(double commonSize,
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

void SharedStorage::Run(ClientsManager& clients_manager, Logger*& logger, Flow*& flow, bool with_plots)
{
    logger->StartLog();
    double prev_time = 0;
    Request *request = flow->GetRequest();

    std::string pdf_dir = "", cdf_dir = "";
    GetOutputDirs((const Flow*&) flow, pdf_dir, cdf_dir);
    clients_manager.pdf_dir = pdf_dir;
    clients_manager.cdf_dir = cdf_dir;

    // while we not reach the value of number experiment or trace_file not ended
    while ( !flow->IsEndOfFlow() )
    {
        // Add request to AddToCache cache
        _cache->AddToCache(*request);
        clients_manager.clients_map[request->_asu]->request_counter++;
        clients_manager.clients_map[request->_asu]->AddStackDistToMap(request->_stack_distance);
        clients_manager.clients_map[request->_asu]->hits++;

        clients_manager.clients_map[request->_asu]->avg_hit_rate =
                clients_manager.clients_map[request->_asu]->hits /
                        clients_manager.clients_map[request->_asu]->request_counter;

        // It's time for histogram
        if (with_plots)
        {
            if ( request->_timestamp - prev_time >= _time_step )
            {
                PreparePDF(clients_manager.clients_map, pdf_dir);
                PrepareCDF(clients_manager.clients_map, cdf_dir);
                _hist_counter++;
                clients_manager.common_hist_counter++;
                prev_time = request->_timestamp;
            }
            clients_manager.clients_map[request->_asu]->result_hist_counter++;
        }
        request = flow->GetRequest();
    }

    Utils::CreateDirectory(path_to_hr_vs_size);
    for (ClientMap::iterator it = clients_manager.clients_map.begin(); it != clients_manager.clients_map.end(); ++it)
    {
        it->second->experimental_qos = clients_manager.clients_map[request->_asu]->avg_hit_rate;
        string path_for_file = Utils::PathCombine(path_to_hr_vs_size, string("App_") +
                to_string(it->first) + string(".txt"));
        Utils::AppendToFile(path_for_file, _common_size, it->second->experimental_qos);
    }

    logger->EndLog();
}