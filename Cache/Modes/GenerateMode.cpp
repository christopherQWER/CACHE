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
                                              xmlGenerator.limit.limit_type,
                                              xmlGenerator.limit.limit_value,
                                              source_struct.switcher));
    }

    // Create temp list with requests from different apps
    list<Request*> req_tmp;

    switch(xmlGenerator.limit.limit_type)
    {
        case TIME:
        {
            Timestamp temp_time = 0;
            while (xmlGenerator.limit.limit_value > temp_time)
            {
                list<Request*> req_tmp;
                for (auto flow : flow_list)
                {
                    Request *req = flow->GetRequest();
                    temp_time += req->_timestamp;
                    req->_timestamp = temp_time;
                    req_tmp.push_back(req);
                }
                req_tmp.sort();

                for (auto request : req_tmp)
                {
                    if (request->_timestamp < xmlGenerator.limit.limit_value)
                    {
                        string request_string = RequestParser::GetStringFromRequest(*request);
                        Utils::AppendToFile(output_trace_file, request_string);
                    }
                    else
                    {
                        break;
                    }
                }
                req_tmp.clear();
            }
            break;
        }
        case REQUEST_NUMBER:
        {
            ByteSize req_number = 0;
            Timestamp temp_time = 0;
            while (xmlGenerator.limit.limit_value > req_number)
            {
                list<Request*> req_tmp;
                for (auto flow : flow_list)
                {
                    Request *req = flow->GetRequest();
                    temp_time += req->_timestamp;
                    req->_timestamp = temp_time;
                    req_tmp.push_back(req);
                }

                for (auto request : req_tmp)
                {
                    if (req_number < xmlGenerator.limit.limit_value)
                    {
                        string request_string = RequestParser::GetStringFromRequest(*request);
                        Utils::AppendToFile(output_trace_file, request_string);
                        req_number++;
                    }
                    else
                    {
                        break;
                    }
                }
                req_tmp.clear();
            }
            break;
        }
        default:
        {
            break;
        }
    }

    if(logger != nullptr)
        delete logger;
}