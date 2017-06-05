//
// Created by cat on 4/12/17.
//

#include "Storage.h"
using namespace std;

Storage::Storage(double commonSize,
                    const string &algorithm_dir,
                    double time_step,
                    ByteSize experiments_number) :
        _common_size(commonSize * _1_GB_IN_BYTES_),
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
        path_to_hr_vs_size = Utils::PathCombine(_algorithm_dir, flow->flow_dir_name, string(_HR_VS_SIZE));
    }
}

double Storage::BytesToGb(ByteSize byteSize)
{
    return byteSize / static_cast<double>(_1_GB_IN_BYTES_);
}
