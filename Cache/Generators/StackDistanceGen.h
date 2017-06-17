//
// Created by cat on 4/20/17.
//

#pragma once
#include <fstream>
#include <sstream>
#include <map>
#include "../Utils/Types.h"
#include "RandomValue.h"
#include "UniformReal.h"


class StackDistanceGen : public RandomValue {
public:
    /// \brief              Load's pdf histogram values from text file
    ///                     in format:
    ///                         1    0,2
    ///                         3    0,4
    ///                           ...
    ///                     and initializes pdf storage.
    /// \param pdf_file
    StackDistanceGen(const std::string& pdf_file);
    ~StackDistanceGen();

    StackDist GetRandomValue();

    /// \brief              Write stack distance-probability pairs to text file
    /// \param output_path
    /// \return
    double WritePairsToFile(const std::string& output_path);

private:
    UniformReal* uniform_real_gen;

    PairStorage _pdf_storage;
    ProportionalMap _cdf_storage;

    PairStorage _experimental_pdf;
    ByteSize _exp_counter;

    /// \brief
    /// \param line_to_parse
    /// \return
    std::pair<StackDist, double> ParsePairs(const std::string& line_to_parse);

    /// \brief              Function creates cdf storage from values in
    ///                     pdf storage
    void CreateCdfStorage();

    std::map<double, long double>::iterator CustomLowerBound(double uniformNumber);
};