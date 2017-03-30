//
// Created by cat on 12/13/16.
//

#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../Xml/pugixml.hpp"
#include "../Utils/Types.h"

///
enum AnalyzerType{COMMON = 0, DETAILED, ALL};

///
struct AppInfo
{
    int reads;
    int writes;
    ByteSize avg_req_size;
    ByteSize line_num;
    AppInfo() : reads(0), writes(0), avg_req_size(0), line_num(0) {}
};

class TraceAnalyzer {
public:
    /// \brief [Constructor]
    /// \param input_file []
    /// \param output_file []
    TraceAnalyzer(const std::string file_path, std::string output_file);
    ~TraceAnalyzer();

    void GetCommonStat();
    void GetDetailedStat();

    static inline const char* toString(AnalyzerType stat_type)
    {
        switch (stat_type)
        {
            case COMMON:       return "COMMON";
            case DETAILED:     return "DETAILED";
            case ALL:          return "ALL";
            default:           return "UNKNOWN";
        }
    }

    static inline AnalyzerType toType(const char* str_repr)
    {
        if (strcmp(str_repr, "COMMON") == 0)
            return COMMON;
        else if (strcmp(str_repr, "DETAILED") == 0)
            return DETAILED;
        else if (strcmp(str_repr, "ALL") == 0)
            return ALL;
    }

private:
    int _reads;
    int _writes;
    ByteSize _avg_req_size;
    ByteSize _line_num;
    std::ifstream _trace_stream;
    std::string _input_file;
    std::string _output_file;

    /// \brief []
    /// \param output_path []
    void AppendToFile(const std::string& output_path);

    /// \brief []
    /// \param output_path []
    /// \param app_map []
    void AppendToXml(const std::string& output_path, const std::map<Asu, AppInfo>& app_map);
};