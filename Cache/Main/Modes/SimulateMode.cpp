//
// Created by cat on 5/14/17.
//

#include "ModeRunner.h"
using namespace std;

// Prototypes
void GetModeConfig(const string& mode_config_path, XmlSimulate& xmlSimulator);
Flow* CreateFlowInst(const XmlSimulate& xmlSimulator, const string& input_pdf);
void CreateXmlAppList(const XmlSimulate& xmlSimulator, const string& analyze_conf_path);


void RunSimulateMode(Config my_config)
{
    XmlSimulate xmlSimulator;
    GetModeConfig(my_config.simulate_path, xmlSimulator);

    Logger *logger = Logger::CreateLogger(xmlSimulator.logger.logger_type);
    Flow *flow = CreateFlowInst(xmlSimulator, "");

    // Create storage instances and some needed info
    switch (xmlSimulator.stor_type)
    {
        case SHARED:
        {
            SharedStorage sharedCache = SharedStorage(xmlSimulator.common_size,
                    xmlSimulator.plot_dir, 60, 0);
            CreateXmlAppList(xmlSimulator, my_config.analyze_path);
            ClientsManager clientsManager = ClientsManager(xmlSimulator.app_list);
            sharedCache.CreateStorage();
            sharedCache.Run(clientsManager.clients_map, logger, flow, xmlSimulator.with_plots);
            clientsManager.QosComparator(logger);
            break;
        }
        case PARTIAL:
        {
            StaticPartial staticPartial = StaticPartial(xmlSimulator.common_size,
                    xmlSimulator.plot_dir, 60, 0);
            CreateXmlAppList(xmlSimulator, my_config.analyze_path);
            ClientsManager clientsManager = ClientsManager(xmlSimulator.app_list);
            staticPartial.CreateStorage(xmlSimulator.div_type, clientsManager.clients_map);
            staticPartial.Run(clientsManager.clients_map, logger, flow, xmlSimulator.with_plots);
            clientsManager.QosComparator(logger);
            break;
        }
        default:
        {
            break;
        }
    }
}


void GetModeConfig(const string& mode_config_path, XmlSimulate& xmlSimulator)
{
    pugi::xml_document local_config;
    MainConfig::LoadFromFile(mode_config_path, local_config);
    XmlSimulateMode::Deserialize(local_config, xmlSimulator);
}

Flow* CreateFlowInst(const XmlSimulate& xmlSimulator, const string& input_pdf)
{
    Flow* flow;
    switch (xmlSimulator.flow.flow_type)
    {
    case FFILE:
    {
        flow = new TraceFileFlow(xmlSimulator.flow.path_to_flow);
        break;
    }
    case FGENERATOR:
    {
        flow = new StackDistFlow(xmlSimulator.flow.app_count, input_pdf);
        break;
    }
    default:
    {
        break;
    }
    }
    return flow;
}

void CreateXmlAppList(const XmlSimulate& xmlSimulator, const string& analyze_conf_path)
{
    if (xmlSimulator.app_count == 0)
    {
        pugi::xml_document trace_config;
        XmlTraceAnalyze xmlTraceMode;
        MainConfig::LoadFromFile(analyze_conf_path, trace_config);
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
}