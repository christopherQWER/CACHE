//
// Created by cat on 4/12/17.
//

#include "Algorithm.h"
#include "../Utils/Plot.h"
#include "../Utils/Paths.h"
using namespace std;

Algorithm::Algorithm(int experiments_number, int gist_counter, std::string algorithm_dir) :
        _experiments_number(experiments_number),
        _gist_counter(gist_counter),
        _algorithm_dir(algorithm_dir),
        _time_step(0)
{
}

Algorithm::~Algorithm()
{
}

void Algorithm::InsertToClientsMap(Asu asu, const Client& application)
{
    _client_map.insert(pair<Asu, Client>(asu, application));
}

bool Algorithm::IsInMap(Asu asu)
{
    return !(_client_map.find(asu) == _client_map.end());
}

void Algorithm::PreparePDF()
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (ClientMap::iterator it = _client_map.begin(); it != _client_map.end(); ++it)
    {
        string current_dir = Utils::PathCombine(it->second.pdf_dir_path, to_string(_gist_counter));
        Utils::CreateDirectory(current_dir);
        string pdf_txt = Utils::PathCombine(current_dir, to_string(it->first) + ".txt");
        it->second.SavePdfPlotDots(pdf_txt);
    }
}

void Algorithm::PrepareCDF()
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (ClientMap::iterator it = _client_map.begin(); it != _client_map.end(); ++it)
    {
        string current_dir = Utils::PathCombine(it->second.cdf_dir_path, to_string(_gist_counter));
        Utils::CreateDirectory(current_dir);
        string cdf_txt = Utils::PathCombine(current_dir, to_string(it->first)+".txt");
        it->second.SaveCdfPlotDots(cdf_txt);
    }
}

void Algorithm::DrawPDFPlot(string trace_name)
{
    string working_dir = Utils::PathCombine(_algorithm_dir,
            trace_name, string(_PDF_DIR_), to_string(_gist_counter));
    string pdf_plt = Utils::PathCombine(working_dir, string("pdf.plt"));
    string pdf_png = Utils::PathCombine(working_dir, string("pdf.png"));

    Plot pdf_plot = Plot("512", "512",
            trace_name + " PDF",
            pdf_png, pdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Pdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );

    string pdf_command = "plot ";
    StackDist min = _client_map.begin()->second.stack_dist_map.begin()->first;
    StackDist max = (--(_client_map.begin()->second.stack_dist_map.end()))->first;

    // Go through apps
    ByteSize map_size = _client_map.size();
    int client_counter = 0;
    for (ClientMap::iterator it = _client_map.begin(); it != _client_map.end(); ++it)
    {
        if (min > it->second.stack_dist_map.begin()->first)
        {
            min = it->second.stack_dist_map.begin()->first;
        }
        if (max < (--(it->second.stack_dist_map.end()))->first)
        {
            max = (--(it->second.stack_dist_map.end()))->first;
        }
        string pdf_txt = Utils::PathCombine(working_dir, to_string(it->first) + ".txt");
        pdf_command += "'" + pdf_txt + "'" +
                        " using 1:2 with lines title 'Ap_" +
                        to_string(it->first) + "'";
        if (client_counter < map_size - 1)
        {
            pdf_command += ",\\";
        }
        pdf_plot.m_command_lines.push_back(pdf_command);
        pdf_command.clear();
        client_counter++;
    }
    client_counter = 0;
    pdf_plot.m_xRange = pair<string, string>(to_string(2), to_string(5000));
    pdf_plot.DoPlot();
}

void Algorithm::DrawCDFPlot(std::string trace_name)
{
    string working_dir = Utils::PathCombine(_algorithm_dir,
            trace_name, string(_CDF_DIR_), to_string(_gist_counter));
    string cdf_plt = Utils::PathCombine(working_dir, string("cdf.plt"));
    string cdf_png = Utils::PathCombine(working_dir, string("cdf.png"));

    Plot cdf_plot = Plot("512", "512",
            trace_name + " CDF",
            cdf_png, cdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Cdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );

    int client_counter = 0;
    string cdf_command = "plot ";
    StackDist min = _client_map.begin()->second.stack_dist_map.begin()->first;
    StackDist max = (--(_client_map.begin()->second.stack_dist_map.end()))->first;

    // Go through apps
    ByteSize map_size = _client_map.size();
    for (ClientMap::iterator it = _client_map.begin(); it != _client_map.end(); ++it)
    {
        if (min > it->second.stack_dist_map.begin()->first)
        {
            min = it->second.stack_dist_map.begin()->first;
        }
        if (max < (--(it->second.stack_dist_map.end()))->first)
        {
            max = (--(it->second.stack_dist_map.end()))->first;
        }
        string cdf_txt = Utils::PathCombine(working_dir, to_string(it->first) + ".txt");
        cdf_command += "'" + cdf_txt + "'" + " using 1:2 with lines title 'Ap_" +
                        to_string(it->first) + "'";

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