//
// Created by cat on 12/13/16.
//

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../Xml/pugixml.hpp"
#include "Types.h"

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
    TraceAnalyzer(const std::string& input_file, const std::string& output_file);
    ~TraceAnalyzer();

    void GetCommonStat();
    void GetDetailedStat();

private:
    int _reads;
    int _writes;
    ByteSize _avg_req_size;
    ByteSize _line_num;
    std::ifstream _trace_stream;
    std::string _input_file;
    std::string _output_file;

    void AppendToFile(const std::string& output_path);
    void AppendToXml(const std::string& output_path, const std::map<Asu, AppInfo>& app_map);
};