//
// Created by cat on 1/21/17.
//

#include "Client.h"
using namespace std;


Client::Client(Asu asu, double qos)
{
    avg_hit_rate = 0;
    avg_stack_dist = 0;
    hits = 0;

    request_counter = 0;
    result_hist_counter = 0;

    output_file_name = "";
    qos_file_name = "";

    application_id = asu;
    required_qos = qos;
}

Client::~Client()
{
    _stack_dist_map.clear();
    avg_hit_rate = 0;
    avg_stack_dist = 0;
    hits = 0;

    request_counter = 0;
    result_hist_counter = 0;

    output_file_name = "";
    qos_file_name = "";

    application_id = 0;
    required_qos = 0;
}

void Client::Clear()
{
    request_counter = 0;
    avg_hit_rate = 0;
    avg_stack_dist = 0;
    hits = 0;
    _stack_dist_map.clear();
}

HitRate Client::CalculateHitRate()
{
    if (request_counter == 0)
    {
        return -1;
    }
    avg_hit_rate = hits / static_cast<double>(request_counter);
    return avg_hit_rate;
}

StackDist Client::CalculateAvgStackDistance()
{
    if (request_counter == 0)
    {
        return -1;
    }
    avg_stack_dist = avg_stack_dist / request_counter;
    return avg_stack_dist;
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

void Client::SaveQoSPlotDots(const std::string& file_path)
{
    for (StackDistMap::iterator it = _stack_dist_map.begin(); it != _stack_dist_map.end(); ++it)
    {
        Utils::AppendToFile(file_path, it->first, required_qos);
    }
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

ByteSize Client::GetRequiredSizeByQoS()
{
    ProportionalMap revert_map;
    double common_val = 0;
    for (StackDistMap::iterator it = _stack_dist_map.begin(); it != _stack_dist_map.end(); ++it)
    {
        double curr_val = static_cast<double>(it->second) / static_cast<double>(request_counter);
        revert_map.insert(pair<double, StackDist>(common_val + curr_val, it->first));
        common_val += curr_val;
    }
    ProportionalMap::iterator needed_it = revert_map.upper_bound(required_qos);
    //++(needed_it);
    if (needed_it == revert_map.end())
    {
        if (required_qos < revert_map.begin()->first)
        {
            required_cache_size = revert_map.begin()->second * _CELL_SIZE_;
            return required_cache_size;
        }
        else
        {
            ProportionalMap::reverse_iterator reverse_it = revert_map.rbegin();
            required_cache_size = reverse_it->second * _CELL_SIZE_;
            return required_cache_size;
        }
    }

    // Because stack distance shows number of requests with 512 bytes size
    required_cache_size = needed_it->second * _CELL_SIZE_;
    return required_cache_size;
}

StackDist Client::GetMinStackDistance()
{
    return _stack_dist_map.begin()->first;
}

StackDist Client::GetMaxStackDistance()
{
    return (--(_stack_dist_map.end()))->first;
}