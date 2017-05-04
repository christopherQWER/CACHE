//
// Created by cat on 4/2/17.
//

#include "ModeRunner.h"
#include "../Storages/Storage.h"
#include "../Storages/SharedStorage.h"
#include "../Storages/StaticPartial.h"
#include "../Utils/Paths.h"
#include "../Xml/AnalyzerConfig.h"
#include "../Xml/SimulateConfig.h"

using namespace std;

void RunTraceAnalyseMode(Config my_config)
{
    string path_to_config = my_config.analyze_path;
    pugi::xml_document local_config;
    XmlTraceAnalyze xmlTraceInfo;
    MainConfig::LoadFromFile(path_to_config, local_config);
    AnalyzerConfig::Deserialize(local_config, xmlTraceInfo);

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


void RunSimulateMode(Config my_config)
{
    string path_to_config = my_config.simulate_path;
    pugi::xml_document local_config;
    XmlSimulate xmlSimulator;
    MainConfig::LoadFromFile(path_to_config, local_config);
    SimulateConfig::Deserialize(local_config, xmlSimulator);

    ByteSize cache_capasity = xmlSimulator.common_size * _1_GB_IN_BYTES_;
    Logger *logger = Logger::CreateLogger(xmlSimulator.logger.logger_type);

    switch (xmlSimulator.type)
    {
        case SHARED:
        {
            SharedStorage sharedCache = SharedStorage(string(_PLOT_DATA_), 60, cache_capasity, 0);
            Flow *flow = Flow::CreateFlow(xmlSimulator.flow.flow_type);
            break;
        }
        case PARTIAL:
        {
            StaticPartial staticPartial = StaticPartial(string(_PLOT_DATA_), 60, 0);
            break;
        }
        default:
        {
            break;
        }
    }
}


void RunGenerateMode(Config my_config)
{
    ByteSize app_count = my_config.partial_cache.app_list.size();
    ByteSize common_size = my_config.partial_cache.common_size * _1_GB_IN_BYTES_;



    // if applications are described in config
    if (app_count > 0)
    {
        // equal partitioning between application units
        ByteSize part_size = common_size / app_count;
        string trace_result = Utils::PathCombine(results_dir, "Generated");
        // Go through cache objects
        for (const auto &cache : my_config.partial_cache.app_list)
        {
            Client client = Client();
            client.Init(cache.asu, trace_result);
            client._cache = new Lru(part_size);
            staticPartial.InsertToClientsMap(cache.asu, client);
        }
    }
    // get applications from trace analyzer statistic
    else
    {
        if (my_config.trace_analyzer.type == DETAILED)
        {
            // go through all trace files
            for (auto &trace_file : my_config.trace_analyzer.trace_list )
            {
                // get xml-statistic file path
                string trace_file_dir = Utils::SplitFilename(trace_file.path);
                string source_file = Utils::PathCombine(trace_file_dir, trace_file.name + ".xml");
                string trace_result = Utils::PathCombine(results_dir, trace_file.name);

                TraceInfo config = TraceInfo();
                pugi::xml_document doc;
                AnalyzeConfig::LoadFromFile(source_file, doc);
                AnalyzeConfig::Deserialize(doc, config);

                my_config.partial_cache.common_size = common_size;
                my_config.partial_cache.app_count = config.apps.size();
                my_config.partial_cache.request_num = config.length;
                ByteSize part_size = common_size / my_config.partial_cache.app_count;

                // Go through cache objects
                for (const auto &app : config.apps)
                {
                    Client client = Client();
                    client.Init(app.unit, trace_result);
                    client._cache = new Lru(part_size);
                    staticPartial.InsertToClientsMap(app.unit, client);
                }
                staticPartial.EqualPartial(trace_file.path,
                                            my_config.partial_cache.logger.logger_type,
                                            my_config.partial_cache.logger.path_to_log);
            }
        }
    }
}