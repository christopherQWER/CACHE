//
// Created by cat on 5/14/17.
//

#include "ModeRunner.h"
using namespace std;

void RunSimulateMode(Config my_config)
{
    string path_to_config = my_config.simulate_path;
    pugi::xml_document local_config;
    Flow *flow;
    XmlSimulate xmlSimulator;
    ClientsManager *clientsManager;
    MainConfig::LoadFromFile(path_to_config, local_config);
    XmlSimulateMode::Deserialize(local_config, xmlSimulator);

    Logger *logger = Logger::CreateLogger(xmlSimulator.logger.logger_type);
    switch (xmlSimulator.flow.flow_type)
    {
        case FFILE:
        {
            flow = new TraceFileFlow(xmlSimulator.flow.path_to_flow);
            break;
        }
        case FGENERATOR:
        {
            flow = new StackDistFlow();
            break;
        }
        default:
        {
            break;
        }
    }

    switch (xmlSimulator.stor_type)
    {
        case SHARED:
        {
            SharedStorage sharedCache = SharedStorage(xmlSimulator.common_size,
                    string(_PLOT_DATA_), 60, 0);
            sharedCache.CreateStorage();
            sharedCache.Run();
            break;
        }
        case PARTIAL:
        {
            StaticPartial staticPartial = StaticPartial(xmlSimulator.common_size,
                    string(_PLOT_DATA_), 60, 0);
            if (xmlSimulator.app_count == 0)
            {
                pugi::xml_document trace_config;
                XmlTraceAnalyze xmlTraceMode;
                MainConfig::LoadFromFile(my_config.analyze_path, trace_config);
                XmlAnalyzeMode::Deserialize(trace_config, xmlTraceMode);

                // Get from app units from xml-statistics
                if (xmlTraceMode.type == DETAILED)
                {
                    string trace_file_dir = Utils::SplitFilename(xmlSimulator.flow.path_to_flow);
                    string source_file = Utils::PathCombine(trace_file_dir,
                            Utils::GetFileNameWithoutExt(xmlSimulator.flow.path_to_flow) + ".xml");

                    TraceInfo config = TraceInfo();
                    pugi::xml_document doc;
                    XmlAnalyzeMode::LoadFromFile(source_file, doc);
                    AnalyzeConfig::Deserialize(doc, config);

                    for (const auto &app : config.apps)
                    {
                        XmlClient xml_client = XmlClient();
                        xml_client.asu = app.unit;
                        xmlSimulator.app_list.push_back(xml_client);
                    }
                }
            }
            clientsManager = new ClientsManager(xmlSimulator.app_list);
            staticPartial.CreateStorage(xmlSimulator.div_type, clientsManager->clients_map);
            staticPartial.Run(logger, flow, xmlSimulator.with_plots);
            break;
        }
        default:
        {
            break;
        }
    }
}