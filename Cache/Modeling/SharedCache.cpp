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
    t_hit_rate = 0;
    //delete t_cache;
}

SharedCache::~SharedCache()
{
}

void SharedCache::FileRequests(const string &file_name)
{
    int counter = 0;
    int gist_counter = 0;
    int module = 50000;
    Request *request;
    t_flow = new TraceFileFlow(file_name);
    string results_dir = Utils::GetFileNameWithoutExt(file_name);
    string pdf_path = _GISTS_DIR_ + string("//") + results_dir + "//" + to_string(request->_asu) + "//" + _PDF_DIR_;
    string cdf_path = _GISTS_DIR_ + string("//") + results_dir + "//" + to_string(request->_asu) + "//" + _CDF_DIR_;
    Utils::CreateDirectory(pdf_path);
    Utils::CreateDirectory(cdf_path);

#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
    pLogger->StartLog();
#endif

    request = t_flow->GetRequest();

    // while we not reach the value of number experiment or file not ended
    while ( request != nullptr )
    {
#ifdef DEBUG
        pLogger->ShowRequestInfo(t_request_counter, request->_asu, request->_lba, request->_timestamp);
#endif


        t_cache->LRU(*request);
        if ( (counter != 0) && (counter % module == 0) )
        {
            t_cache->PDFGistogramm(pdf_path + string("//" + to_string(gist_counter) + ".txt"));
            t_cache->CDFGistogramm(cdf_path + string("//" + to_string(gist_counter) + ".txt"));
            gist_counter++;
        }

        request = t_flow->GetRequest();
        counter++;
    }

    gist_counter = 100;
    string pdf_plt = _GISTS_DIR_ + string("//") + results_dir + string("//pdf.plt");
    string png_pdf_path = _GISTS_DIR_ + string("//") + results_dir + string("//") + results_dir + string("_PDFs.png");

    Utils::AppendToFile(pdf_plt, "set terminal  png size 512,512 font 'Verdana, 10'");
    Utils::AppendToFile(pdf_plt, "set nokey");
    Utils::AppendToFile(pdf_plt, "set title \"WebSearch_1 PDF\"");
    Utils::AppendToFile(pdf_plt, "set output '" + png_pdf_path + "'");
    Utils::AppendToFile(pdf_plt, "set ylabel \"PDF\"");
    Utils::AppendToFile(pdf_plt, "set yrange [0:0.1]");
    Utils::AppendToFile(pdf_plt, "set xlabel \"Stack distance\"");
    Utils::AppendToFile(pdf_plt, "set xrange [2:100000]");
    Utils::AppendToFile(pdf_plt, "set xtics 20000");
    Utils::AppendToFile(pdf_plt, "set grid xtics ytics");


    string cdf_plt = _GISTS_DIR_ + string("//") + results_dir + string("//cdf.plt");
    string png_cdf_path = _GISTS_DIR_ + string("//") + results_dir + string("//") + results_dir + string("_CDFs.png");
    Utils::AppendToFile(cdf_plt, "set terminal  png size 512,512 font 'Verdana, 10'");
    Utils::AppendToFile(cdf_plt, "set nokey");
    Utils::AppendToFile(cdf_plt, "set title \"WebSearch_1 CDF\"");
    Utils::AppendToFile(cdf_plt, "set output '" + png_cdf_path + "'");
    Utils::AppendToFile(cdf_plt, "set ylabel \"CDF\"");
    Utils::AppendToFile(cdf_plt, "set yrange [0:1]");
    Utils::AppendToFile(cdf_plt, "set xlabel \"Stack distance\"");
    Utils::AppendToFile(cdf_plt, "set xrange [2:100000]");
    Utils::AppendToFile(cdf_plt, "set xtics 20000");
    Utils::AppendToFile(cdf_plt, "set grid xtics ytics");

    string plot = "plot ";
    string pdf = "";
    string cdf = "";
    for (int i = 0; i < gist_counter; i++)
    {
        if (i == 0)
        {
            pdf += plot;
            cdf += plot;
        }

        pdf += "'" + pdf_path + string("//" + to_string(i) + ".txt") +
               "' using 1:2 lw 2 lt rgb 'blue'";
        cdf += "'" + cdf_path + string("//" + to_string(i) + ".txt") +
               "' using 1:2 lw 2 lt rgb 'red'";
        if (i < gist_counter - 1)
        {
            pdf += ",\\";
            cdf += ",\\";
        }
        Utils::AppendToFile(pdf_plt, pdf);
        Utils::AppendToFile(cdf_plt, cdf);
        pdf.clear();
        cdf.clear();
    }
    Utils::ExecuteCmd(string("gnuplot \"" + pdf_plt + "\""));
    Utils::ExecuteCmd(string("gnuplot \"" + cdf_plt + "\""));

    t_hit_rate = t_cache->CalculateHitRate();

#ifdef DEBUG
    pLogger->ShowHitRate(t_hit_rate);
#endif

    t_stack_dist = t_cache->CalculateStackDistance();

#ifdef DEBUG
    pLogger->ShowStackDistance(t_stack_dist);
    pLogger->EndLog();
#endif
}

void SharedCache::TestStat(const string &file_name)
{
    TraceAnalyzer* a = new TraceAnalyzer(file_name);
    a->GetStat();
    a->AppendToFile(file_name);
}


void SharedCache::MainTester()
{
    int errorCode = 0;
    ByteSize cache_capasity = _1_GB_IN_BYTES_ / 4;
    int experiment_number = 1000000;
    SharedCache tester;

    tester = SharedCache(experiment_number, cache_capasity);
    tester.t_logger->ShowLogText("=================Start: WebSearch1.spc=================");
    //tester.TestStat(_WEB_SEARCH_1_);
    tester.FileRequests(_WEB_SEARCH_1_);
    tester.t_logger->ShowLogText("==================End: WebSearch1.spc==================");
    tester.Clear();

    tester = SharedCache(experiment_number, cache_capasity);
    tester.t_logger->ShowLogText("=================Start: WebSearch2.spc=================");
    //tester.TestStat(_WEB_SEARCH_2_);
    tester.FileRequests(_WEB_SEARCH_2_);
    tester.t_logger->ShowLogText("==================End: WebSearch2.spc==================");
    tester.Clear();

    tester = SharedCache(experiment_number, cache_capasity);
    tester.t_logger->ShowLogText("=================Start: WebSearch3.spc=================");
    //tester.TestStat(_WEB_SEARCH_3_);
    tester.FileRequests(_WEB_SEARCH_3_);
    tester.t_logger->ShowLogText("==================End: WebSearch3.spc==================");
    tester.Clear();

    tester = SharedCache(experiment_number, cache_capasity);
    tester.t_logger->ShowLogText("=================Start: Financial1.spc=================");
    //tester.TestStat(_FINANCIAL_1_);
    tester.FileRequests(_FINANCIAL_1_);
    tester.t_logger->ShowLogText("==================End: Financial1.spc==================");
    tester.Clear();

    tester = SharedCache(experiment_number, cache_capasity);
    tester.t_logger->ShowLogText("=================Start: Financial2.spc=================");
    //tester.TestStat(_FINANCIAL_2_);
    tester.FileRequests(_FINANCIAL_2_);
    tester.t_logger->ShowLogText("==================End: Financial2.spc==================");
    tester.Clear();
}


