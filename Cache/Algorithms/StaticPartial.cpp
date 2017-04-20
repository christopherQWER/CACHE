//
// Created by cat on 10/27/16.
//

#include "StaticPartial.h"
#include "../Flows/TraceFileFlow.h"
#include "../Flows/StackDistFlow.h"
#include "../Utils/Paths.h"
#include "../Utils/Utils.h"

using namespace std;

StaticPartial::StaticPartial()
{
    experiments_number = 0;
    _gist_counter = 0;
    stack_dist = 0;
}

void StaticPartial::PercentPartial()
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
    // gists per 60 secs
    _time_step = 60;
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
            // Create pdf and cdf plots of current applications
            //CreatePdfPlot(path_to_cur_pdf_gists, _gist_counter, client_counter);
            //CreateCdfPlot(path_to_cur_cdf_gists, _gist_counter, client_counter);
            _gist_counter++;
            prev_time = request->_timestamp;
        }
        if (request)
        {
            delete request;
        }
        request = flow->GetRequest();
        counter++;
    }

    if (flow)
    {
        delete flow;
    }
    logger->EndLog();
    if (logger)
    {
        delete logger;
    }
}

void StaticPartial::CommonPlot(const string& flow_file_name)
{
    string results_dir = Utils::PathCombine(string(_PLOT_DATA_), string("Partial"));
    string flow_name = Utils::GetFileNameWithoutExt(flow_file_name);
    results_dir = Utils::PathCombine(results_dir, flow_name);
    string path_to_cur_pdf_gists = Utils::PathCombine(results_dir, string(_PDF_DIR_), to_string(_gist_counter));
    string path_to_cur_cdf_gists = Utils::PathCombine(results_dir, string(_CDF_DIR_), to_string(_gist_counter));

    for (ClientMap::iterator it = _client_map.begin(); it != _client_map.end(); ++it)
    {
        // Txt file for current ASU with pdf
        string pdf_txt = Utils::PathCombine(path_to_cur_pdf_gists, to_string(it->first) + ".txt");
        // Txt file for current ASU with cdf
        string cdf_txt = Utils::PathCombine(path_to_cur_cdf_gists, to_string(it->first) + ".txt");

        it->second.SavePdfPlotDots(pdf_txt);
        it->second.SaveCdfPlotDots(cdf_txt);
    }
}
