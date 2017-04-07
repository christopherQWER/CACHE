//
// Created by cat on 4/2/17.
//

#include "ModeRunner.h"
#include "../Algorithms/SharedCache.h"
#include "../Algorithms/StaticPartial.h"
#include "../Utils/Paths.h"

using namespace std;

void RunTraceAnalyseMode(Config my_config)
{
    for (auto &trace : my_config.trace_analyzer.trace_list)
    {
        string stat_dir = Utils::SplitFilename(trace.path.c_str());

        string file_name_xml = trace.name + string(".xml");
        string detailed_result = Utils::PathCombine(stat_dir, file_name_xml);

        string file_name_txt = trace.name + string(".txt");
        string common_result = Utils::PathCombine(stat_dir, file_name_txt);

        if (my_config.trace_analyzer.type == DETAILED)
        {
            TraceAnalyzer *a = new TraceAnalyzer(trace.path.c_str(), detailed_result);
            a->GetDetailedStat();
        }
        if (my_config.trace_analyzer.type == COMMON)
        {
            TraceAnalyzer *a = new TraceAnalyzer(trace.path.c_str(), common_result);
            a->GetCommonStat();
        }
        if (my_config.trace_analyzer.type == ALL)
        {
            TraceAnalyzer *a = new TraceAnalyzer(trace.path.c_str(), detailed_result);
            a->GetDetailedStat();
            delete a;

            a = new TraceAnalyzer(trace.path.c_str(), common_result);
            a->GetCommonStat();
        }
    }
}


void RunSharedCacheMode(Config my_config)
{
    ByteSize cache_capasity = my_config.shared_cache.size * _1_GB_IN_BYTES_;
    int experiment_number = my_config.shared_cache.request_num;

    string results_dir = Utils::PathCombine(string(_PLOT_DATA_), string("Shared"));
    Utils::CreateDirectory(results_dir);

    SharedCache sharedCache = SharedCache(results_dir, 60, cache_capasity, 0);

    if (my_config.shared_cache.flow.flow_type == FFILE)
    {
        sharedCache.RunAlgorithm(my_config.shared_cache.flow.path_to_flow,
                                  my_config.shared_cache.logger.logger_type,
                                  "");
    }
    else
    {
        sharedCache.RunAlgorithm("", my_config.shared_cache.logger.logger_type, "");
    }
}


void RunPartialCacheMode(Config my_config)
{
    ByteSize app_count = my_config.partial_cache.app_list.size();
    ByteSize common_size = my_config.partial_cache.common_size * _1_GB_IN_BYTES_;

    string results_dir = Utils::PathCombine(string(_PLOT_DATA_), string("Partial"));
    Utils::CreateDirectory(results_dir);

    StaticPartial staticPartial = StaticPartial(results_dir, 60, 0);

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


void RunPlotsMode(Config my_config)
{

}