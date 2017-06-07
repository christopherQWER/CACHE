//
// Created by cat on 5/14/17.
//

#include "ModeRunner.h"
#define LEVEL DEBUG

using namespace std;
UniformReal uni_real_generator = UniformReal(0.1, 0.5);


// Prototypes
void GetModeConfig(const string& mode_config_path, XmlSimulate& xmlSimulator);
Flow* CreateFlowInst(const XmlSimulate& xmlSimulator, const list<string>& input_pdf);
void CreateXmlAppList(XmlSimulate& xmlSimulator, const string& analyze_conf_path);
void MemoryCleaner(Flow* flow, ClientsManager *clientsManager);
double SetQoS();


void RunSimulateMode(Config my_config)
{
    double time_step = 60;
    XmlSimulate xmlSimulator;
    GetModeConfig(my_config.simulate_path, xmlSimulator);
    CreateXmlAppList(xmlSimulator, my_config.analyze_path);
    Logger *logger = Logger::CreateLogger(xmlSimulator.logger.logger_type,
                    xmlSimulator.logger.path_to_log);
    logger->StartLog();
    ClientsManager *clientsManager = new ClientsManager(xmlSimulator.app_list);
    Storage *storage;

    for (double i = 0.1; i < 1.0; i += 0.1)
    {
        logger->ShowLogText(LEVEL, string("Storage type: ") + Storage::toString(xmlSimulator.stor_type));
        logger->ShowLogText(LEVEL, "===============================================================");
        switch (xmlSimulator.stor_type)
        {
            case SHARED:
            {
                storage = new SharedStorage(i, xmlSimulator.plot_dir,
                                            time_step,
                                            xmlSimulator.request_num);

                logger->ShowLogText(LEVEL, "Comon cache size: " + to_string(i) + " Gb");
                logger->ShowLogText(LEVEL, "Time step for histograms: " + to_string(time_step) + " sec");
                storage->CreateStorage();
                break;
            }
            case PARTIAL:
            {
                storage = new StaticPartial(i, xmlSimulator.plot_dir,
                                                            time_step,
                                                            xmlSimulator.request_num);

                logger->ShowLogText(LEVEL, "Comon cache size: " + to_string(i) + " Gb");
                logger->ShowLogText(LEVEL, "Time step for histograms: " + to_string(time_step) + " sec");
                logger->ShowLogText(LEVEL, string("First partitioning way: ") +
                        StaticPartial::toString(xmlSimulator.div_type));
                storage->CreateStorage(xmlSimulator.div_type, clientsManager->clients_map);
                break;
            }
            case DYNAMIC:
            {
            }
            default:
            {
                logger->ShowLogText(LEVEL, "Unknown storage type.");
                return;
            }
        }

        Flow *flow = CreateFlowInst(xmlSimulator, list<string>());
        logger->ShowLogText(LEVEL, "Flow type: " + Flow::toString(xmlSimulator.flow.flow_type));

        storage->Run(*clientsManager, logger, flow, xmlSimulator.with_plots);

        clientsManager->QosComparator(logger);
        if (xmlSimulator.with_plots)
        {
            clientsManager->DrawPDFPlot(flow->flow_dir_name);
            clientsManager->DrawCDFPlot(flow->flow_dir_name);
        }
        logger->ShowLogText(LEVEL, "===============================================================");

        clientsManager->common_hist_counter = 0;
        if (storage != nullptr)
            delete storage;

        if (flow != nullptr)
            delete flow;
    }
    clientsManager->DrawHrVSCacheSizePlot(Storage::toString(xmlSimulator.stor_type));
    logger->EndLog();

    if (clientsManager != nullptr)
        delete clientsManager;

    if (logger != nullptr)
        delete logger;
}

void MemoryCleaner(Flow* flow, ClientsManager *clientsManager)
{

}

void GetModeConfig(const string& mode_config_path, XmlSimulate& xmlSimulator)
{
    pugi::xml_document local_config;
    MainConfig::LoadFromFile(mode_config_path, local_config);
    XmlSimulateMode::Deserialize(local_config, xmlSimulator);
}

Flow* CreateFlowInst(const XmlSimulate& xmlSimulator, const list<string>& input_pdf)
{
    Flow* flow;
    switch (xmlSimulator.flow.flow_type)
    {
        case FFILE:
        {
            flow = new TraceFileFlow(xmlSimulator.flow.path_to_flow,
                    xmlSimulator.limit.limit_type, xmlSimulator.limit.limit_value);
            break;
        }
        case FGENERATOR:
        {
            flow = new StackDistFlow(xmlSimulator.flow.app_count, input_pdf,
                    xmlSimulator.limit.limit_type, xmlSimulator.limit.limit_value);
            break;
        }
        default:
        {
            break;
        }
    }
    return flow;
}

void CreateXmlAppList(XmlSimulate& xmlSimulator,
                      const string& analyze_conf_path)
{
    if (xmlSimulator.app_list.size() == 0)
    {
        pugi::xml_document trace_config;
        XmlTraceAnalyze xmlTraceMode;
        MainConfig::LoadFromFile(analyze_conf_path, trace_config);
        XmlAnalyzeMode::Deserialize(trace_config, xmlTraceMode);

        // Get from app units from xml-statistics
        if (xmlTraceMode.type == DETAILED)
        {
            string trace_file_dir = Utils::GetDirectoryNameFromPath(xmlSimulator.flow.path_to_flow);
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
                xml_client.qos = SetQoS();
                xmlSimulator.app_list.push_back(xml_client);
            }
        }
    }
}

double SetQoS()
{
    return uni_real_generator.GetRandom();
}