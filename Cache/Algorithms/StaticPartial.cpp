//
// Created by cat on 10/27/16.
//

#include "StaticPartial.h"
#include "../Flows/TraceFileFlow.h"
#include "../Flows/StackDistFlow.h"
#include "../Utils/Utils.h"

using namespace std;

StaticPartial::StaticPartial(std::string algorithm_dir, double time_step, int experiments_number) :
        Algorithm(algorithm_dir, time_step, experiments_number)
{
}

void StaticPartial::EqualPartial(const string& flow_file_name,
                                 LoggerType type,
                                 const string& log_file_name)
{
    Logger *logger = Logger::CreateLogger(type);
    logger->StartLog();

    // Counts number of requests for all time
    int counter = 0;
    double prev_time = 0;

    Flow *flow;
    Request *request;

    // if flow must be from generator
    if (flow_file_name == "")
    {
        flow = new StackDistFlow();
    }
    // else flow from trace file
    else
    {
        flow = new TraceFileFlow(flow_file_name);
    }

    request = flow->GetRequest();
    prev_time = request->_timestamp;

    while ( request != nullptr )
    {
        logger->ShowRequestInfo(INFO, counter, request->_asu, request->_lba, request->_timestamp);

        // Add request to LRU cache
        _client_map[request->_asu]._cache->LRU(*request);
        // Increment request counter for application class
        _client_map[request->_asu]._request_counter++;
        // Save stack distance for concrete class storage
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

void StaticPartial::PercentPartial()
{

}
