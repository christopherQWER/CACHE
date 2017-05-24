//
// Created by cat on 2/19/17.
//

#pragma once
#include <iostream>
#include <string>
#include "../Libs/pugixml.hpp"
#include "../Loggers/Logger.h"
#include "../Flows/Flow.h"
#include "../Utils/Types.h"

struct XmlLog {
    LoggerType logger_type;
    std::string path_to_log;
    XmlLog() : logger_type(LCONSOLE), path_to_log(std::string("")){}
};

struct XmlFlow {
    FlowType flow_type;
    int app_count;
    std::string path_to_flow;
    XmlFlow() : flow_type(FFILE),
                app_count(0),
                path_to_flow(std::string("")) {}
};

struct Config {
    std::string simulate_path;
    std::string generate_path;
    std::string analyze_path;
    Config() : simulate_path(std::string("")),
               generate_path(std::string("")),
               analyze_path(std::string("")){}
};

static const std::string Modes = "Modes";

static const std::string sApplication = "App";
static const std::string sAppCount = "AppCount";
static const std::string sLogs = "Logs";
static const std::string sFlow = "Flow";

static const std::string sName = "Name";
static const std::string sType = "Type";
static const std::string sRequestNum = "RequestNum";

static const std::string sXmlAsu = "Asu";
static const std::string sQoS = "QoS";

static const std::string sSimulate = "Simulate";
static const std::string sGenerate = "Generate";
static const std::string sAnalyzerMode = "Analyze";

class MainConfig {
public:

    static void Serialize(const Config &cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, Config &cnf);

    static void SerializeLogger(const XmlLog& logger, pugi::xml_node& root_node);
    static void DeserializeLogger(const pugi::xml_node &root_node, XmlLog &logger);

    static void SerializeFlow(const XmlFlow& flow, pugi::xml_node& root_node);
    static void DeserializeFlow(const pugi::xml_node &root_node, XmlFlow &flow);

    static void LoadFromFile(const std::string &file_name, pugi::xml_document &doc);
    static void SaveToFile(const pugi::xml_document &doc, const std::string &file_name);
};