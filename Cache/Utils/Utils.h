//
// Created by cat on 10/2/16.
//

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include <sys/stat.h>


class Utils
{
public:

    //static void OpenFile(const std::string file_path);
    template<typename T1, typename T2>
    static void AppendToFile(const std::string &output_path, T1 i_var, T2 d_var)
    {
        std::ofstream density_file;
        density_file.open(output_path.c_str(), std::fstream::out | std::fstream::app);

        density_file << i_var;
        density_file << "\t";
        density_file << d_var;
        density_file << "\n";

        density_file.close();
    }
    static void AppendToFile(const std::string &output_path, const std::string &text);
    static void WriteLines(const std::string &output_path, std::vector<std::string> &lines);
    static void ExecuteCmd(const std::string &input);
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
    static std::string SplitFilename (const std::string& str);
};