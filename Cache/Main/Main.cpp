#include "../Modeling/TraceAnalyzer.h"
#include "../Utils/Paths.h"
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
void RunTraceAnalyseMode();
void RunSharedCacheMode();
void RunPartialCacheMode();


int main()
{
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
                RunTraceAnalyseMode();
                break;
            }
            case SHARED_CACHE:
            {
                cout << "Start shared cache mode..." << endl;
                void RunSharedCacheMode();
                break;
            }
            case PARTIAL_CACHE:
            {
                cout << "Start partial cache mode..." << endl;
                void RunPartialCacheMode();
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


void RunTraceAnalyseMode()
{
    TraceAnalyzer *a = new TraceAnalyzer(_WEB_SEARCH_1_, _STAT_XML_);
    a->GetDetailedStat();
}


void RunSharedCacheMode()
{

}


void RunPartialCacheMode()
{

}