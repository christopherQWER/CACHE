//
// Created by cat on 12/4/16.
//

#include "SharedCache.h"
#define CONSOLE CONSOLE_LOGGER
//#define DEBUG
//#define FILE FILE_LOGGER
using namespace std;


SharedCache::SharedCache()
{
}

SharedCache::SharedCache(int request_number, ByteSize cache_size)
{
    t_hit_rate = 0;
    t_experiments_number = request_number;
    t_cache = new Lru(cache_size);
    t_logger = Logger::CreateLogger(CONSOLE);
}

void SharedCache::Clear()
{
    t_experiments_number = 0;
    t_stack_dist = 0;
    t_hit_rate = 0;
    t_client_map.clear();
//    if (t_cache != NULL)
//    {
//        delete t_cache;
//    }
//    if (t_flow != NULL)
//    {
//        delete t_flow;
//    }
//    if (t_logger != NULL)
//    {
//        delete t_logger;
//    }
}

SharedCache::~SharedCache()
{
    Clear();
}

void SharedCache::InsertToClientsMap(Client client)
{
    t_client_map.insert(pair<Asu, Client>(client._application_id, client));
}

void SharedCache::FileRequests(const string &file_name)
{
    int counter = 0;
    int gist_counter = 0;
    int client_counter = 0;
    int module = 100000;
    Request *request;
    t_flow = new TraceFileFlow(file_name);
    string results_dir = _GISTS_DIR_ + string("//") + Utils::GetFileNameWithoutExt(file_name);

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    request = t_flow->GetRequest();
    Client client = Client();
    client.Init(request, results_dir);
    InsertToClientsMap(client);

    // while we not reach the value of number experiment or file not ended
    while ( request != nullptr )
    {
#ifdef DEBUG
        pLogger->ShowRequestInfo(t_request_counter, request->_asu, request->_lba, request->_timestamp);
#endif

        // Add request to LRU cache
        t_cache->LRU(*request);

        // If current application class doesn't exists => create
        if (t_client_map.find(request->_asu) == t_client_map.end())
        {
            Client client = Client();
            client.Init(request, results_dir);
            t_client_map.insert(pair<Asu, Client>(request->_asu, client));
        }
        // Increment request counter for application class
        t_client_map[request->_asu]._request_counter++;

        // Save stack distance for concrete class storage
        t_client_map[request->_asu].SaveStackDist(request->_stack_distance);

        // It's time for gistogram
        if ( (counter != 0) && (counter % module == 0) )
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
                                 "10000", true
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
                                 "10000", true
                                );

            string pdf_command = "plot ";
            string cdf_command = "plot ";

            StackDist min = t_client_map.begin()->second.stack_dist_map.begin()->first;
            StackDist max = (--(t_client_map.begin()->second.stack_dist_map.end()))->first;
            // Go through apps
            int map_size = t_client_map.size();
            for (ClientMap it = t_client_map.begin(); it != t_client_map.end(); ++it)
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

                pdf_command += "'" + pdf_txt + "'" + " using 1:2 with lines";
                cdf_command += "'" + cdf_txt + "'" + " using 1:2 with lines";

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
            pdf_plot.m_xRange = pair<string, string>(to_string(min + 1), to_string(max / 3));
            pdf_plot.DoPlot();

            cdf_plot.m_xRange = pair<string, string>(to_string(min + 1), to_string(max));
            cdf_plot.DoPlot();
            gist_counter++;
        }
        request = t_flow->GetRequest();
        counter++;
    }

    t_hit_rate = t_cache->CalculateHitRate();

#ifdef DEBUG
    pLogger->ShowHitRate(t_hit_rate);
#endif

    t_stack_dist = t_cache->CalculateAvgStackDistance();

#ifdef DEBUG
    pLogger->ShowStackDistance(t_stack_dist);
    pLogger->EndLog();
#endif
}


void SharedCache::MainTester()
{
    int errorCode = 0;
    ByteSize cache_capasity = _1_GB_IN_BYTES_ / 4;
    int experiment_number = 1500000;
    SharedCache tester;

    tester = SharedCache(experiment_number, cache_capasity);
    tester.t_logger->ShowLogText("=================Start: WebSearch1.spc=================");
    //tester.TestStat(_WEB_SEARCH_1_);
    tester.FileRequests(_WEB_SEARCH_1_);
    tester.t_logger->ShowLogText("==================End: WebSearch1.spc==================");
    tester.Clear();

//    tester = SharedCache(experiment_number, cache_capasity);
//    tester.t_logger->ShowLogText("=================Start: WebSearch2.spc=================");
//    //tester.TestStat(_WEB_SEARCH_2_);
//    tester.FileRequests(_WEB_SEARCH_2_);
//    tester.t_logger->ShowLogText("==================End: WebSearch2.spc==================");
//    tester.Clear();
//
//    tester = SharedCache(experiment_number, cache_capasity);
//    tester.t_logger->ShowLogText("=================Start: WebSearch3.spc=================");
//    //tester.TestStat(_WEB_SEARCH_3_);
//    tester.FileRequests(_WEB_SEARCH_3_);
//    tester.t_logger->ShowLogText("==================End: WebSearch3.spc==================");
//    tester.Clear();
//
//    tester = SharedCache(experiment_number, cache_capasity);
//    tester.t_logger->ShowLogText("=================Start: Financial1.spc=================");
//    //tester.TestStat(_FINANCIAL_1_);
//    tester.FileRequests(_FINANCIAL_1_);
//    tester.t_logger->ShowLogText("==================End: Financial1.spc==================");
//    tester.Clear();
//
//    tester = SharedCache(experiment_number, cache_capasity);
//    tester.t_logger->ShowLogText("=================Start: Financial2.spc=================");
//    //tester.TestStat(_FINANCIAL_2_);
//    tester.FileRequests(_FINANCIAL_2_);
//    tester.t_logger->ShowLogText("==================End: Financial2.spc==================");
//    tester.Clear();
}


