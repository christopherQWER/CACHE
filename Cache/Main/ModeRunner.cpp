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
    ByteSize cache_capasity = (my_config.shared_cache.size * _1_GB_IN_BYTES_) / 4;
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
    ByteSize app_count = my_config.partial_cache.cache_list.size();
    if (app_count > 0)
    {
        // size of all cache space in bytes
        ByteSize common_size = my_config.partial_cache.common_size * _1_GB_IN_BYTES_;
        // equal partitioning between application units
        ByteSize part_size = common_size / app_count;
        map<Asu, AppClass> clients;
        // Go through cache objects
        for (const auto &cache : my_config.partial_cache.cache_list)
        {
            AppClass client = AppClass();
            client._application_id = cache.asu;
            client._cache = new Lru(part_size);
            clients.insert(pair<Asu, AppClass>(cache.asu, client));
        }
    }
    else
    {
    }
}