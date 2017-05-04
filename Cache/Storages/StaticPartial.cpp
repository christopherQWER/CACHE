//
// Created by cat on 10/27/16.
//

#include "StaticPartial.h"
#include "../Flows/StackDistFlow.h"
using namespace std;

StaticPartial::StaticPartial(std::string algorithm_dir, double time_step, int experiments_number) :
        Storage(algorithm_dir, time_step, cache_size, experiments_number)
{
    _algorithm_dir = Utils::PathCombine(algorithm_dir, "Partial");
    Utils::CreateDirectory(_algorithm_dir);
}

void StaticPartial::EqualPartial()
{
    logger->StartLog();

    // Counts number of requests for all time
    int counter = 0;
    double prev_time = 0;

    Flow *flow;
    Request *request;

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

    logger->EndLog();
}

void StaticPartial::PercentPartial()
{

}
