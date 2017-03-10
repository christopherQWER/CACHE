//
// Created by cat on 2/19/17.
//

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H
#include "pugixml.hpp"
#include "../Loggers/Logger.h"
#include "../Flows/Flow.h"
#include "../Utils/Types.h"

struct XmlSharedCache {
    double size;
    int requestNum;
};

struct XmlCache{
    double size;
    int requestNum;
    Asu asu;
    double HitRate;
};

struct XmlPartialCache{
    int appCount;
    ByteSize CommonSize;
    std::list<XmlCache> cacheList;
};

struct Config{
    XmlSharedCache sharedCache;
    XmlPartialCache partialCache;
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

    /**
     * [Serialization and deserialization from/to object]
     * @param cnf [Input config]
     * @param obj [Object container]
     */
    void Serialize(const Config &cnf, pugi::xml_document &doc);
    void Deserialize(const pugi::xml_document &doc, Config &cnf);

    void Serialize(const std::string &file_name, pugi::xml_document &doc);
    void Deserialize(const pugi::xml_document &doc, const std::string &file_name);
};

#endif //PROJECT_CONFIG_H
