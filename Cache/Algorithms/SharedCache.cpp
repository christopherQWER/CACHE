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

void SharedCache::CreatePlot(const string& results_dir, int gist_counter, int client_counter)
{
    string path_to_cur_pdf_gists = results_dir + string("//") + _PDF_DIR_ + string("//") + to_string(gist_counter);
    Utils::CreateDirectory(path_to_cur_pdf_gists);
    string pdf_plt = path_to_cur_pdf_gists + string("//pdf.plt");
    string pdf_png = path_to_cur_pdf_gists + string("//pdf.png");

    Plot pdf_plot = Plot("512", "512",
            "WebSearch_1 PDF",
            pdf_png, pdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Pdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );


    string path_to_cur_cdf_gists = results_dir + string("//") + _CDF_DIR_ + string("//") + to_string(gist_counter);
    Utils::CreateDirectory(path_to_cur_cdf_gists);
    string cdf_plt = path_to_cur_cdf_gists + string("//cdf.plt");
    string cdf_png = path_to_cur_cdf_gists + string("//cdf.png");

    Plot cdf_plot = Plot("512", "512",
            "WebSearch_1 CDF",
            cdf_png, cdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Cdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );

    string pdf_command = "plot ";
    string cdf_command = "plot ";

    StackDist min = client_map.begin()->second.stack_dist_map.begin()->first;
    StackDist max = (--(client_map.begin()->second.stack_dist_map.end()))->first;
    // Go through apps
    int map_size = client_map.size();
    for (ClientMap it = client_map.begin(); it != client_map.end(); ++it)
    {
        if (min > it->second.stack_dist_map.begin()->first)
        {
            min = it->second.stack_dist_map.begin()->first;
        }
        if (max < (--(it->second.stack_dist_map.end()))->first)
        {
            max = (--(it->second.stack_dist_map.end()))->first;
        }

        string pdf_txt = path_to_cur_pdf_gists + "//" + to_string(it->first) + ".txt";
        string cdf_txt = path_to_cur_cdf_gists + "//" + to_string(it->first) + ".txt";

        pdf_command += "'" + pdf_txt + "'" + " using 1:2 with lines title 'Ap_" + to_string(it->first) + "'";
        cdf_command += "'" + cdf_txt + "'" + " using 1:2 with lines title 'Ap_" + to_string(it->first) + "'";

        it->second.PDFGistogramm(pdf_txt);
        it->second.CDFGistogramm(cdf_txt);

        if (client_counter < map_size - 1)
        {
            pdf_command += ",\\";
            cdf_command += ",\\";
        }
        pdf_plot.m_command_lines.push_back(pdf_command);
        cdf_plot.m_command_lines.push_back(cdf_command);

        pdf_command.clear();
        cdf_command.clear();
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

    cdf_plot.m_xRange = pair<string, string>(to_string(min + 1), to_string(max));
    cdf_plot.DoPlot();
}

void SharedCache::RunAlgorithm(const string& file_name)
{
    Logger *logger = Logger::CreateLogger(TYPE);
    logger->ShowLogText(INFO, "=================Start: WebSearch1.spc=================");

    int counter = 0;
    int gist_counter = 0;
    int client_counter = 0;
    int module = 100000;

    Request *request;
    Client client = Client();
    Logger *pLogger = Logger::CreateLogger(TYPE);
    Flow *flow = new TraceFileFlow(file_name);
    string results_dir = _GISTS_DIR_ + string("//") + Utils::GetFileNameWithoutExt(file_name);

    pLogger->StartLog();
    request = flow->GetRequest();

    client.Init(request, results_dir);
    InsertToClientsMap(client);

    // while we not reach the value of number experiment or trace_file not ended
    while ( request != nullptr )
    {
        pLogger->ShowRequestInfo(INFO, counter, request->_asu, request->_lba, request->_timestamp);

        // Add request to LRU cache
        cache->LRU(*request);

        // If current application class doesn't exists => create
        if (client_map.find(request->_asu) == client_map.end())
        {
            Client client = Client();
            client.Init(request, results_dir);
            client_map.insert(pair<Asu, Client>(request->_asu, client));
        }
        // Increment request counter for application class
        client_map[request->_asu]._request_counter++;

        // Save stack distance for concrete class storage
        client_map[request->_asu].SaveStackDist(request->_stack_distance);

        // It's time for gistogram
        if ( (counter != 0) && (counter % module == 0) )
        {
            CreatePlot(results_dir, gist_counter, client_counter);
            gist_counter++;
        }
        request = flow->GetRequest();
        counter++;
    }

    cache->_hit_rate = cache->CalculateHitRate();
    pLogger->ShowHitRate(INFO, cache->_hit_rate);

    stack_dist = cache->CalculateAvgStackDistance();
    pLogger->ShowStackDistance(INFO, stack_dist);
    pLogger->EndLog();

    logger->ShowLogText(INFO, "==================End: WebSearch1.spc==================");
}