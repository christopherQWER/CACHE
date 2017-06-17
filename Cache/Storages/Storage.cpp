//
// Created by cat on 4/12/17.
//

#include "Storage.h"
using namespace std;
#define LEVEL DEBUG

Storage::Storage(ByteSize commonSize,
                    const string &algorithm_dir,
                    double time_step,
                    ByteSize experiments_number) :
        _common_size(commonSize),
        _experiments_number(experiments_number),
        _algorithm_dir(algorithm_dir),
        _time_step(time_step)
{
    _hist_counter = 0;
}

Storage::~Storage()
{
}

void Storage::PreparePDF(ClientMap& clients_map, const string& pdf_dir_path)
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        // Create output directory
        string current_dir = Utils::PathCombine(pdf_dir_path, to_string(_hist_counter));
        Utils::CreateDirectory(current_dir);

        // Save values to output file
        it->second->output_file_name = string("App_") + to_string(it->first) + string(".txt");
        string pdf_txt = Utils::PathCombine(current_dir, it->second->output_file_name);
        it->second->SavePdfPlotDots(pdf_txt);
    }
}

void Storage::PrepareCDF(ClientMap& clients_map, const string& cdf_dir_path)
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string current_dir = Utils::PathCombine(cdf_dir_path, to_string(_hist_counter));
        Utils::CreateDirectory(current_dir);

        it->second->output_file_name = string("App_") + to_string(it->first) + string(".txt");
        string cdf_txt = Utils::PathCombine(current_dir, it->second->output_file_name);
        it->second->SaveCdfPlotDots(cdf_txt);
    }
}

void Storage::PrepareQoS(ClientMap& clients_map, const string& pdf_dir_path)
{
    for (ClientMap::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        // Create output directory
        string current_dir = Utils::PathCombine(pdf_dir_path, to_string(_hist_counter));
        Utils::CreateDirectory(current_dir);

        it->second->qos_file_name = string ("QoS_") + to_string(it->first) + string(".txt");
        string qos_txt = Utils::PathCombine(current_dir, it->second->qos_file_name);
        it->second->SaveQoSPlotDots(qos_txt);
    }
}

void Storage::PrepareHrVSSize(ClientMap& clients_map, Logger *logger)
{
    Utils::CreateDirectory(path_to_hr_vs_size);
    for (ClientMap::iterator it = clients_map.begin();
         it != clients_map.end(); ++it)
    {
        it->second->avg_hit_rate = clients_map[it->first]->CalculateHitRate();
        it->second->avg_stack_dist = clients_map[it->first]->CalculateAvgStackDistance();

        logger->ShowHitRate(LEVEL, it->second->avg_hit_rate);
        logger->ShowStackDistance(LEVEL, it->second->avg_stack_dist);

        string path_for_file = Utils::PathCombine(path_to_hr_vs_size, string("App_") +
                to_string(it->first) + string(".txt"));
        string path_for_qos = Utils::PathCombine(path_to_hr_vs_size, string("QoS_") +
                to_string(it->first) + string(".txt"));

        Utils::AppendToFile(path_for_file, _common_size, it->second->avg_hit_rate);
        Utils::AppendToFile(path_for_qos, _common_size, it->second->required_qos);
    }
}

void Storage::GetOutputDirs(const Flow* &flow, std::string& pdf_dir, std::string& cdf_dir)
{
    if (flow->current_type == FGENERATOR)
    {
        pdf_dir = Utils::PathCombine(_algorithm_dir,
                                    Flow::toString(FGENERATOR),
                                    to_string(_common_size) + string("_Byte"),
                                    string(_PDF_DIR_));

        cdf_dir = Utils::PathCombine(_algorithm_dir,
                                    Flow::toString(FGENERATOR),
                                    to_string(_common_size) + string("_Byte"),
                                    string(_CDF_DIR_));
        path_to_hr_vs_size = Utils::PathCombine(_algorithm_dir,
                                                Flow::toString(FGENERATOR),
                                                string(_HR_VS_SIZE));
    }
    else
    {
        pdf_dir = Utils::PathCombine(_algorithm_dir, flow->flow_dir_name,
                to_string(_common_size) + string("_Byte"), string(_PDF_DIR_));
        cdf_dir = Utils::PathCombine(_algorithm_dir, flow->flow_dir_name,
                to_string(_common_size) + string("_Byte"), string(_CDF_DIR_));
        path_to_hr_vs_size = Utils::PathCombine(_algorithm_dir, flow->flow_dir_name,
                string(_HR_VS_SIZE));
    }
}

void Storage::SaveForPlots(ClientsManager& clients_manager, Logger *logger)
{
    PreparePDF(clients_manager.clients_map, clients_manager.pdf_dir);
    PrepareCDF(clients_manager.clients_map, clients_manager.cdf_dir);
    //PrepareQoS(clients_manager.clients_map, clients_manager.pdf_dir);
    logger->ShowLogText(LEVEL, "Saving histograms...");

    _hist_counter++;
    logger->ShowLogText(LEVEL, "Histograms: " + to_string(_hist_counter));

    clients_manager.common_hist_counter++;

    //clients_manager.clients_map[request->_asu]->result_hist_counter++;
}

double Storage::BytesToGb(ByteSize byteSize)
{
    return byteSize / static_cast<double>(_1_GB_IN_BYTES_);
    //return byteSize;
}

void Storage::CreateStorage()
{

}

void Storage::CreateStorage(DivisionType type, ClientMap client_map)
{

}
