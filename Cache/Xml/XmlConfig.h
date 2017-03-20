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

struct XmlSharedCache {
    double size;
    int request_num;
    Type logger_type;
    FlowType flow_type;
};

struct XmlCache {
    double size;
    int request_num;
    Asu asu;
    double hit_rate;
    Type logger_type;
    FlowType flow_type;
};

struct XmlPartialCache {
    int app_count;
    ByteSize common_size;
    std::list<XmlCache> cache_list;
};

struct Config {
    XmlSharedCache shared_cache;
    XmlPartialCache partial_cache;
};

static const std::string Model = "Model";
static const std::string XmlSharedCache = "SharedCache";
static const std::string PartialCache = "PartialCache";
static const std::string XmlCache = "Cache";
static const std::string XmlLogs = "Logs";
static const std::string XmlFlow = "Flow";
static const std::string Size = "Size";
static const std::string RequestNum = "RequestNum";
static const std::string AppCount = "AppCount";
static const std::string CommonSize = "CommonSize";
static const std::string XmlAsu = "Asu";
static const std::string XmlHitRate = "HitRate";

class XmlConfig {
public:

     /// [Serialization and deserialization from/to object]
     /// \param cnf [Input config]
     /// \param doc [Object container]
    static void Serialize(const Config &cnf, pugi::xml_document &doc);

    ///
    /// \param doc []
    /// \param cnf []
    static void Deserialize(const pugi::xml_document &doc, Config &cnf);

    ///
    /// \param file_name []
    /// \param doc []
    static void LoadFromFile(const std::string &file_name, pugi::xml_document &doc);

    ///
    /// \param doc []
    /// \param file_name []
    static void SaveToFile(const pugi::xml_document &doc, const std::string &file_name);
};