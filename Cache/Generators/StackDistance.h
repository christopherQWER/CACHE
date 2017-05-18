//
// Created by cat on 4/20/17.
//

#pragma once
#include <fstream>
#include <sstream>
#include <map>
#include "../Utils/Types.h"
#include "RandomValue.h"
typedef std::map<StackDist, double> PairStorage;

class StackDistance : public RandomValue {
public:
    /// \brief              Load's pdf histogram values from text file
    ///                     in format:
    ///                         1    0,2
    ///                         3    0,4
    ///                           ...
    ///                     and initializes pdf storage.
    /// \param pdf_file
    StackDistance(const std::string& pdf_file);
    ~StackDistance();

    StackDist GetRandomValue();

    /// \brief              Write stack distance-probability pairs to text file
    /// \param output_path
    /// \return
    double WritePairsToFile(const std::string& output_path);

private:
    PairStorage _pdf_storage;
    std::map<double, StackDist> _cdf_storage;

    PairStorage _experimental_pdf;
    ByteSize _exp_counter;

    /// \brief
    /// \param line_to_parse
    /// \return
    std::pair<StackDist, double> ParsePairs(const std::string& line_to_parse);

    /// \brief              Function creates cdf storage from values in
    ///                     pdf storage
    void CreateCdfStorage();
};