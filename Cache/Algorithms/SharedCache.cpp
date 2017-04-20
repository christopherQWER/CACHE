#include "../Utils/Plot.h"
#include "../Utils/Paths.h"
#include "SharedCache.h"
#define TYPE LCONSOLE
//#define DEBUG
using namespace std;


SharedCache::SharedCache(int request_number,
                        int gist_counter,
                        std::string algorithm_dir,
                        ByteSize cache_size) :
        Algorithm(request_number, gist_counter, algorithm_dir)
{
    _cache = new Lru(cache_size);
}

void SharedCache::Clear()
{
    if (_cache != NULL)
    {
        delete _cache;
    }
    experiments_number = 0;
    stack_dist = 0;
    _client_map.clear();
}

SharedCache::~SharedCache()
{
    Clear();
}

void SharedCache::RunAlgorithm(const string& flow_file_name,
                               LoggerType type,
                               const string& log_file_name)
{
    Logger *logger = Logger::CreateLogger(type);

    // Counts number of requests fo all time
    int counter = 0;

    // Gists per 60 secs
    _time_step = 60;
    double prev_time = 0;

    Request *request;
    Flow *flow;
    Client client = Client();
    _algorithm_dir = Utils::PathCombine(string(_PLOT_DATA_), string("Shared"));
    Utils::CreateDirectory(_algorithm_dir);

    // if flow must be from generator
    if (flow_file_name == "")
    {
        flow = new StackDistFlow();
        _algorithm_dir += "Generated";
        logger->ShowLogText(INFO, "=================Start: Generated=================");
    }
    // else flow from trace file
    else
    {
        flow = new TraceFileFlow(flow_file_name);
        string flow_file = Utils::GetFileNameWithoutExt(flow_file_name);
        string path = Utils::PathCombine(_algorithm_dir, flow_file);
        Utils::CreateDirectory(path);
        logger->ShowLogText(INFO, "=================Start: " + flow_file + "=================");
    }

    logger->StartLog();
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
            Client client = Client();
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

            // Create pdf and cdf plots of current applications
            DrawPDFPlot();
            DrawCDFPlot();
            _gist_counter++;
            prev_time = request->_timestamp;
        }
        request = flow->GetRequest();
        counter++;
    }

    logger->EndLog();
}