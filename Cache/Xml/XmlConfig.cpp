//
// Created by cat on 2/19/17.
//
#include "XmlConfig.h"
using namespace std;

void XmlConfig::Serialize(const Config &cnf, pugi::xml_document &doc)
{
    pugi::xml_node modelNode = doc.append_child(Model.c_str());

    pugi::xml_node sharedNode = modelNode.append_child(XmlSharedCache.c_str());
    sharedNode.append_attribute(Size.c_str()).set_value(cnf.shared_cache.size);
    sharedNode.append_attribute(RequestNum.c_str()).set_value(cnf.shared_cache.request_num);
    pugi::xml_node loggerNode = sharedNode.append_child(XmlLogs.c_str());
    loggerNode.set_value(Logger::toString(cnf.shared_cache.logger_type));
    pugi::xml_node flowNode = sharedNode.append_child(XmlFlow.c_str());
    flowNode.set_value(Flow::toString(cnf.shared_cache.flow_type));

    pugi::xml_node partialNode = modelNode.append_child(PartialCache.c_str());
    partialNode.append_attribute(AppCount.c_str()).set_value(cnf.partial_cache.app_count);
    partialNode.append_attribute(CommonSize.c_str()).set_value((unsigned long)cnf.partial_cache.common_size);

    for (auto &cache : cnf.partial_cache.cache_list)
    {
        pugi::xml_node cacheNode = partialNode.append_child(XmlCache.c_str());
        cacheNode.append_attribute(Size.c_str()).set_value(cache.size);
        cacheNode.append_attribute(XmlAsu.c_str()).set_value(cache.asu);
        cacheNode.append_attribute(XmlHitRate.c_str()).set_value(cache.hit_rate);
        cacheNode.append_attribute(RequestNum.c_str()).set_value(cache.request_num);

        pugi::xml_node loggerNode = cacheNode.append_child(XmlLogs.c_str());
        loggerNode.set_value(Logger::toString(cache.logger_type));
        pugi::xml_node flowNode = cacheNode.append_child(XmlFlow.c_str());
        flowNode.set_value(Flow::toString(cache.flow_type));
    }
}

void XmlConfig::Deserialize(const pugi::xml_document &doc, Config &cnf)
{
    pugi::xml_node sharedCache = doc.child(XmlSharedCache.c_str());
    cnf.shared_cache.size = sharedCache.attribute(Size.c_str()).as_double(1);
    cnf.shared_cache.request_num = sharedCache.attribute(RequestNum.c_str()).as_int(1000000);
    cnf.shared_cache.logger_type = (Type)sharedCache.append_attribute(RequestNum.c_str()).as_int(LCONSOLE);
    cnf.shared_cache.flow_type = (FlowType)sharedCache.append_attribute(XmlLogs.c_str()).as_int(FFILE);

    pugi::xml_node partial_cache = doc.child(PartialCache.c_str());
    cnf.partial_cache.app_count = partial_cache.attribute(AppCount.c_str()).as_int(0);
    cnf.partial_cache.common_size = (ByteSize)partial_cache.attribute(CommonSize.c_str()).as_int(1);

    for (auto &cache : partial_cache.children(XmlCache.c_str()))
    {
        struct XmlCache cache_obj;
        cache_obj.asu = cache.attribute(XmlAsu.c_str()).as_uint(0);
        cache_obj.size = cache.attribute(Size.c_str()).as_double(1);
        cache_obj.hit_rate = cache.attribute(XmlHitRate.c_str()).as_double(0.2);
        cache_obj.request_num = cache.attribute(RequestNum.c_str()).as_int(1000000);
        cache_obj.logger_type = (Type)sharedCache.append_attribute(RequestNum.c_str()).as_int(LCONSOLE);
        cache_obj.flow_type = (FlowType)sharedCache.append_attribute(XmlLogs.c_str()).as_int(FFILE);
        cnf.partial_cache.cache_list.push_back(cache_obj);
    }
}

//From trace_file
void XmlConfig::LoadFromFile(const std::string &file_name, pugi::xml_document &doc)
{
    pugi::xml_parse_result result = doc.load_file(file_name.c_str());
}

//To trace_file
void XmlConfig::SaveToFile(const pugi::xml_document &doc, const std::string &file_name)
{
    bool saveSucceeded = doc.save_file(file_name.c_str());
}