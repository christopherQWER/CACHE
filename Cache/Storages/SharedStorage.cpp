#include "../Utils/GnuPlot.h"
#include "SharedStorage.h"
#define LEVEL DEBUG
using namespace std;


SharedStorage::SharedStorage(ByteSize commonSize,
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
    while ( (request != NULL) && (!flow->IsEndOfFlow()) )
    {
        if ( clients_manager.clients_map.find(request->_asu) != clients_manager.clients_map.end())
        {
            // Add request to AddToCache cache
            _cache->AddToCache(*request);
            logger->ShowLogText(LEVEL, "Request stack distance: " +
                    to_string(request->_stack_distance));

            // All that need for client's map
            clients_manager.InitAllRequiredFields(request);
        }
        request = flow->GetRequest();
    }

    // It's time for histogram
    if (with_plots)
    {
        SaveForPlots( clients_manager, logger);
    }
    PrepareHrVSSize(clients_manager.clients_map, logger);
}