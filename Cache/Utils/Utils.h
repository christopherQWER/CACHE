//
// Created by cat on 10/2/16.
//
#pragma once
#ifndef CACHE_UTILS_H
#define CACHE_UTILS_H

#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <sys/stat.h>
class Utils
{
public:

    //static void OpenFile(const std::string file_path);
    static void AppendToFile(const std::string &output_path, int i_var, double d_var);
    static void AppendToFile(const std::string &output_path, const std::string &text);
    static int DoubleToInt(double d_input);

    template<typename First, typename... Rest>
    std::string PathCombine(const First& first, const Rest&... rest)
    {
        std::string result_str = "//";
        result_str.append(first);
        result_str.append("//");
        return PathCombine(rest...);
    }
    static std::string GetCurrentUnixTime();
    static std::string GetFileName(const std::string &path);
    static std::string GetFileNameWithoutExt(const std::string &path);

    static bool CreateDirectory(const std::string &dir_path);
};


#endif //CACHE_UTILS_H
