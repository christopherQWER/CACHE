//
// Created by cat on 12/13/16.
//

#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../Libs/pugixml.hpp"
#include "../Utils/Types.h"
#include "../Xml/AnalyzeConfig.h"

enum AnalyzerType{COMMON = 0, DETAILED, ALL, ANALYZE_LOG};

class TraceAnalyzer {
public:
    TraceAnalyzer(const std::string &file_path, std::string &output_file);
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
            case ANALYZE_LOG:  return "ANALYZE_LOG";
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
        else if (strcmp(str_repr, "ANALYZE_LOG") == 0)
            return ANALYZE_LOG;
    }

private:
    int _reads;
    int _writes;
    ByteSize _avg_req_size;
    ByteSize _line_num;

    std::ifstream _trace_stream;
    std::string _input_file;
    std::string _output_file;

    void AppendToFile(const std::string& output_path);
};