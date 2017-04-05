//
// Created by cat on 4/2/17.
//

#include "ModeRunner.h"
#include "../Algorithms/SharedCache.h"
#include "../Algorithms/StaticPartial.h"

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

    SharedCache* sharedCache = new SharedCache(experiment_number, cache_capasity);

    if (my_config.shared_cache.flow.flow_type == FFILE)
    {
        sharedCache->RunAlgorithm(my_config.shared_cache.flow.path_to_flow,
                my_config.shared_cache.logger.logger_type, "");
    }
    else
    {
        sharedCache->RunAlgorithm("", my_config.shared_cache.logger.logger_type, "");
    }
}


void RunPartialCacheMode(Config my_config)
{
    ByteSize app_count = my_config.partial_cache.app_list.size();
    // size of all cache space in bytes
    ByteSize common_size = my_config.partial_cache.common_size * _1_GB_IN_BYTES_;

    // if applications are described in config
    if (app_count > 0)
    {
        // equal partitioning between application units
        ByteSize part_size = common_size / app_count;
        map<Asu, AppClass> clients;
        // Go through cache objects
        for (const auto &cache : my_config.partial_cache.app_list)
        {
            AppClass client = AppClass();
            client._application_id = cache.asu;
            client._cache = new Lru(part_size);
            clients.insert(pair<Asu, AppClass>(cache.asu, client));
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

                TraceInfo config = TraceInfo();
                pugi::xml_document doc;
                AnalyzeConfig::LoadFromFile(source_file, doc);
                AnalyzeConfig::Deserialize(doc, config);

                my_config.partial_cache.common_size = common_size;
                my_config.partial_cache.app_count = config.apps.size();
                my_config.partial_cache.request_num = config.length;
                ByteSize part_size = common_size / my_config.partial_cache.app_count;

                map<Asu, AppClass> client_map;
                // Go through cache objects
                for (const auto &app : config.apps)
                {
                    AppClass client = AppClass();
                    client._application_id = app.unit;
                    client._cache = new Lru(part_size);
                    client_map.insert(pair<Asu, AppClass>(app.unit, client));
                }

                StaticPartial::EqualPartial(trace_file.path, client_map,
                        my_config.partial_cache.logger.logger_type,
                        my_config.partial_cache.logger.path_to_log);
            }
        }
    }
}