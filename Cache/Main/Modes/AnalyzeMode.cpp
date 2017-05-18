//
// Created by cat on 5/14/17.
//

#include "ModeRunner.h"
using namespace std;

void RunTraceAnalyseMode(Config my_config)
{
    string path_to_config = my_config.analyze_path;
    pugi::xml_document local_config;
    XmlTraceAnalyze xmlTraceInfo;
    MainConfig::LoadFromFile(path_to_config, local_config);
    XmlAnalyzeMode::Deserialize(local_config, xmlTraceInfo);

    for (auto &trace : xmlTraceInfo.trace_list)
    {
        string stat_dir = Utils::SplitFilename(trace.name.c_str());

        string file_name_xml = trace.name + string(".xml");
        string detailed_result = Utils::PathCombine(stat_dir, file_name_xml);

        string file_name_txt = trace.name + string(".txt");
        string common_result = Utils::PathCombine(stat_dir, file_name_txt);

        if (xmlTraceInfo.type == DETAILED)
        {
            TraceAnalyzer *a = new TraceAnalyzer(trace.path.c_str(), detailed_result);
            a->GetDetailedStat();
        }
        if (xmlTraceInfo.type == COMMON)
        {
            TraceAnalyzer *a = new TraceAnalyzer(trace.path.c_str(), common_result);
            a->GetCommonStat();
        }
        if (xmlTraceInfo.type == ALL)
        {
            TraceAnalyzer *a = new TraceAnalyzer(trace.path.c_str(), detailed_result);
            a->GetDetailedStat();
            delete a;
            a = new TraceAnalyzer(trace.path.c_str(), common_result);
            a->GetCommonStat();
        }
    }
}