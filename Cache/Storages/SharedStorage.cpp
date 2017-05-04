#include "../Utils/Plot.h"
#include "SharedStorage.h"
#define TYPE LCONSOLE
//#define DEBUG
using namespace std;


SharedStorage::SharedStorage(std::string algorithm_dir,
                             double time_step,
                             ByteSize cache_size,
                             int request_number) :
        Storage(cache_size, algorithm_dir, time_step, request_number)
{
    _cache = new Lru(cache_size);
    _algorithm_dir = Utils::PathCombine(algorithm_dir, string("Shared"));
    Utils::CreateDirectory(_algorithm_dir);
}

void SharedStorage::Clear()
{
    if (_cache != NULL)
    {
        delete _cache;
    }
    _client_map.clear();
}

void SharedStorage::RunAlgorithm(Logger* &logger, Flow* &flow, bool with_plots)
{
    logger->StartLog();
    // Counts number of requests fo all time
    int counter = 0;
    double prev_time = 0;

    Request *request;
    Client client = Client();

    prev_time = request->_timestamp;

    client.Init(request->_asu, _algorithm_dir);
    InsertToClientsMap(request->_asu, client);

    // while we not reach the value of number experiment or trace_file not ended
    while ( request != nullptr )
    {
        logger->ShowRequestInfo(INFO, counter, request->_asu, request->_lba, request->_timestamp);

        // Add request to LRU cache
        _cache->LRU(*request);

        // If current application class doesn't exists => create
        if (!IsInMap(request->_asu))
        {
            client.Init(request->_asu, _algorithm_dir);
            InsertToClientsMap(request->_asu, client);
        }
        _client_map[request->_asu]._request_counter++;
        _client_map[request->_asu].AddStackDistToMap(request->_stack_distance);

        // It's time for gistogram
        if ( request->_timestamp - prev_time >= _time_step )
        {
            PreparePDF();
            PrepareCDF();
            _gist_counter++;
            prev_time = request->_timestamp;
        }
        delete request;
        request = flow->GetRequest();
        counter++;
    }

    delete flow;
    logger->EndLog();
    delete logger;
}