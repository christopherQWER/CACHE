//
// Created by cat on 1/21/17.
//

#include "Client.h"
#include "../Utils/Paths.h"

using namespace std;

Client::Client()
{
    _request_counter = 0;
    _application_id = 0;
    _QoS = 0;
    pdf_dir_path = "";
    cdf_dir_path = "";
}

Client::~Client()
{
    stack_dist_map.clear();
}

void Client::Init(Asu asu, std::string results_dir)
{
    _application_id = asu;
    _request_counter = 0;
    _QoS = 0;
    pdf_dir_path = Utils::PathCombine(results_dir, _PDF_DIR_);
    cdf_dir_path = Utils::PathCombine(results_dir, _CDF_DIR_);
    Utils::CreateDirectory(pdf_dir_path);
    Utils::CreateDirectory(cdf_dir_path);
}

void Client::SavePdfPlotDots(const std::string& file_path)
{
    int count = 0;
    for (DistStorage::iterator it = stack_dist_map.begin(); it != stack_dist_map.end(); ++it)
    {
        double value = static_cast<double>(it->second) / static_cast<double>(_request_counter);
        Utils::AppendToFile(file_path, it->first, value);
        count++;
    }
}

void Client::SaveCdfPlotDots(const std::string& file_path)
{
    double common_val = 0;
    for (DistStorage::iterator it = stack_dist_map.begin(); it != stack_dist_map.end(); ++it)
    {
        double curr_val = static_cast<double>(it->second) / static_cast<double>(_request_counter);
        Utils::AppendToFile(file_path, it->first, common_val + curr_val);
        common_val += curr_val;
    }
}

void Client::AddStackDistToMap(StackDist stack_dist)
{
    if (IsInStorage(stack_dist))
    {
        stack_dist_map[stack_dist]++;
    }
    else
    {
        stack_dist_map.insert(pair<StackDist, int>(stack_dist, 1));
    }
}

bool Client::IsInStorage(StackDist value)
{
    return !(stack_dist_map.find(value) == stack_dist_map.end());
}