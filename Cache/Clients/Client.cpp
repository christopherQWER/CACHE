//
// Created by cat on 1/21/17.
//

#include "Client.h"
using namespace std;


Client::Client(Asu asu, double qos)
{
    experimental_qos = 0;
    avg_hit_rate = 0;
    hits = 0;

    request_counter = 0;
    result_hist_counter = 0;

    output_file_name = "";

    application_id = asu;
    required_qos = qos;
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
    return _stack_dist_map.find(value) != _stack_dist_map.end();
}

void Client::SavePdfPlotDots(const string& file_path)
{
    for (StackDistMap::iterator it = _stack_dist_map.begin(); it != _stack_dist_map.end(); ++it)
    {
        double value = static_cast<double>(it->second) / static_cast<double>(request_counter);
        Utils::AppendToFile(file_path, it->first, value);
    }
    result_hist_counter++;
}

void Client::SaveCdfPlotDots(const string& file_path)
{
    double common_val = 0;
    for (StackDistMap::iterator it = _stack_dist_map.begin(); it != _stack_dist_map.end(); ++it)
    {
        double curr_val = static_cast<double>(it->second) / static_cast<double>(request_counter);
        Utils::AppendToFile(file_path, it->first, common_val + curr_val);
        common_val += curr_val;
    }
    result_hist_counter++;
}

StackDist Client::GetMinStackDistance()
{
    return _stack_dist_map.begin()->first;
}

StackDist Client::GetMaxStackDistance()
{
    return (--(_stack_dist_map.end()))->first;
}