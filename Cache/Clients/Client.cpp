//
// Created by cat on 1/21/17.
//

#include "Client.h"
using namespace std;


void Client::Client(Asu asu, double qos)
{
    application_id = asu;
    required_qos = qos;
    result_gist_counter = 0;
    request_counter = 0;
    output_file_name = "";
}

Client::~Client()
{
    _stack_dist_map.clear();
}

void Client::AddStackDistToMap(StackDist stack_dist)
{
    if (IsInStorage(stack_dist))
    {
        _stack_dist_map[stack_dist]++;
    }
    else
    {
        _stack_dist_map.insert(pair<StackDist, int>(stack_dist, 1));
    }
}

bool Client::IsInStorage(StackDist value)
{
    return !(_stack_dist_map.find(value) == _stack_dist_map.end());
}

void Client::SavePdfPlotDots(const std::string& file_path)
{
    for (StackDistMap::iterator it = _stack_dist_map.begin(); it != _stack_dist_map.end(); ++it)
    {
        double value = static_cast<double>(it->second) / static_cast<double>(request_counter);
        Utils::AppendToFile(file_path, it->first, value);
    }
    result_gist_counter++;
}

void Client::SaveCdfPlotDots(const std::string& file_path)
{
    double common_val = 0;
    for (StackDistMap::iterator it = _stack_dist_map.begin(); it != _stack_dist_map.end(); ++it)
    {
        double curr_val = static_cast<double>(it->second) / static_cast<double>(request_counter);
        Utils::AppendToFile(file_path, it->first, common_val + curr_val);
        common_val += curr_val;
    }
    result_gist_counter++;
}

StackDist Client::GetMinStackDistance()
{
    return _stack_dist_map.begin()->first;
}

StackDist Client::GetMaxStackDistance()
{
    return (--(_stack_dist_map.end()))->first;
}
