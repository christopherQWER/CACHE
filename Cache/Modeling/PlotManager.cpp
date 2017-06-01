//
// Created by cat on 5/10/17.
//

#include <fstream>
#include <sstream>
#include "PlotManager.h"
using namespace std;

void PlotManager::LoadCacheSizeVSHr(const string& file_path, map<ByteSize, double>& size_hr_map)
{
    string buffer = "";
    ifstream pdf_file;
    pdf_file.open(file_path.c_str());

    if (getline(pdf_file, buffer))
    {
        pair<ByteSize, double> new_pair;
        if (GetPairFromString(buffer, new_pair))
        {
            size_hr_map.insert(new_pair);
        }
    }
}

void PlotManager::LoadPdfPlotDots(const string& file_path, ProportionalMap &pdf_map)
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

void PlotManager::LoadCdfPlotDots(const string& file_path)
{

}

template<typename T1, typename T2>
bool PlotManager::GetPairFromString(const string& pdf_string, pair<T1, T2> &new_pair)
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