//
// Created by cat on 4/20/17.
//

#include "StackDistanceGen.h"
#include "UniformReal.h"
#include "../Utils/Utils.h"
using namespace std;
UniformReal uniform_gen = UniformReal(0.0, 1.0);

StackDistanceGen::StackDistanceGen(const std::string& pdf_file_path)
        : _exp_counter(0)
{
    string line = "";
    ifstream pdf_file;
    pdf_file.open(pdf_file_path.c_str());

    while (getline(pdf_file, line))
    {
        pair<StackDist, double> parsed_pair = ParsePairs(line);
        _pdf_storage.insert(parsed_pair);
    }
    pdf_file.close();
}

StackDistanceGen::~StackDistanceGen()
{
    if (_cdf_storage.size() > 0)
    {
        _cdf_storage.clear();
    }
    if (_pdf_storage.size() > 0)
    {
        _pdf_storage.clear();
    }
}

StackDist StackDistanceGen::GetRandomValue()
{
    CreateCdfStorage();

    double uniform_number = 0;
    uniform_number = uniform_gen.GetRandom();

    map<double, StackDist>::iterator it = _cdf_storage.lower_bound(uniform_number);
    if (it != _cdf_storage.end())
    {
        if (_experimental_pdf.find(it->second) != _experimental_pdf.end())
        {
            _experimental_pdf[it->second]++;
        }
        else
        {
            _experimental_pdf.insert(pair<StackDist, double>(it->second, 1));
        }
        _exp_counter++;
        return it->second;
    }
    return 0;
}

pair<StackDist, double> StackDistanceGen::ParsePairs(const std::string& line_to_parse)
{
    pair<StackDist, double> parsed;
    StackDist stackDist = 0;
    double pdf_value = 0;
    bool result = false;
    istringstream origs(line_to_parse.c_str());
    string part;

    result = getline(origs, part, '\t') &&
            (istringstream(part) >> stackDist) &&
            getline(origs, part, '\t') &&
            (istringstream(part) >> pdf_value);
    if (!result && origs)
    {
        origs.setstate(ios::failbit);
    }
    parsed.first = stackDist;
    parsed.second = pdf_value;
}

void StackDistanceGen::CreateCdfStorage()
{
    double sum = 0;
    for(auto& pdf_pair : _pdf_storage)
    {
        sum += pdf_pair.second;
        _cdf_storage.insert(pair<double, StackDist>(sum, pdf_pair.first));
    }
}

double StackDistanceGen::WritePairsToFile(const string& path)
{
    int count = 0;
    // Write "stack_dist/hit_rate" files for every application unit
    for (PairStorage::iterator it = _experimental_pdf.begin(); it != _experimental_pdf.end(); ++it)
    {
        double value = it->second / static_cast<double>(_exp_counter);
        Utils::AppendToFile(path, it->first, value);
        count++;
    }
}