//
// Created by cat on 12/13/16.
//
#pragma once
#ifndef _TRACE_ANALYZER_H
#define _TRACE_ANALYZER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Types.h"
#include "../Generators/Request.h"
#include "../../Tests/Paths.h"


class TraceAnalyzer {
public:
    TraceAnalyzer();
    TraceAnalyzer(const std::string& file_path);
    ~TraceAnalyzer();

    void GetStat();
    void AppendToFile(const std::string& output_path);

private:
    int _reads;
    int _writes;
    ByteSize _avg_req_size;
    ByteSize _line_num;
    std::ifstream _trace_file;
};


#endif //_TRACE_ANALYZER_H
