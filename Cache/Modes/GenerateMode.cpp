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
    Utils::CreateDirectory(xmlGenerator.flow.path_to_flow);
    string output_trace_file = Utils::PathCombine(xmlGenerator.flow.path_to_flow,
            Utils::GetCurrentStringUnixTime() + ".spc");

    list<Flow*> flow_list;
    for (auto source_struct : xmlGenerator.source_for_apps)
    {
        flow_list.push_back(new StackDistFlow(xmlGenerator.flow.app_count,
                                              source_struct.input_pdf_dirs,
                                              source_struct.switcher,
                                              xmlGenerator.system_time));
    }

    // Create temp list with requests from different apps
    list<Request*> req_tmp;
    Timestamp temp_time = 0;
    while (xmlGenerator.system_time > temp_time)
    {
        list<Request*> req_tmp;
        for (auto flow : flow_list)
        {
            Request *req = flow->GetRequest();
            req_tmp.push_back(req);
            req_tmp.sort();

            temp_time = req->_timestamp;
            if (temp_time < xmlGenerator.system_time)
            {
                string request_string = RequestParser::GetStringFromRequest(*req);
                Utils::AppendToFile(output_trace_file, request_string);
            }
            else
            {
                break;
            }
        }
        req_tmp.clear();
    }

    if(logger != nullptr)
        delete logger;
}