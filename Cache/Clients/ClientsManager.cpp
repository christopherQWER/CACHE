//
// Created by cat on 5/8/17.
//

#include "ClientsManager.h"
using namespace std;

ClientsManager::ClientsManager(const list<XmlClient>& xml_client_list)
{
    // Go through cache objects
    for (list<XmlClient>::const_iterator it = xml_client_list.begin(); it != xml_client_list.end(); it++)
    {
        Client *client = new Client(it->asu, it->qos);
        clients_map.insert(pair<Asu, Client*>(it->asu, client));
    }
    pdf_dir = "";
    cdf_dir = "";
}

ClientsManager::~ClientsManager()
{
    for (auto client_pair : clients_map)
    {
        if (client_pair.second != nullptr)
        {
            delete client_pair.second;
        }
    }
}

bool ClientsManager::IsInMap(Asu asu)
{
    return !(clients_map.find(asu) == clients_map.end());
}

void ClientsManager::QosComparator(Logger*& logger)
{
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string text = string("Asu " + to_string(it->first) + ": ") +
                        "required qos: " + to_string(it->second->required_qos) + ", " +
                        "experimental qos: " + to_string(it->second->experimental_qos);
        logger->ShowLogText(INFO, text);
    }
}

void ClientsManager::DrawPDFPlot(const string &trace_name)
{
    string working_dir = Utils::PathCombine(pdf_dir, to_string(common_hist_counter));
    string pdf_plt = Utils::PathCombine(working_dir, string("pdf.plt"));
    string pdf_png = Utils::PathCombine(working_dir, string("pdf.png"));

    GnuPlot pdf_plot = GnuPlot("512", "512",
            trace_name + " PDF",
            pdf_png, pdf_plt,
            "Stack distance", pair<string, string>(to_string(2), to_string(100000)),
            "Pdf", pair<string, string>(to_string(0), to_string(1)),
            "10000", false
    );

    StackDist min = 0, max = 0;
    FindLimitsByX(min, max);

    // Go through apps
    ByteSize map_size = clients_map.size();
    int client_counter = 0;
    string pdf_command = "plot ";
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string pdf_txt = Utils::PathCombine(working_dir, "App_" + to_string(it->first) + ".txt");
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
    pdf_plot.m_xRange = pair<string, string>(to_string(min), to_string(max));
    pdf_plot.DoPlot();
}

void ClientsManager::DrawCDFPlot(const string &trace_name)
{
    string working_dir = Utils::PathCombine(cdf_dir, to_string(common_hist_counter));
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
    StackDist min = 0, max = 0;
    FindLimitsByX(min, max);

    // Go through apps
    ByteSize map_size = clients_map.size();
    string cdf_command = "plot ";
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string cdf_txt = Utils::PathCombine(working_dir, "App_" + to_string(it->first) + ".txt");
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
    cdf_plot.m_xRange = pair<string, string>(to_string(min), to_string(max));
    cdf_plot.DoPlot();
}

void ClientsManager::CommonPlot(const string &flow_file_name)
{
//    string results_dir = Utils::PathCombine(string(_PLOT_DATA_), string("Partial"));
//    string flow_name = Utils::GetFileNameWithoutExt(flow_file_name);
//    results_dir = Utils::PathCombine(results_dir, flow_name);
//    string path_to_cur_pdf_gists = Utils::PathCombine(results_dir, string(_PDF_DIR_),
//            to_string(common_hist_counter));
//    string path_to_cur_cdf_gists = Utils::PathCombine(results_dir, string(_CDF_DIR_),
//            to_string(common_hist_counter));
//
//    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
//    {
//        // Txt file for current ASU with pdf
//        string pdf_txt = Utils::PathCombine(path_to_cur_pdf_gists, to_string(it->first) + ".txt");
//        // Txt file for current ASU with cdf
//        string cdf_txt = Utils::PathCombine(path_to_cur_cdf_gists, to_string(it->first) + ".txt");
//
//        it->second->SavePdfPlotDots(pdf_txt);
//        it->second->SaveCdfPlotDots(cdf_txt);
//    }
}

void ClientsManager::FindLimitsByX(StackDist& min, StackDist& max)
{
    // Get limits of first application
    ClientMap::iterator it = clients_map.begin();
    min = it->second->GetMinStackDistance();
    max = it->second->GetMaxStackDistance();
    ++it;

    for (; it != clients_map.end(); ++it)
    {
        if (min > it->second->GetMinStackDistance())
        {
            min = it->second->GetMinStackDistance();
        }
        if (max < it->second->GetMaxStackDistance())
        {
            max = it->second->GetMaxStackDistance();
        }
    }
}

ClientsManager::ClientsManager()
{

}
