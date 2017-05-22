//
// Created by cat on 4/12/17.
//

#include "Storage.h"
using namespace std;

Storage::Storage(ByteSize commonSize,
                    const string &algorithm_dir,
                    double time_step,
                    int experiments_number) :
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

void Storage::PreparePDF(const ClientMap& clients_map, const string& pdf_dir_path)
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (ClientMap::const_iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        // Create output directory
        string current_dir = Utils::PathCombine(pdf_dir_path, to_string(_hist_counter));
        Utils::CreateDirectory(current_dir);

        // Save values to output file
        it->second.output_file_name = "App_" + to_string(it->first) + ".txt";
        string pdf_txt = Utils::PathCombine(current_dir, it->second.output_file_name);
        it->second.SavePdfPlotDots(pdf_txt);
    }
}

void Storage::PrepareCDF(const ClientMap& clients_map, const string& cdf_dir_path)
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (ClientMap::const_iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string current_dir = Utils::PathCombine(cdf_dir_path, to_string(_hist_counter));
        Utils::CreateDirectory(current_dir);

        it->second.output_file_name = "App_" + to_string(it->first) + ".txt";
        string cdf_txt = Utils::PathCombine(current_dir, it->second.output_file_name);
        it->second.SaveCdfPlotDots(cdf_txt);
    }
}

void Storage::GetOutputDirs(const Flow* &flow, std::string& pdf_dir, std::string& cdf_dir)
{
    if (flow->current_type == FGENERATOR)
    {
        string time_string = Utils::GetCurrentStringUnixTime();
        pdf_dir = Utils::PathCombine(_algorithm_dir, FGENERATOR, time_string, _PDF_DIR_);
        cdf_dir = Utils::PathCombine(_algorithm_dir, FGENERATOR, time_string, _CDF_DIR_);
    }
    else
    {
        pdf_dir = Utils::PathCombine(_algorithm_dir, flow->flow_dir_name, _PDF_DIR_);
        cdf_dir = Utils::PathCombine(_algorithm_dir, flow->flow_dir_name, _CDF_DIR_);
    }
}
