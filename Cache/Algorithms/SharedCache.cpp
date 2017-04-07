#include "../Utils/Plot.h"
#include "SharedCache.h"
#define TYPE LCONSOLE
//#define DEBUG
using namespace std;


SharedCache::SharedCache(std::string algorithm_dir,
                         double time_step,
                         ByteSize cache_size,
                         int request_number) :
        Algorithm(algorithm_dir, time_step, request_number)
{
    _cache = new Lru(cache_size);
}

void SharedCache::Clear()
{
    if (_cache != NULL)
    {
        delete _cache;
    }
    _client_map.clear();
}

void SharedCache::RunAlgorithm(const string& flow_file_name,
                               LoggerType type,
                               const string& log_file_name)
{
    Logger *logger = Logger::CreateLogger(type);
    logger->StartLog();

    // Counts number of requests fo all time
    int counter = 0;
    double prev_time = 0;

    Request *request;
    Flow *flow;
    Client client = Client();

    // if flow must be from generator
    if (flow_file_name == "")
    {
        flow = new StackDistFlow();
        _algorithm_dir = Utils::PathCombine(_algorithm_dir, string("Generated"));
        Utils::CreateDirectory(_algorithm_dir);
    }
    // else flow from trace file
    else
    {
        flow = new TraceFileFlow(flow_file_name);
        string flow_file = Utils::GetFileNameWithoutExt(flow_file_name);
        _algorithm_dir = Utils::PathCombine(_algorithm_dir, flow_file);
        Utils::CreateDirectory(_algorithm_dir);
    }

    request = flow->GetRequest();
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