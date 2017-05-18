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
    Flow flow;
}