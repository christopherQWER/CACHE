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
#include "Types.h"

class Utils
{
public:

    //static void OpenFile(const std::string file_path);
    template<typename T1, typename T2>
    static void AppendToFile(const std::string &output_path, T1 i_var, T2 d_var)
    {
        std::ofstream density_file;
        density_file.open(output_path.c_str(), std::fstream::out | std::fstream::app);

        density_file << std::to_string(i_var);
        density_file << "\t";
        density_file << std::to_string(d_var);
        density_file << "\n";

        density_file.close();
    }

    static void AppendToFile(const std::string& output_path, const std::string &text);
    static void WriteLines(const std::string& output_path, std::vector<std::string> &lines);
    static void ExecuteCmd(const std::string& input);
    static int DoubleToInt(double d_input);
    //static std::string PathCombine(const char *fmt, const char* ...);
    template<typename T>
    static T PathCombine(T v)
    {
        return v;
    }
    template<typename T, typename... Args>
    static T PathCombine(T first, Args... args)
    {
        return first + "//" + PathCombine(args...);
    }
    template<typename T>
    static std::string convert(T _input)
    {
        std::stringstream blah;
        blah << _input;
        return blah.str();
    }
    static std::string GetCurrentStringUnixTime();
    static std::string GetWorkingDirectory();
    static std::string GetFileName(const std::string &path);
    static std::string GetFileNameWithoutExt(const std::string &path);
    static bool CreateDirectory(const std::string &dir_path);
    static std::string GetDirectoryNameFromPath(const std::string &file_path);
    static double GetPointByTwoPoints(ByteSize x1, double y1, ByteSize x2, double y2, ByteSize x3);
};