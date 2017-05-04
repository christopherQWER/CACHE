#include "../Modeling/TraceAnalyzer.h"
#include "../Utils/Paths.h"
#include "ModeRunner.h"
using namespace std;
#define TYPE LCONSOLE
// Functions prototypes
void ShowMenu(void);


int main()
{
    Logger *pLogger = Logger::CreateLogger(TYPE);
    Config my_config = Config();
    pugi::xml_document doc;
    MainConfig::LoadFromFile(_XML_CONFIG_, doc);
    MainConfig::Deserialize(doc, my_config);

    while (true)
    {
        // shows all program's modes
        ShowMenu();

        // get user choice of mode
        int choice = 0;
        cin >> choice;
        Mode client_mode = static_cast<Mode>(choice);

        switch (client_mode)
        {
            case TRACE_ANALYZE:
            {
                pLogger->ShowLogText(DEBUG, "Start trace analyser mode...\n");
                RunTraceAnalyseMode(my_config);
                break;
            }
            case SIMULATE:
            {
                pLogger->ShowLogText(DEBUG, "Start simulate cache mode...\n");
                RunSimulateMode(my_config);
                break;
            }
            case GENERATE:
            {
                pLogger->ShowLogText(DEBUG, "Start generate flow mode...\n");
                RunGenerateMode(my_config);
                break;
            }
            case EXIT:
            {
                pLogger->ShowLogText(DEBUG, "I'm ended.\n");
                exit(0);
            }
            default:
            {
                pLogger->ShowLogText(DEBUG, "Choose right mode.\n");
                break;
            }
        }
    }
}


 // Function prints on display different program's modes
void ShowMenu(void)
{
    cout << "Choose mode:\n" << endl;
    cout << to_string(TRACE_ANALYZE) + string(" --> ") + toString(TRACE_ANALYZE) << endl;
    cout << to_string(SIMULATE) + string(" --> ") + toString(SIMULATE) << endl;
    cout << to_string(GENERATE) + string(" --> ") + toString(GENERATE) << endl;
    cout << to_string(EXIT) + string(" --> EXIT") << endl;
    cout << endl;
}