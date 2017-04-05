//
// Created by cat on 2/19/17.
//
#include "MainConfig.h"
using namespace std;

void MainConfig::Serialize(const Config &cnf, pugi::xml_document &doc)
{
    // create root "Modes"
    pugi::xml_node modes_node = doc.append_child(Modes.c_str());

    // create child "TraceAnalyzer"
    pugi::xml_node trace_analyze_node = modes_node.append_child(sTraceAnalyzer.c_str());
    trace_analyze_node.append_attribute(sType.c_str()).set_value(TraceAnalyzer::toString(cnf.trace_analyzer.type));

    // create children of "TraceAnalyzer"
    for (auto &trace : cnf.trace_analyzer.trace_list)
    {
        pugi::xml_node trace_node = trace_analyze_node.append_child(sTrace.c_str());
        trace_node.append_attribute(sName.c_str()).set_value(trace.name.c_str());
        trace_node.set_value(trace.path.c_str());
    }

    // create child "SharedCache"
    pugi::xml_node shared_node = modes_node.append_child(sSharedCache.c_str());
    shared_node.append_attribute(sSize.c_str()).set_value(static_cast<long unsigned int>(cnf.shared_cache.size));
    shared_node.append_attribute(sRequestNum.c_str()).set_value(cnf.shared_cache.request_num);

    // create logger tag
    pugi::xml_node logger_node = shared_node.append_child(sLogs.c_str());
    logger_node.append_attribute(sType.c_str()).set_value(Logger::toString(cnf.shared_cache.logger.logger_type));
    if (cnf.shared_cache.logger.logger_type == LCONSOLE)
    {
        logger_node.set_value(cnf.shared_cache.logger.path_to_log.c_str());
    }

    // create flow tag
    pugi::xml_node flow_node = shared_node.append_child(sFlow.c_str());
    flow_node.append_attribute(sType.c_str()).set_value(Flow::toString(cnf.shared_cache.flow.flow_type));
    if(cnf.shared_cache.flow.flow_type == FFILE)
    {
        flow_node.set_value(cnf.shared_cache.flow.path_to_flow.c_str());
    }

    // create child "StaticPartial"
    pugi::xml_node partial_node = modes_node.append_child(sPartialCache.c_str());
    partial_node.append_attribute(sAppCount.c_str()).set_value(static_cast<unsigned long>(cnf.partial_cache.app_count));
    partial_node.append_attribute(sCommonSize.c_str()).set_value(static_cast<unsigned long>(cnf.partial_cache.common_size));
    partial_node.append_attribute(sRequestNum.c_str()).set_value(static_cast<unsigned long>(cnf.partial_cache.request_num));

    // create logger tag
    pugi::xml_node logger_node_1 = partial_node.append_child(sLogs.c_str());
    logger_node_1.append_attribute(sType.c_str()).set_value(Logger::toString(cnf.shared_cache.logger.logger_type));
    if (cnf.shared_cache.logger.logger_type == LCONSOLE)
    {
        logger_node_1.set_value(cnf.shared_cache.logger.path_to_log.c_str());
    }

    // create flow tag
    pugi::xml_node flow_node_1 = partial_node.append_child(sFlow.c_str());
    flow_node_1.append_attribute(sType.c_str()).set_value(Flow::toString(cnf.shared_cache.flow.flow_type));
    if(cnf.shared_cache.flow.flow_type == FFILE)
    {
        flow_node_1.set_value(cnf.shared_cache.flow.path_to_flow.c_str());
    }

    // create children of "StaticPartial"
    pugi::xml_node caches = partial_node.append_child(sApps.c_str());
    for (auto &cache : cnf.partial_cache.app_list)
    {
        pugi::xml_node cache_node = caches.append_child(sApplication.c_str());
        cache_node.append_attribute(sSize.c_str()).set_value(static_cast<long unsigned int>(cache.size));
        cache_node.append_attribute(sXmlAsu.c_str()).set_value(cache.asu);
        cache_node.append_attribute(sQoS.c_str()).set_value(cache.qos);
    }
}

void MainConfig::Deserialize(const pugi::xml_document &doc, Config &cnf)
{
    pugi::xml_node modes = doc.child(Modes.c_str());

    // get trace analyzer info
    pugi::xml_node trace_analyzer = modes.child(sTraceAnalyzer.c_str());
    cnf.trace_analyzer = XmlTraceAnalyze();
    cnf.trace_analyzer.type = TraceAnalyzer::toType(trace_analyzer.attribute(sType.c_str()).as_string(""));

    // get trace analyzer children
    for (pugi::xml_node child = trace_analyzer.child(sTrace.c_str()); child; child = child.next_sibling(sTrace.c_str()))
    {
        XmlTrace trace_obj = XmlTrace();
        trace_obj.name = child.attribute(sName.c_str()).as_string("");
        trace_obj.path = child.text().as_string("");
        cnf.trace_analyzer.trace_list.push_back(trace_obj);
    }

    // get shared cache info
    cnf.shared_cache = XmlSharedCache();
    pugi::xml_node shared_cache = modes.child(sSharedCache.c_str());
    cnf.shared_cache.size = shared_cache.attribute(sSize.c_str()).as_uint(1);
    cnf.shared_cache.request_num = shared_cache.attribute(sRequestNum.c_str()).as_int(1000000);

    // get logger tag
    pugi::xml_node log_node = shared_cache.child(sLogs.c_str());
    cnf.shared_cache.logger.logger_type = Logger::toType(log_node.attribute(sType.c_str()).as_string(""));
    cnf.shared_cache.logger.path_to_log = log_node.text().as_string("");

    // get flow tag
    pugi::xml_node flow_node = shared_cache.child(sFlow.c_str());
    cnf.shared_cache.flow.flow_type = Flow::toType(flow_node.attribute(sType.c_str()).as_string(""));
    cnf.shared_cache.flow.path_to_flow = flow_node.text().as_string("");

    // get partial cache info
    cnf.partial_cache = XmlPartialCache();
    pugi::xml_node partial_cache = modes.child(sPartialCache.c_str());
    cnf.partial_cache.app_count = partial_cache.attribute(sAppCount.c_str()).as_uint(0);
    cnf.partial_cache.request_num = partial_cache.attribute(sRequestNum.c_str()).as_uint(1000000);
    cnf.partial_cache.common_size = static_cast<ByteSize>(partial_cache.attribute(sCommonSize.c_str()).as_int(1));

    // get logger tag
    pugi::xml_node log_node_1 = partial_cache.child(sLogs.c_str());
    cnf.shared_cache.logger.logger_type = Logger::toType(log_node_1.attribute(sType.c_str()).as_string(""));
    cnf.shared_cache.logger.path_to_log = log_node_1.text().as_string("");

    // get flow tag
    pugi::xml_node flow_node_1 = partial_cache.child(sFlow.c_str());
    cnf.shared_cache.flow.flow_type = Flow::toType(flow_node_1.attribute(sType.c_str()).as_string(""));
    cnf.shared_cache.flow.path_to_flow = flow_node_1.text().as_string("");

    // get partial cache children
    pugi::xml_node caches_node = partial_cache.child(sApps.c_str());
    for (pugi::xml_node child = caches_node.child(sApplication.c_str()); child; child = child.next_sibling(sApplication.c_str()))
    {
        XmlCache cache_obj = XmlCache();
        cache_obj.asu = child.attribute(sXmlAsu.c_str()).as_uint(0);
        cache_obj.size = child.attribute(sSize.c_str()).as_uint(1);
        cache_obj.qos = child.attribute(sQoS.c_str()).as_double(0.2);
        cnf.partial_cache.app_list.push_back(cache_obj);
    }
}

//From trace_file
void MainConfig::LoadFromFile(const std::string &file_name, pugi::xml_document &doc)
{
    pugi::xml_parse_result result = doc.load_file(file_name.c_str());
    if (result)
    {
        cout << "XML [" << file_name <<
                  "] parsed without errors, attr value: [" <<
                  doc.child("node").attribute("attr").value() << "]\n\n";
    }
    else
    {
        cout << "XML [" << file_name <<
                  "] parsed with errors, attr value: [" <<
                  doc.child("node").attribute("attr").value() << "]\n";
        cout << "Error description: " << result.description() << "\n";
        cout << "Error offset: " <<
                  result.offset << " (error at [..." <<
                  (file_name.c_str() + result.offset) << "]\n\n";
    }
}

//To trace_file
void MainConfig::SaveToFile(const pugi::xml_document &doc, const string &file_name)
{
    bool saveSucceeded = doc.save_file(file_name.c_str());
}