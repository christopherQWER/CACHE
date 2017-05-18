//
// Created by cat on 1/21/17.
//

#include "Client.h"
using namespace std;

Client::Client()
{
    _request_counter = 0;
    _application_id = 0;
    _QoS = 0;
}

void Client::Client(Asu asu, double qos)
{
    Client();
    _application_id = asu;
    _QoS = qos;
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
    int count = 0;
    for (StackDistMap::iterator it = _stack_dist_map.begin(); it != _stack_dist_map.end(); ++it)
    {
        double value = static_cast<double>(it->second) / static_cast<double>(_request_counter);
        Utils::AppendToFile(file_path, it->first, value);
        count++;
    }
}

void Client::SaveCdfPlotDots(const std::string& file_path)
{
    double common_val = 0;
    for (StackDistMap::iterator it = _stack_dist_map.begin(); it != _stack_dist_map.end(); ++it)
    {
        double curr_val = static_cast<double>(it->second) / static_cast<double>(_request_counter);
        Utils::AppendToFile(file_path, it->first, common_val + curr_val);
        common_val += curr_val;
    }
}