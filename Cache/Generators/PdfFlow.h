//
// Created by cat on 4/20/17.
//

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <map>
#include "../Utils/Types.h"
typedef std::map<StackDist, double> PairStorage;

class PdfFlow {
public:
    PdfFlow();
    PdfFlow(const std::string& pdf_file);
    ~PdfFlow();

    StackDist GetRandom();

private:
    PairStorage _pdf_storage;
    std::map<double, StackDist> _cdf_storage;

    void ParsePairs(const std::string& line_to_parse);
    void GetCdfByPdf();
};