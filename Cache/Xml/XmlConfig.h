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
    ByteSize size;
    int request_num;
    LoggerType logger_type;
    FlowType flow_type;
    XmlSharedCache() : size(0), request_num(0), logger_type(LCONSOLE), flow_type(FFILE) {}
};

struct XmlCache {
    ByteSize size;
    Asu asu;
    double hit_rate;
    LoggerType logger_type;
    FlowType flow_type;
    XmlCache() : size(0), asu(0), hit_rate(0), logger_type(LCONSOLE), flow_type(FFILE) {}
};

struct XmlPartialCache {
    int app_count;
    int request_num;
    ByteSize common_size;
    std::list<XmlCache> cache_list;
    XmlPartialCache() : app_count(0), request_num(0), common_size(0), cache_list(std::list<XmlCache>()) {}
};

struct Config {
    XmlTraceAnalyze trace_analyzer;
    XmlSharedCache shared_cache;
    XmlPartialCache partial_cache;
    Config() : trace_analyzer(XmlTraceAnalyze()), shared_cache(XmlSharedCache()), partial_cache(XmlPartialCache()) {}
};

static const std::string Modes = "Modes";

static const std::string sTraceAnalyzer = "TraceAnalyzer";
static const std::string sSharedCache = "SharedCache";
static const std::string sPartialCache = "PartialCache";

static const std::string sTrace = "Trace";
static const std::string sCache = "Cache";
static const std::string sLogs = "Logs";
static const std::string sFlow = "Flow";

static const std::string sName = "Name";
static const std::string sStatType = "StatType";
static const std::string sSize = "Size";
static const std::string sRequestNum = "RequestNum";
static const std::string sAppCount = "AppCount";
static const std::string sCommonSize = "CommonSize";
static const std::string sXmlAsu = "Asu";
static const std::string sXmlHitRate = "HitRate";

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