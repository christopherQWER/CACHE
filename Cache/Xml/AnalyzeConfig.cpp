//
// Created by cat on 4/3/17.
//

#include "AnalyzeConfig.h"
using namespace std;

void AnalyzeConfig::Serialize(const TraceInfo &trace_info, pugi::xml_document &doc)
{
    pugi::xml_node root = doc.append_child(sTraceFile.c_str());
    root.append_attribute(sTracePath.c_str()).set_value(trace_info.input_file.c_str());
    root.append_attribute(sLength.c_str()).set_value(static_cast<long unsigned int>(trace_info.length));
    root.append_attribute(sOutPath.c_str()).set_value(trace_info.output_file.c_str());

    for(auto &app : trace_info.apps)
    {
        pugi::xml_node xml_app = root.append_child(sApp.c_str());
        xml_app.append_attribute(sUnit.c_str()).set_value(app.unit);
        xml_app.append_attribute(sReads.c_str()).set_value(app.reads);
        xml_app.append_attribute(sWrites.c_str()).set_value(app.writes);
        xml_app.append_attribute(sReqNum.c_str()).set_value(static_cast<unsigned long>(app.req_num));
        xml_app.append_attribute(sAvgBytes.c_str()).set_value(static_cast<unsigned long>(app.avg_req_size));
    }
}

void AnalyzeConfig::Deserialize(const pugi::xml_document &doc, TraceInfo &trace_info)
{
    pugi::xml_node root = doc.child(sTraceFile.c_str());
    trace_info.input_file = root.attribute(sTracePath.c_str()).as_string("");
    trace_info.output_file = root.attribute(sOutPath.c_str()).as_string("");
    trace_info.length = root.attribute(sLength.c_str()).as_uint(0);

    for (pugi::xml_node child = root.child(sApp.c_str()); child; child = child.next_sibling(sApp.c_str()))
    {
        AppInfo app_inf = AppInfo();
        app_inf.unit = child.attribute(sUnit.c_str()).as_uint(0);
        app_inf.avg_req_size = child.attribute(sAvgBytes.c_str()).as_uint(0);
        app_inf.req_num = child.attribute(sReqNum.c_str()).as_uint(0);
        app_inf.reads = child.attribute(sReads.c_str()).as_uint(0);
        app_inf.writes = child.attribute(sWrites.c_str()).as_uint(0);
        trace_info.apps.push_back(app_inf);
    }
}