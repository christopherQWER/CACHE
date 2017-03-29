#include "../Modeling/TraceAnalyzer.h"
#include "../Algorithms/SharedCache.h"
#include "../Xml/XmlConfig.h"
#include "../Utils/Paths.h"
#include "../Modeling/AppClass.h"
using namespace std;

// Enumeration for program modes
enum Mode{
    TRACE_ANALYZE = 1,
    SHARED_CACHE,
    PARTIAL_CACHE,
    EXIT
};

// Functions prototypes
void ShowMenu(void);
void RunTraceAnalyseMode(Config my_config);
void RunSharedCacheMode(Config my_config);
void RunPartialCacheMode(Config my_config);


int main()
{
    Config my_config = Config();
    pugi::xml_document doc;
    XmlConfig::LoadFromFile(_XML_CONFIG_, doc);
    XmlConfig::Deserialize(doc, my_config);

    while (true)
    {
        // shows all program's modes
        ShowMenu();

        // get user choice of mode
        int choice = cin.get() - 48;
        Mode client_mode = static_cast<Mode>(choice);

        switch (client_mode)
        {
            case TRACE_ANALYZE:
            {
                cout << "Start trace analyser mode..." << endl;
                RunTraceAnalyseMode(my_config);
                break;
            }
            case SHARED_CACHE:
            {
                cout << "Start shared cache mode..." << endl;
                RunSharedCacheMode(my_config);
                break;
            }
            case PARTIAL_CACHE:
            {
                cout << "Start partial cache mode..." << endl;
                RunPartialCacheMode(my_config);
                break;
            }
            case EXIT:
            {
                cout << "I'm ended." << endl;
                exit(0);
            }
            default:
            {
                cout << "Choose right mode." << endl;
                break;
            }
        }
    }
}

 /// \brief         [Function turn elements of Mode type to string representation]
 /// \param mode    [program mode]
 /// \return        [string representation of Mode]
static const char* toString(Mode mode)
{
    switch (mode)
    {
        case TRACE_ANALYZE: { return "TRACE_ANALYZE";}
        case SHARED_CACHE: { return "SHARED_CACHE";}
        case PARTIAL_CACHE: { return "PARTIAL_CACHE";}
        case EXIT: {return "EXIT";}
        default: { return "UNKNOWN";}
    }
}

 // Function prints on display different program's modes
void ShowMenu(void)
{
    cout << "Choose mode:" << endl;
    cout << to_string(TRACE_ANALYZE) + string(" --> ") + toString(TRACE_ANALYZE) << endl;
    cout << to_string(SHARED_CACHE) + string(" --> ") + toString(SHARED_CACHE) << endl;
    cout << to_string(PARTIAL_CACHE) + string(" --> ") + toString(PARTIAL_CACHE) << endl;
    cout << to_string(PARTIAL_CACHE + 1) + string(" --> EXIT") << endl;
    cout << endl;
}


void RunTraceAnalyseMode(Config my_config)
{
    for (auto &trace : my_config.trace_analyzer.trace_list)
    {
        TraceAnalyzer *a = new TraceAnalyzer(trace.path.c_str(), trace.name.c_str());
        if (my_config.trace_analyzer.type == DETAILED)
        {
            a->GetDetailedStat();
        }
        else if (my_config.trace_analyzer.type == COMMON)
        {
            a->GetCommonStat();
        }
    }
}


void RunSharedCacheMode(Config my_config)
{
    ByteSize cache_capasity = (my_config.shared_cache.size * _1_GB_IN_BYTES_) / 4;
    int experiment_number = my_config.shared_cache.request_num;

    SharedCache* sharedCache = new SharedCache(experiment_number, cache_capasity);
    sharedCache->RunAlgorithm(_WEB_SEARCH_1_);
}


void RunPartialCacheMode(Config my_config)
{
    int app_count = my_config.partial_cache.cache_list.size();
    if (app_count > 0)
    {
        ByteSize common_size = my_config.partial_cache.common_size * _1_GB_IN_BYTES_;
        ByteSize part_size = common_size / app_count;
        list<AppClass> clients;
        // Go through cache objects
        for (const auto &cache : my_config.partial_cache.cache_list)
        {
            AppClass client = AppClass(part_size);
            client._application_id = cache.asu;
            clients.push_back(client);
        }
    }
    else
    {

    }
}