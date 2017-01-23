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
}

Client::~Client()
{
}

void Client::PDFGistogramm(const std::string &file_path)
{
    int count = 0;
    for (DistStor::iterator it = stack_dist_map.begin(); it != stack_dist_map.end(); ++it)
    {
//        while (count < it->first )
//        {
//            Utils::AppendToFile(file_path, count, 0);
//            count++;
//        }
        Utils::AppendToFile(file_path,
                            it->first,
                            static_cast<double>(it->second) / static_cast<double>(_request_counter));
        count++;
    }
}

void Client::CDFGistogramm(const std::string &file_path)
{
    double val = 0;
    for (DistStor::iterator it = stack_dist_map.begin(); it != stack_dist_map.end(); ++it)
    {
        Utils::AppendToFile(file_path, it->first,
                            val + (static_cast<double>(it->second) / static_cast<double>(_request_counter)));

        val += (static_cast<double>(it->second) / static_cast<double>(_request_counter));
    }
}

void Client::Init(Request* request, std::string results_dir)
{
    _application_id = request->_asu;
    pdf_dir_path = results_dir + "//" + _PDF_DIR_;
    cdf_dir_path = results_dir + "//" + _CDF_DIR_;
    Utils::CreateDirectory(pdf_dir_path);
    Utils::CreateDirectory(cdf_dir_path);
}

void Client::SaveStackDist(StackDist stack_dist)
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