//
// Created by cat on 4/20/17.
//

#include "StackDistanceGen.h"
#include "../Utils/Utils.h"
using namespace std;

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
    CreateCdfStorage();
    uniform_real_gen = new UniformReal(0.0, 1.0);
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
    if (uniform_real_gen != NULL)
    {
        delete uniform_real_gen;
    }
}

ProportionalMap::iterator StackDistanceGen::CustomLowerBound(double uniformNumber )
{
    ProportionalMap::iterator prev = _cdf_storage.end();

    for( ProportionalMap::iterator it = _cdf_storage.begin();
            it != _cdf_storage.end(); prev = it, ++it )
    {
        if ( uniformNumber >= prev->first && uniformNumber < it->first )
        {
            break;
        }
    }

    return prev;
}

StackDist StackDistanceGen::GetRandomValue()
{
    double uniform_number = 0;
    while (uniform_number < _cdf_storage.begin()->first)
    {
        uniform_number = uniform_real_gen->GetRandom();
    }

    ProportionalMap::iterator it = CustomLowerBound( uniform_number );
    if (it != _cdf_storage.end())
    {
        // Shit for test =========================================================
        if (_experimental_pdf.find(it->second) != _experimental_pdf.end())
        {
            _experimental_pdf[it->second]++;
        }
        else
        {
            _experimental_pdf.insert(pair<StackDist, double>(it->second, 1));
        }
        _exp_counter++;
        // =======================================================================
        return it->second;
    }
    ProportionalMap::reverse_iterator it_rev = _cdf_storage.rbegin();
    return it_rev->second;
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
    return  parsed;
}

void StackDistanceGen::CreateCdfStorage()
{
    double sum = 0;

    for(auto& pdf_pair : _pdf_storage)
    {
        sum += pdf_pair.second;
        _cdf_storage.insert(pair<double, StackDist>(sum, pdf_pair.first));
        Utils::AppendToFile("//home//cat//Documents//CACHE//Inputs//Flows//Uniform_CDF.txt",
                sum, pdf_pair.first);
    }
}

double StackDistanceGen::WritePairsToFile(const string& path)
{
    // Write "stack_dist/hit_rate" files for every application unit
    for (PairStorage::iterator it = _experimental_pdf.begin(); it != _experimental_pdf.end(); ++it)
    {
        double value = it->second / static_cast<double>(_exp_counter);
        Utils::AppendToFile(path, it->first, value);
    }
}