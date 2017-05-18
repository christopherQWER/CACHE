//
// Created by cat on 4/23/17.
//

#include "XmlAnalyzeMode.h"

void XmlAnalyzeMode::Serialize(const XmlTraceAnalyze& analyze_cnf, pugi::xml_document& doc)
{
    // create child "TraceAnalyzer"
    pugi::xml_node trace_analyze_node = doc.append_child(sAnalyzerMode.c_str());
    trace_analyze_node.append_attribute(sType.c_str()).set_value(TraceAnalyzer::toString(analyze_cnf.type));

    // create children of "TraceAnalyzer"
    for (auto &trace : analyze_cnf.trace_list)
    {
        pugi::xml_node trace_node = trace_analyze_node.append_child(sTrace.c_str());
        trace_node.append_attribute(sName.c_str()).set_value(trace.name.c_str());
        trace_node.set_value(trace.path.c_str());
    }
}

void XmlAnalyzeMode::Deserialize(const pugi::xml_document& doc, XmlTraceAnalyze& analyze_cnf)
{
    // get trace analyzer info
    pugi::xml_node trace_analyzer = doc.child(sAnalyzerMode.c_str());
    analyze_cnf = XmlTraceAnalyze();
    analyze_cnf.type = TraceAnalyzer::toType(trace_analyzer.attribute(sType.c_str()).as_string(""));

    // get trace analyzer children
    for (pugi::xml_node child = trace_analyzer.child(sTrace.c_str()); child; child = child.next_sibling(sTrace.c_str()))
    {
        XmlTrace trace_obj = XmlTrace();
        trace_obj.name = child.attribute(sName.c_str()).as_string("");
        trace_obj.path = child.text().as_string("");
        analyze_cnf.trace_list.push_back(trace_obj);
    }
}