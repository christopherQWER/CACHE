//
// Created by cat on 5/14/17.
//

#include "ModeRunner.h"
#define LEVEL DEBUG
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
        flow_list.push_back(new StackDistFlow(source_struct.asu,
                                              source_struct.low_address,
                                              source_struct.input_pdf_dirs,
                                              source_struct.request_num,
                                              source_struct.switcher));
    }
    // Create temp list with requests from different apps
    //list<Request*> req_tmp;

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
            map<Timestamp, Request*> req_tmp;
            while (xmlGenerator.limit.limit_value > req_number)
            {
                for (auto& flow : flow_list)
                {
                    Request *req;
                    if (!flow->IsEndOfFlow())
                    {
                        req = flow->GetRequest();
                        req_tmp.insert(pair<Timestamp, Request*>(req->_timestamp, req));
                        req_number++;
                    }
                }
            }
            for (auto request : req_tmp)
            {
                logger->ShowRequestInfo(LEVEL, req_number, request.second->_asu,
                        request.second->_lba,
                        request.second->_timestamp);
                string request_string = RequestParser::GetStringFromRequest(*request.second);
                Utils::AppendToFile(output_trace_file, request_string);
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