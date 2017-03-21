//
// Created by cat on 2/19/17.
//
#include "XmlConfig.h"
using namespace std;

void XmlConfig::Serialize(const Config &cnf, pugi::xml_document &doc)
{
    // create root "Modes"
    pugi::xml_node modes_node = doc.append_child(Modes.c_str());

    // create child "TraceAnalyzer"
    pugi::xml_node trace_analyze_node = modes_node.append_child(XmlTraceAnalyzer.c_str());
    trace_analyze_node.append_attribute(StatType.c_str()).set_value(TraceAnalyzer::toString(cnf.trace_analyzer.type));

    // create children of "TraceAnalyzer"
    for (auto &trace : cnf.trace_analyzer.trace_list)
    {
        pugi::xml_node trace_node = trace_analyze_node.append_child(XmlTrace.c_str());
        trace_node.append_attribute(Name.c_str()).set_value(trace.name.c_str());
        trace_node.set_value(trace.path.c_str());
    }

    // create child "SharedCache"
    pugi::xml_node shared_node = modes_node.append_child(XmlSharedCache.c_str());
    shared_node.append_attribute(Size.c_str()).set_value(cnf.shared_cache.size);
    shared_node.append_attribute(RequestNum.c_str()).set_value(cnf.shared_cache.request_num);
    pugi::xml_node logger_node = shared_node.append_child(XmlLogs.c_str());
    logger_node.set_value(Logger::toString(cnf.shared_cache.logger_type));
    pugi::xml_node flow_node = shared_node.append_child(XmlFlow.c_str());
    flow_node.set_value(Flow::toString(cnf.shared_cache.flow_type));

    // create child "PartialCache"
    pugi::xml_node partial_node = modes_node.append_child(XmlPartialCache.c_str());
    partial_node.append_attribute(AppCount.c_str()).set_value(cnf.partial_cache.app_count);
    partial_node.append_attribute(CommonSize.c_str()).set_value((unsigned long)cnf.partial_cache.common_size);

    // create children of "PartialCache"
    for (auto &cache : cnf.partial_cache.cache_list)
    {
        pugi::xml_node cache_node = partial_node.append_child(XmlCache.c_str());
        cache_node.append_attribute(Size.c_str()).set_value(cache.size);
        cache_node.append_attribute(XmlAsu.c_str()).set_value(cache.asu);
        cache_node.append_attribute(XmlHitRate.c_str()).set_value(cache.hit_rate);
        cache_node.append_attribute(RequestNum.c_str()).set_value(cache.request_num);

        pugi::xml_node logger_node = cache_node.append_child(XmlLogs.c_str());
        logger_node.set_value(Logger::toString(cache.logger_type));
        pugi::xml_node flow_node = cache_node.append_child(XmlFlow.c_str());
        flow_node.set_value(Flow::toString(cache.flow_type));
    }
}

void XmlConfig::Deserialize(const pugi::xml_document &doc, Config &cnf)
{
    // get trace analyzer info
    pugi::xml_node trace_analyzer = doc.child(XmlTraceAnalyzer.c_str());
    cnf.trace_analyzer.type = (AnalyzerType)trace_analyzer.attribute(StatType.c_str()).as_int(1);

    // get trace analyzer children
    for (auto &trace : trace_analyzer.children(XmlTrace.c_str()))
    {
        struct XmlTrace trace_obj;
        trace_obj.name = trace.attribute(Name.c_str()).as_string("");
        trace_obj.path = trace.value();
        cnf.trace_analyzer.trace_list.push_back(trace_obj);
    }

    // get shared cache info
    pugi::xml_node shared_cache = doc.child(XmlSharedCache.c_str());
    cnf.shared_cache.size = shared_cache.attribute(Size.c_str()).as_double(1);
    cnf.shared_cache.request_num = shared_cache.attribute(RequestNum.c_str()).as_int(1000000);
    cnf.shared_cache.logger_type = (LoggerType)shared_cache.append_attribute(RequestNum.c_str()).as_int(LCONSOLE);
    cnf.shared_cache.flow_type = (FlowType)shared_cache.append_attribute(XmlLogs.c_str()).as_int(FFILE);

    // get partial cache info
    pugi::xml_node partial_cache = doc.child(XmlPartialCache.c_str());
    cnf.partial_cache.app_count = partial_cache.attribute(AppCount.c_str()).as_int(0);
    cnf.partial_cache.common_size = (ByteSize)partial_cache.attribute(CommonSize.c_str()).as_int(1);

    // get partial cache children
    for (auto &cache : partial_cache.children(XmlCache.c_str()))
    {
        struct XmlCache cache_obj;
        cache_obj.asu = cache.attribute(XmlAsu.c_str()).as_uint(0);
        cache_obj.size = cache.attribute(Size.c_str()).as_double(1);
        cache_obj.hit_rate = cache.attribute(XmlHitRate.c_str()).as_double(0.2);
        cache_obj.request_num = cache.attribute(RequestNum.c_str()).as_int(1000000);
        cache_obj.logger_type = (LoggerType)shared_cache.append_attribute(RequestNum.c_str()).as_int(LCONSOLE);
        cache_obj.flow_type = (FlowType)shared_cache.append_attribute(XmlLogs.c_str()).as_int(FFILE);
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