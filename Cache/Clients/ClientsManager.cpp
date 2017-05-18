//
// Created by cat on 5/8/17.
//

#include "ClientsManager.h"
#include "../Xml/Modes/XmlAnalyzeMode.h"

using namespace std;

ClientsManager::ClientsManager(list<XmlClient> xml_client_list)
{
    // Go through cache objects
    for (const auto &xml_client : xml_client_list)
    {
        Client client = Client(xml_client.asu, xml_client.qos);
        clients_map.insert(pair<Asu, Client>(xml_client.asu, client));
    }
}

bool ClientsManager::IsInMap(Asu asu)
{
    return !(clients_map.find(asu) == clients_map.end());
}


void ClientsManager::DrawPDFPlot(const string &trace_name)
{
    string working_dir = Utils::PathCombine(_algorithm_dir,
                                            trace_name, string(_PDF_DIR_),
                                            to_string(_gist_counter));
    string pdf_plt = Utils::PathCombine(working_dir, string("pdf.plt"));
    string pdf_png = Utils::PathCombine(working_dir, string("pdf.png"));

    GnuPlot pdf_plot = GnuPlot("512", "512",
            trace_name + " PDF",
            pdf_png, pdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Pdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );

    string pdf_command = "plot ";
    StackDist min = clients_map.begin()->second.stack_dist_map.begin()->first;
    StackDist max = (--(clients_map.begin()->second.stack_dist_map.end()))->first;

    // Go through apps
    ByteSize map_size = clients_map.size();
    int client_counter = 0;
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
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

void ClientsManager::DrawCDFPlot(const string &trace_name)
{
    string working_dir = Utils::PathCombine(_algorithm_dir,
            trace_name, string(_CDF_DIR_), to_string(_gist_counter));
    string cdf_plt = Utils::PathCombine(working_dir, string("cdf.plt"));
    string cdf_png = Utils::PathCombine(working_dir, string("cdf.png"));

    GnuPlot cdf_plot = GnuPlot("512", "512",
            trace_name + " CDF",
            cdf_png, cdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Cdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );

    int client_counter = 0;
    string cdf_command = "plot ";
    StackDist min = clients_map.begin()->second.stack_dist_map.begin()->first;
    StackDist max = (--(clients_map.begin()->second.stack_dist_map.end()))->first;

    // Go through apps
    ByteSize map_size = clients_map.size();
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
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

void ClientsManager::CommonPlot(const string &flow_file_name)
{
    string results_dir = Utils::PathCombine(string(_PLOT_DATA_), string("Partial"));
    string flow_name = Utils::GetFileNameWithoutExt(flow_file_name);
    results_dir = Utils::PathCombine(results_dir, flow_name);
    string path_to_cur_pdf_gists = Utils::PathCombine(results_dir, string(_PDF_DIR_),
            to_string(_gist_counter));
    string path_to_cur_cdf_gists = Utils::PathCombine(results_dir, string(_CDF_DIR_),
            to_string(_gist_counter));

    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        // Txt file for current ASU with pdf
        string pdf_txt = Utils::PathCombine(path_to_cur_pdf_gists, to_string(it->first) + ".txt");
        // Txt file for current ASU with cdf
        string cdf_txt = Utils::PathCombine(path_to_cur_cdf_gists, to_string(it->first) + ".txt");

        it->second.SavePdfPlotDots(pdf_txt);
        it->second.SaveCdfPlotDots(cdf_txt);
    }
}