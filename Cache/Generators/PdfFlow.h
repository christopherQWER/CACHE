//
// Created by cat on 4/20/17.
//

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "../Utils/Types.h"
#include "Distribution.h"
typedef std::map<StackDist, double> PairStorage;

class PdfFlow : public Distribution{
public:
    PdfFlow();
    PdfFlow(const std::string& pdf_file);
    ~PdfFlow();

    StackDist GetRandomValue();
    double GetPdf(const std::string &path);

private:
    PairStorage _pdf_storage;
    std::map<double, StackDist> _cdf_storage;
    PairStorage _experimental_pdf;
    ByteSize _exp_counter;

    void ParsePairs(const std::string& line_to_parse);
    void GetCdfByPdf();
};