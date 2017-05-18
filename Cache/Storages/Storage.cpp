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
    _gist_counter = 0;
}

Storage::~Storage()
{
}

void Storage::PreparePDF(const ClientMap& clients_map, const string& pdf_dir_path)
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (ClientMap::const_iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string current_dir = Utils::PathCombine(pdf_dir_path, to_string(_gist_counter));
        Utils::CreateDirectory(current_dir);
        string pdf_txt = Utils::PathCombine(current_dir, to_string(it->first) + ".txt");
        it->second.SavePdfPlotDots(pdf_txt);
    }
}

void Storage::PrepareCDF(const ClientMap& clients_map, const string& cdf_dir_path)
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (ClientMap::const_iterator it = clients_map.begin(); it != clients_map.end(); ++it)
    {
        string current_dir = Utils::PathCombine(cdf_dir_path, to_string(_gist_counter));
        Utils::CreateDirectory(current_dir);

        string cdf_txt = Utils::PathCombine(current_dir, to_string(it->first)+".txt");
        it->second.SaveCdfPlotDots(cdf_txt);
    }
}