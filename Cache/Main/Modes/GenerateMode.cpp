//
// Created by cat on 5/14/17.
//

#include "ModeRunner.h"
using namespace std;

void RunGenerateMode(Config my_config)
{
    string path_to_config = my_config.generate_path;
    pugi::xml_document local_config;
    XmlGenerate xmlGenerator;
    MainConfig::LoadFromFile(path_to_config, local_config);
    XmlGenerateMode::Deserialize(local_config, xmlGenerator);

    Logger *logger = Logger::CreateLogger(xmlGenerator.logger.logger_type);
    Flow flow = StackDistFlow(xmlGenerator.flow.app_count,
                                xmlGenerator.input_pdf_dir,
                                xmlGenerator.system_time);
    string output_trace_file = Utils::PathCombine(xmlGenerator.flow.path_to_flow,
            Utils::GetCurrentStringUnixTime() + ".spc");

    Request req = flow.GetRequest();
    while (xmlGenerator.system_time > req._timestamp)
    {
        string request_string = RequestParser::GetStringFromRequest(req);
        Utils::AppendToFile(output_trace_file, request_string);
        flow.GetRequest();
    }
}