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
    return !(_stack_dist_map.find(value) == _stack_dist_map.end());
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

void Client::LoadPdfPlotDots(const string& file_path, ProportionalMap &pdf_map)
{
    string buffer = "";
    ifstream pdf_file;
    pdf_file.open(file_path.c_str());

    if (getline(pdf_file, buffer))
    {
        pair<double, StackDist> new_pair;
        if (GetPairFromString(buffer, new_pair))
        {
            pdf_map.insert(new_pair);
        }
    }
}

bool Client::GetPairFromString(const string& pdf_string, pair<double, StackDist> &new_pair)
{
    StackDist stack_dist = 0;
    double probably = 0;

    string input = pdf_string;
    istringstream ss(input);
    string part;
    bool result = getline(ss, part, ',') &&
             (istringstream(part) >> stack_dist) &&
             getline(ss, part, ',') &&
             (istringstream(part) >> probably);
    if (!result && ss)
    {
        ss.setstate(ios::failbit);
        return false;
    }
    new_pair = pair<StackDist, double>(stack_dist, probably);
    return true;
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

void Client::LoadCdfPlotDots(const string& file_path)
{
    _stack_dist_map.clear();

}

StackDist Client::GetMinStackDistance()
{
    return _stack_dist_map.begin()->first;
}

StackDist Client::GetMaxStackDistance()
{
    return (--(_stack_dist_map.end()))->first;
}