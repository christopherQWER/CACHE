//
// Created by cat on 4/3/17.
//
#pragma once
#include <iostream>
#include "../Utils/Types.h"
#include "MainConfig.h"
#include "../Libs/pugixml.hpp"

struct AppInfo
{
    int reads;
    int writes;
    ByteSize avg_req_size;
    ByteSize req_num;
    Asu unit;
    AppInfo() : reads(0), writes(0), avg_req_size(0), req_num(0), unit(0) {}
};

struct TraceInfo
{
    /// Trace file path
    std::string input_file;
    /// File with analyzer results
    std::string output_file;
    /// Number of trace strings in file
    ByteSize length;
    std::list<AppInfo> apps;
    TraceInfo() : input_file(std::string("")), output_file(std::string("")), length(0), apps() {}
};

static const std::string sTraceFile = "TraceFile";
static const std::string sTracePath = "TracePath";
static const std::string sOutPath = "OutputPath";
static const std::string sLength = "Length";

static const std::string sApp = "App";
static const std::string sUnit = "Unit";
static const std::string sReads = "Reads";
static const std::string sWrites = "Writes";
static const std::string sAvgBytes = "AvgBytes";
static const std::string sReqNum = "RequestNumber";


class AnalyzeConfig : MainConfig{
public:
    static void Serialize(const TraceInfo &trace_info, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, TraceInfo &trace_info);
};