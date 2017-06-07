#include "../Utils/GnuPlot.h"
#include "SharedStorage.h"
#define LEVEL DEBUG
using namespace std;


SharedStorage::SharedStorage(double commonSize,
                                const std::string &algorithm_dir,
                                double time_step,
                                ByteSize experiments_number) :
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
    logger->ShowLogText(LEVEL, "Cache simulation ran.");
    double prev_time = 0;
    Request *request = flow->GetRequest();

    std::string pdf_dir = "", cdf_dir = "";
    GetOutputDirs((const Flow*&) flow, pdf_dir, cdf_dir);
    clients_manager.pdf_dir = pdf_dir;
    clients_manager.cdf_dir = cdf_dir;

    // while we not reach the value of number experiment or trace_file not ended
    while ( (!flow->IsEndOfFlow()) || (request != nullptr))
    {
        // Add request to AddToCache cache
        _cache->AddToCache(*request);

        // All that need for client's map
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
                PreparePDF(clients_manager.clients_map, pdf_dir);
                PrepareCDF(clients_manager.clients_map, cdf_dir);
                //PrepareQoS(clients_manager.clients_map, pdf_dir);
                logger->ShowLogText(LEVEL, "Saving histograms...");

                _hist_counter++;
                logger->ShowLogText(LEVEL, "Histograms: " + to_string(_hist_counter));

                clients_manager.common_hist_counter++;
                prev_time = request->_timestamp;
                logger->ShowLogText(LEVEL, "Current time pasted: " + to_string(prev_time));
            }
            clients_manager.clients_map[request->_asu]->result_hist_counter++;
        }
        request = flow->GetRequest();
    }

    Utils::CreateDirectory(path_to_hr_vs_size);
    for (ClientMap::iterator it = clients_manager.clients_map.begin();
         it != clients_manager.clients_map.end(); ++it)
    {
        it->second->avg_hit_rate = clients_manager.clients_map[it->first]->CalculateHitRate();
        it->second->avg_stack_dist = clients_manager.clients_map[it->first]->CalculateAvgStackDistance();

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