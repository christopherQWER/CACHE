//
// Created by cat on 2/19/17.
//

#pragma once
#include <iostream>
#include <string>
#include "pugixml.hpp"

#include "../Loggers/Logger.h"
#include "../Flows/Flow.h"
#include "../Utils/Types.h"
#include "../Modeling/TraceAnalyzer.h"

struct XmlTrace{
    std::string name;
    std::string path;
    XmlTrace() : name(std::string("")), path(std::string("")) {}
};

struct XmlTraceAnalyze {
    AnalyzerType type;
    std::list<XmlTrace> trace_list;
    XmlTraceAnalyze() : type(DETAILED), trace_list() {}
};

struct XmlSharedCache {
    double size;
    int request_num;
    LoggerType logger_type;
    FlowType flow_type;
    XmlSharedCache() : size(0), request_num(0), logger_type(LCONSOLE), flow_type(FFILE) {}
};

struct XmlCache {
    double size;
    int request_num;
    Asu asu;
    double hit_rate;
    LoggerType logger_type;
    FlowType flow_type;
    XmlCache() : size(0), request_num(0), asu(0), hit_rate(0), logger_type(LCONSOLE), flow_type(FFILE) {}
};

struct XmlPartialCache {
    int app_count;
    ByteSize common_size;
    std::list<XmlCache> cache_list;
    XmlPartialCache() : app_count(0), common_size(0), cache_list() {}
};

struct Config {
    XmlTraceAnalyze trace_analyzer;
    XmlSharedCache shared_cache;
    XmlPartialCache partial_cache;
    Config() :  trace_analyzer(), shared_cache(), partial_cache() {}
};

static const std::string Modes = "Modes";

static const std::string XmlTraceAnalyzer = "TraceAnalyzer";
static const std::string XmlSharedCache = "SharedCache";
static const std::string XmlPartialCache = "StaticPartial";

static const std::string XmlTrace = "Trace";
static const std::string XmlCache = "Cache";
static const std::string XmlLogs = "Logs";
static const std::string XmlFlow = "Flow";

static const std::string Name = "Name";
static const std::string StatType = "StatType";
static const std::string Size = "Size";
static const std::string RequestNum = "RequestNum";
static const std::string AppCount = "AppCount";
static const std::string CommonSize = "CommonSize";
static const std::string XmlAsu = "Asu";
static const std::string XmlHitRate = "HitRate";

class XmlConfig {
public:

     /// \brief Serialize object Config to xml document object
     /// \param cnf [Input config]
     /// \param doc [Object container]
    static void Serialize(const Config &cnf, pugi::xml_document &doc);

    /// \brief  Deserialize xml-document to Config object
    /// \param doc []
    /// \param cnf []
    static void Deserialize(const pugi::xml_document &doc, Config &cnf);

    /// \brief
    /// \param file_name []
    /// \param doc []
    static void LoadFromFile(const std::string &file_name, pugi::xml_document &doc);

    /// \brief
    /// \param doc []
    /// \param file_name []
    static void SaveToFile(const pugi::xml_document &doc, const std::string &file_name);
};