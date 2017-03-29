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
    pugi::xml_node trace_analyze_node = modes_node.append_child(sTraceAnalyzer.c_str());
    trace_analyze_node.append_attribute(sStatType.c_str()).set_value(TraceAnalyzer::toString(cnf.trace_analyzer.type));

    // create children of "TraceAnalyzer"
    for (auto &trace : cnf.trace_analyzer.trace_list)
    {
        pugi::xml_node trace_node = trace_analyze_node.append_child(sTrace.c_str());
        trace_node.append_attribute(sName.c_str()).set_value(trace.name.c_str());
        trace_node.set_value(trace.path.c_str());
    }

    // create child "SharedCache"
    pugi::xml_node shared_node = modes_node.append_child(sSharedCache.c_str());
    shared_node.append_attribute(sSize.c_str()).set_value(cnf.shared_cache.size);
    shared_node.append_attribute(sRequestNum.c_str()).set_value(cnf.shared_cache.request_num);
    pugi::xml_node logger_node = shared_node.append_child(sLogs.c_str());
    logger_node.set_value(Logger::toString(cnf.shared_cache.logger_type));
    pugi::xml_node flow_node = shared_node.append_child(sFlow.c_str());
    flow_node.set_value(Flow::toString(cnf.shared_cache.flow_type));

    // create child "StaticPartial"
    pugi::xml_node partial_node = modes_node.append_child(sPartialCache.c_str());
    partial_node.append_attribute(sAppCount.c_str()).set_value(cnf.partial_cache.app_count);
    partial_node.append_attribute(sCommonSize.c_str()).set_value((unsigned long)cnf.partial_cache.common_size);

    // create children of "StaticPartial"
    for (auto &cache : cnf.partial_cache.cache_list)
    {
        pugi::xml_node cache_node = partial_node.append_child(sCache.c_str());
        cache_node.append_attribute(sSize.c_str()).set_value(cache.size);
        cache_node.append_attribute(sXmlAsu.c_str()).set_value(cache.asu);
        cache_node.append_attribute(sXmlHitRate.c_str()).set_value(cache.hit_rate);
        cache_node.append_attribute(sRequestNum.c_str()).set_value(cache.request_num);

        pugi::xml_node logger_node = cache_node.append_child(sLogs.c_str());
        logger_node.set_value(Logger::toString(cache.logger_type));
        pugi::xml_node flow_node = cache_node.append_child(sFlow.c_str());
        flow_node.set_value(Flow::toString(cache.flow_type));
    }
}

void XmlConfig::Deserialize(const pugi::xml_document &doc, Config &cnf)
{
    pugi::xml_node modes = doc.child(Modes.c_str());

    // get trace analyzer info
    pugi::xml_node trace_analyzer = modes.child(sTraceAnalyzer.c_str());
    cnf.trace_analyzer.type = static_cast<AnalyzerType>(trace_analyzer.attribute(sStatType.c_str()).as_int(1));

    // get trace analyzer children
    for (pugi::xml_node child = trace_analyzer.child(sTrace.c_str()); child; child = child.next_sibling(sTrace.c_str()))
    {
        XmlTrace trace_obj = XmlTrace();
        trace_obj.name = string(child.attribute(sName.c_str()).as_string(""));
        trace_obj.path = string(child.child_value());
        cnf.trace_analyzer.trace_list.push_back(trace_obj);
    }

    // get shared cache info
    pugi::xml_node shared_cache = doc.child(sSharedCache.c_str());
    cnf.shared_cache.size = shared_cache.attribute(sSize.c_str()).as_double(1);
    cnf.shared_cache.request_num = shared_cache.attribute(sRequestNum.c_str()).as_int(1000000);
    cnf.shared_cache.logger_type = (LoggerType)shared_cache.append_attribute(sRequestNum.c_str()).as_int(LCONSOLE);
    cnf.shared_cache.flow_type = (FlowType)shared_cache.append_attribute(sLogs.c_str()).as_int(FFILE);

    // get partial cache info
    pugi::xml_node partial_cache = doc.child(sPartialCache.c_str());
    cnf.partial_cache.app_count = partial_cache.attribute(sAppCount.c_str()).as_int(0);
    cnf.partial_cache.common_size = (ByteSize)partial_cache.attribute(sCommonSize.c_str()).as_int(1);

    // get partial cache children
    for (pugi::xml_node child = partial_cache.child(sCache.c_str()); child; child = child.next_sibling(sCache.c_str()))
    {
        XmlCache cache_obj = XmlCache();
        cache_obj.asu = child.attribute(sXmlAsu.c_str()).as_uint(0);
        cache_obj.size = child.attribute(sSize.c_str()).as_double(1);
        cache_obj.hit_rate = child.attribute(sXmlHitRate.c_str()).as_double(0.2);
        cache_obj.request_num = child.attribute(sRequestNum.c_str()).as_int(1000000);
        cache_obj.logger_type = (LoggerType)shared_cache.append_attribute(sRequestNum.c_str()).as_int(LCONSOLE);
        cache_obj.flow_type = (FlowType)shared_cache.append_attribute(sLogs.c_str()).as_int(FFILE);
        cnf.partial_cache.cache_list.push_back(cache_obj);
    }
}

//From trace_file
void XmlConfig::LoadFromFile(const std::string &file_name, pugi::xml_document &doc)
{
    pugi::xml_parse_result result = doc.load_file(file_name.c_str());
    if (result)
    {
        std::cout << "XML [" << file_name << "] parsed without errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n\n";
    }
    else
    {
        std::cout << "XML [" << file_name << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (file_name.c_str() + result.offset) << "]\n\n";
    }
}

//To trace_file
void XmlConfig::SaveToFile(const pugi::xml_document &doc, const std::string &file_name)
{
    bool saveSucceeded = doc.save_file(file_name.c_str());
}