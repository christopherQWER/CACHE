//
// Created by cat on 2/19/17.
//

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H
#include "pugixml.hpp"
#include "Serializible.h"
#include "../Loggers/Logger.h"
#include "../Flows/Flow.h"


class SharedCache : public Serializable<pugi::xml_node>
{
public:
    double Size = 1;
    int RequestNum = 1000000;
    std::map<std::string, std::string> innerTags;

    SharedCache()
    {
        innerTags["Logs"] = Logger::toString(LCONSOLE);
        innerTags["Flow"] = Flow::toString(FFILE);
    }

private:
    serialize(Size);
    serialize(RequestNum);
    serialize(innerTags);
};

class PartitionedCache : public Serializable<pugi::xml_node>
{
public:
    int AppCount = 5;
    int CommonSize = 1;
    std::list<Cache> cachesList;
};

class Cache : public Serializable<pugi::xml_node>
{
public:
    double Size = 1;
    Asu asu = 0;
    HitRate hitRate = 0.2;
    int RequestNum = 1000000;
    std::map<std::string, std::string> innerTags;

    Cache()
    {
        innerTags["Logs"] = Logger::toString(LCONSOLE);
        innerTags["Flow"] = Flow::toString(FFILE);
    }
};

class Config : public Serializable<pugi::xml_node>
{
public:
    SharedCache ShareCache;
    PartitionedCache PartCache;
};


#endif //PROJECT_CONFIG_H
