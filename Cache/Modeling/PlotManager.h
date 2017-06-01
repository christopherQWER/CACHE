//
// Created by cat on 5/10/17.
//
#pragma once
#include <iostream>
#include <string>
#include "../Utils/Types.h"

class PlotManager {
public:
    void LoadCacheSizeVSHr(const std::string& file_path, std::map<ByteSize, double>& size_hr_map);
    void LoadPdfPlotDots(const std::string& file_path, ProportionalMap &pdf_map);
    void LoadCdfPlotDots(const std::string& file_path);

private:
    template<typename T1, typename T2>
    static bool GetPairFromString(const std::string& pdf_string, std::pair<T1, T2> &new_pair);
};