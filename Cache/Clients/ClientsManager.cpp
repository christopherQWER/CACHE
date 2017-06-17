//
// Created by cat on 5/8/17.
//

#include "ClientsManager.h"
#define LEVEL DEBUG
using namespace std;

ClientsManager::ClientsManager(const list<XmlClient>& xml_client_list)
{
    // Go through cache objects
    for (list<XmlClient>::const_iterator it = xml_client_list.begin();
         it != xml_client_list.end(); it++)
    {
        Client *client = new Client(it->asu, it->qos);
        client->required_cache_size = it->required_size;
        clients_map.insert(pair<Asu, Client*>(it->asu, client));
    }
    pdf_dir = "";
    cdf_dir = "";
    common_hist_counter = 0;
}

ClientsManager::~ClientsManager()
{
    for (auto& client_pair : clients_map)
    {
        if (client_pair.second != nullptr)
        {
            delete client_pair.second;
        }
    }
    clients_map.clear();
}

void ClientsManager::Clear()
{
    common_hist_counter = 0;
    for (auto& client : clients_map)
    {
        client.second->Clear();
    }
}

bool ClientsManager::IsInMap(Asu asu)
{
    return !(clients_map.find(asu) == clients_map.end());
}

void ClientsManager::InitAllRequiredFields(Request *request)
{
    clients_map[request->_asu]->request_counter++;
    clients_map[request->_asu]->AddStackDistToMap(request->_stack_distance);
    if (request->_is_Hit)
    {
        clients_map[request->_asu]->hits++;
    }
    clients_map[request->_asu]->avg_stack_dist += request->_stack_distance;
    clients_map[request->_asu]->CalculateHitRate();
}

void ClientsManager::QosComparator(Logger*& logger)
{
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string text = string("Asu " + to_string(it->first) + ": ") +
                        "required qos: " + to_string(it->second->required_qos) + ", " +
                        "experimental qos: " + to_string(it->second->avg_hit_rate);
        logger->ShowLogText(LEVEL, text);
    }
}

void ClientsManager::SaveRequiredCacheSizesByQoS(Logger*& logger,
                                                list<XmlClient>& app_list,
                                                ByteSize current_cache_size)
{
    string dir_with_files = Utils::GetDirectoryNameFromPath(pdf_dir);
    string output_file = Utils::PathCombine(Utils::GetDirectoryNameFromPath(dir_with_files), "RequiredSize.txt");

    string log = "==========================================================================================";
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        Utils::AppendToFile(output_file, log);
        it->second->GetRequiredSizeByQoS();
        string text = string("Asu " + to_string(it->first) + ": ") +
                            "common cache size " + to_string(current_cache_size) + ", " +
                             "required qos: " + to_string(it->second->required_qos) + ", " +
                             "required cache size: " + to_string(it->second->required_cache_size);
        logger->ShowLogText(LEVEL, text);
        Utils::AppendToFile(output_file, text);
        list<XmlClient>::iterator list_it = find(app_list.begin(), app_list.end(), XmlClient(it->first, false));
        list_it->required_size = it->second->required_cache_size;
    }
}

void ClientsManager::DrawPDFPlot(const string &trace_name)
{
    for (int i = 0; i < common_hist_counter; ++i)
    {
        string working_dir = Utils::PathCombine(pdf_dir, to_string(i));
        string pdf_plt = Utils::PathCombine(working_dir, string("pdf.plt"));
        string pdf_png = Utils::PathCombine(working_dir, string("pdf.png"));

        StackDist min = 0, max = 0;
        FindLimitsByX(min, max);

        GnuPlot pdf_plot = GnuPlot("512", "512",
                                   trace_name + " PDF",
                                   pdf_png, pdf_plt,
                                   "Stack distance", pair<string, string>(to_string(min), to_string(max)),
                                   "Pdf", pair<string, string>(to_string(0), to_string(1)),
                                   "10000", false
        );

        // Go through apps
        ByteSize map_size = clients_map.size();
        int client_counter = 0;
        string pdf_command = "plot ";
        for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
        {
            string pdf_txt = Utils::PathCombine(working_dir, "App_" + to_string(it->first) + ".txt");
            //string qos_txt = Utils::PathCombine(working_dir, "QoS_" + to_string(it->first) + ".txt");

            // Add line for pdf =====================================================================
            pdf_command += "'" + pdf_txt + "'" +
                           " using 1:2 with lines title 'App_" +
                           to_string(it->first) + "'";

            if (client_counter < map_size - 1)
            {
                pdf_command += ",\\";
            }
            pdf_plot.m_command_lines.push_back(pdf_command);
            pdf_command.clear();
            //=======================================================================================

            // Add line for qos =====================================================================
//            pdf_command += "'" + qos_txt + "'" +
//                    " using 1:2 with lines title 'QoS_" +
//                    to_string(it->first) + "'";



//            pdf_plot.m_command_lines.push_back(pdf_command);
//            pdf_command.clear();
            //======================================================================================

            client_counter++;
        }
        pdf_plot.m_xRange = pair<string, string>(to_string(min), to_string(max));
        pdf_plot.DoPlot();
    }
}

void ClientsManager::DrawCDFPlot(const string &trace_name)
{
    for (int i = 0; i < common_hist_counter; ++i)
    {
        string working_dir = Utils::PathCombine(cdf_dir, to_string(i));
        string cdf_plt = Utils::PathCombine(working_dir, string("cdf.plt"));
        string cdf_png = Utils::PathCombine(working_dir, string("cdf.png"));

        int client_counter = 0;
        StackDist min = 0, max = 0;
        FindLimitsByX(min, max);

        GnuPlot cdf_plot = GnuPlot("512", "512",
                                   trace_name + " CDF",
                                   cdf_png, cdf_plt,
                                   "Stack distance", pair<string, string>(to_string(min), to_string(max)),
                                   "Cdf", pair<string, string>(to_string(0), to_string(1)),
                                   "10000", false
        );

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
}

void ClientsManager::DrawHrVSCacheSizePlot(const std::string algorithm_name,
                                            ByteSize max_cache_capacity,
                                            ByteSize cache_size_step)
{
    string dir_with_files = Utils::GetDirectoryNameFromPath(pdf_dir);
    string algorithm_dir = Utils::PathCombine(Utils::GetDirectoryNameFromPath(dir_with_files),
            string(_HR_VS_SIZE));
    Utils::CreateDirectory(algorithm_dir);

    string hr_plt = Utils::PathCombine(algorithm_dir, string("size_vs_hr.plt"));
    string hr_png = Utils::PathCombine(algorithm_dir, string("size_vs_hr.png"));

    GnuPlot hr_vs_size_plot = GnuPlot("512", "512",
                                algorithm_name,
                                hr_png, hr_plt,
                                "Cache size, bytes", pair<string, string>(to_string(cache_size_step),
                    to_string(max_cache_capacity)),
                                "Hit rate", pair<string, string>(to_string(0), to_string(1)),
                                to_string(cache_size_step), false
    );

    string command = "plot ";
    ByteSize map_size = clients_map.size();
    int client_counter = 0;
    // go through application map
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string file_txt = Utils::PathCombine(algorithm_dir, "App_" + to_string(it->first) + ".txt");
        string qos_file = Utils::PathCombine(algorithm_dir, "QoS_" + to_string(it->first) + ".txt");

        command += "'" + file_txt + "'" +
                       " using 1:2 with lines title 'App_" +
                       to_string(it->first) + "'";

        command += ",\\";
        hr_vs_size_plot.m_command_lines.push_back(command);
        command.clear();

        command += "'" + qos_file + "'" +
                " using 1:2 with lines title 'QoS_" +
                to_string(it->first) + "'";
        if (client_counter < map_size - 1)
        {
            command += ",\\";
        }
        hr_vs_size_plot.m_command_lines.push_back(command);
        command.clear();

        client_counter++;
    }
    //hr_vs_size_plot.m_xRange = pair<string, string>(to_string(0.2), to_string(1));
    hr_vs_size_plot.DoPlot();
}

void ClientsManager::CommonPlot(const string &flow_file_name)
{
//    for (int i = 0; i < common_hist_counter; ++i)
//    {
//        string working_dir = Utils::PathCombine(pdf_dir, to_string(i));
//        for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
//        {
//            // Txt file for current ASU with pdf
//            string pdf_txt = Utils::PathCombine(path_to_cur_pdf_gists, to_string(it->first) + ".txt");
//            // Txt file for current ASU with cdf
//            string cdf_txt = Utils::PathCombine(path_to_cur_cdf_gists, to_string(it->first) + ".txt");
//
//            it->second->SavePdfPlotDots(pdf_txt);
//            it->second->SaveCdfPlotDots(cdf_txt);
//        }
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
