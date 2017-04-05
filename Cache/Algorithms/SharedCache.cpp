#include "../Utils/Plot.h"
#include "../Utils/Paths.h"
#include "SharedCache.h"
#define TYPE LCONSOLE
//#define DEBUG
using namespace std;


SharedCache::SharedCache(int request_number, ByteSize cache_size)
{
    cache = new Lru(cache_size);
    experiments_number = request_number;
}

void SharedCache::Clear()
{
    if (cache != NULL)
    {
        delete cache;
    }
    experiments_number = 0;
    stack_dist = 0;
    client_map.clear();
}

SharedCache::~SharedCache()
{
    Clear();
}

void SharedCache::InsertToClientsMap(Client client)
{
    client_map.insert(pair<Asu, Client>(client._application_id, client));
}

void SharedCache::CreatePdfPlot(const string& results_dir, int gist_counter, int client_counter)
{
    string pdf_plt = results_dir + string("//pdf.plt");
    string pdf_png = results_dir + string("//pdf.png");

    Plot pdf_plot = Plot("512", "512",
            "WebSearch_1 PDF",
            pdf_png, pdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Pdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );

    string pdf_command = "plot ";
    StackDist min = client_map.begin()->second.stack_dist_map.begin()->first;
    StackDist max = (--(client_map.begin()->second.stack_dist_map.end()))->first;

    // Go through apps
    ByteSize map_size = client_map.size();
    for (ClientMap::iterator it = client_map.begin(); it != client_map.end(); ++it)
    {
        if (min > it->second.stack_dist_map.begin()->first)
        {
            min = it->second.stack_dist_map.begin()->first;
        }
        if (max < (--(it->second.stack_dist_map.end()))->first)
        {
            max = (--(it->second.stack_dist_map.end()))->first;
        }
        string pdf_txt = results_dir + "//" + to_string(it->first) + ".txt";
        pdf_command += "'" + pdf_txt + "'" + " using 1:2 with lines title 'Ap_" + to_string(it->first) + "'";
        if (client_counter < map_size - 1)
        {
            pdf_command += ",\\";
        }
        pdf_plot.m_command_lines.push_back(pdf_command);
        pdf_command.clear();
        client_counter++;
    }
    client_counter = 0;
    switch(gist_counter)
    {
        case 0:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(5000));
            break;
        case 1:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(6000));
            break;
        case 2:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(40000));
            break;
        case 3:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(70000));
            break;
        case 4:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(80000));
            break;
        case 5:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(100000));
            break;
        case 6:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(100000));
            break;
        case 7:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(80000));
            break;
        case 8:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(100000));
            break;
        case 9:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(80000));
            break;
        case 10:
            pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(100000));
            break;
        default:
            pdf_plot.m_xRange = pair<string, string>(to_string(min + 1), to_string(max / 3));
            break;
    }
    pdf_plot.DoPlot();
}

void SharedCache::CreateCdfPlot(const std::string& results_dir, int gist_counter, int client_counter)
{
    string cdf_plt = results_dir + string("//cdf.plt");
    string cdf_png = results_dir + string("//cdf.png");

    Plot cdf_plot = Plot("512", "512",
            "WebSearch_1 CDF",
            cdf_png, cdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Cdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );

    string cdf_command = "plot ";
    StackDist min = client_map.begin()->second.stack_dist_map.begin()->first;
    StackDist max = (--(client_map.begin()->second.stack_dist_map.end()))->first;

    // Go through apps
    int map_size = client_map.size();
    for (ClientMap::iterator it = client_map.begin(); it != client_map.end(); ++it)
    {
        if (min > it->second.stack_dist_map.begin()->first)
        {
            min = it->second.stack_dist_map.begin()->first;
        }
        if (max < (--(it->second.stack_dist_map.end()))->first)
        {
            max = (--(it->second.stack_dist_map.end()))->first;
        }
        string cdf_txt = results_dir + "//" + to_string(it->first) + ".txt";
        cdf_command += "'" + cdf_txt + "'" + " using 1:2 with lines title 'Ap_" + to_string(it->first) + "'";

        if (client_counter < map_size - 1)
        {
            cdf_command += ",\\";
        }
        cdf_plot.m_command_lines.push_back(cdf_command);
        cdf_command.clear();
        client_counter++;
    }
    cdf_plot.m_xRange = pair<string, string>(to_string(min + 1), to_string(max));
    cdf_plot.DoPlot();
}

void SharedCache::RunAlgorithm(const string& flow_file_name,
                               LoggerType type,
                               const string& log_file_name)
{
    Logger *logger = Logger::CreateLogger(type);

    // Counts number of requests fo all time
    int counter = 0;
    int gist_counter = 0;
    int client_counter = 0;

    // gists per 30 secs
    double time_step = 300;
    double prev_time = 0;

    Request *request;
    Flow *flow;
    Client client = Client();
    string results_dir = _PLOT_DATA_ + string("//Shared//");

    // if flow must be from generator
    if (flow_file_name == "")
    {
        flow = new StackDistFlow();
        results_dir += "StackDist";
        logger->ShowLogText(INFO, "=================Start: StackDist=================");
    }
    // else flow from trace file
    else
    {
        flow = new TraceFileFlow(flow_file_name);
        results_dir += Utils::GetFileNameWithoutExt(flow_file_name);
        logger->ShowLogText(INFO, "=================Start: " + Utils::GetFileNameWithoutExt(flow_file_name) + "=================");
    }

    logger->StartLog();
    request = flow->GetRequest();
    prev_time = request->_timestamp;

    client.Init(request, results_dir);
    InsertToClientsMap(client);

    // while we not reach the value of number experiment or trace_file not ended
    while ( request != nullptr )
    {
        logger->ShowRequestInfo(INFO, counter, request->_asu, request->_lba, request->_timestamp);

        // Add request to LRU cache
        cache->LRU(*request);

        // If current application class doesn't exists => create
        if (client_map.find(request->_asu) == client_map.end())
        {
            Client clielnt = Client();
            client.Init(request, results_dir);
            client_map.insert(pair<Asu, Client>(request->_asu, client));
        }
        // Increment request counter for application class
        client_map[request->_asu]._request_counter++;

        // Save stack distance for concrete class storage
        client_map[request->_asu].SaveStackDist(request->_stack_distance);

        // It's time for gistogram
        if ( request->_timestamp - prev_time >= time_step )
        {
            // common directory for current gistogram number for pdf
            string path_to_cur_pdf_gists = results_dir +
                                            string("//") +
                                           _PDF_DIR_ +
                                            string("//") +
                                            to_string(gist_counter);

            Utils::CreateDirectory(path_to_cur_pdf_gists);

            // common directory for current gistogram number for cdf
            string path_to_cur_cdf_gists = results_dir +
                                            string("//") +
                                           _CDF_DIR_ +
                                            string("//") +
                                            to_string(gist_counter);

            Utils::CreateDirectory(path_to_cur_cdf_gists);

            // Write "stack_dist/hit_rate" files for every application unit
            for (ClientMap::iterator it = client_map.begin(); it != client_map.end(); ++it)
            {
                // Txt file for current ASU with pdf
                string pdf_txt = path_to_cur_pdf_gists + "//" + to_string(it->first) + ".txt";
                // Txt file for current ASU with cdf
                string cdf_txt = path_to_cur_cdf_gists + "//" + to_string(it->first) + ".txt";

                it->second.SavePdfPlotDots(pdf_txt);
                it->second.SaveCdfPlotDots(cdf_txt);
            }
            // Create pdf and cdf plots of current applications
            //CreatePdfPlot(path_to_cur_pdf_gists, gist_counter, client_counter);
            //CreateCdfPlot(path_to_cur_cdf_gists, gist_counter, client_counter);

            gist_counter++;
            prev_time = request->_timestamp;
        }
        request = flow->GetRequest();
        counter++;
    }

    cache->_hit_rate = cache->CalculateHitRate();
    logger->ShowHitRate(INFO, cache->_hit_rate);

    stack_dist = cache->CalculateAvgStackDistance();
    logger->ShowStackDistance(INFO, stack_dist);
    logger->EndLog();
    //logger->ShowLogText(INFO, "==================End: WebSearch1.spc==================");
}