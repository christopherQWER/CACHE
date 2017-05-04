//
// Created by cat on 2/19/17.
//
#include "MainConfig.h"
using namespace std;

void MainConfig::Serialize(const Config &cnf, pugi::xml_document &doc)
{
    pugi::xml_node modes_node = doc.append_child(Modes.c_str());
    pugi::xml_node generate_node = modes_node.append_child(sGenerate.c_str());
    pugi::xml_node simulate_node = modes_node.append_child(sSimulate.c_str());
    pugi::xml_node analyze_node = modes_node.append_child(sAnalyzerMode.c_str());
}

void MainConfig::Deserialize(const pugi::xml_document &doc, Config &cnf)
{
    pugi::xml_node modes = doc.child(Modes.c_str());
    cnf.simulate_path = modes.child(sSimulate.c_str()).text().as_string("");
    cnf.generate_path = modes.child(sGenerate.c_str()).text().as_string("");
    cnf.analyze_path = modes.child(sAnalyzerMode.c_str()).text().as_string("");
}

void MainConfig::LoadFromFile(const std::string &file_name, pugi::xml_document &doc)
{
    pugi::xml_parse_result result = doc.load_file(file_name.c_str());
    if (result)
    {
        cout << "XML [" << file_name <<
                  "] parsed without errors, attr value: [" <<
                  doc.child("node").attribute("attr").value() << "]\n\n";
    }
    else
    {
        cout << "XML [" << file_name <<
                  "] parsed with errors, attr value: [" <<
                  doc.child("node").attribute("attr").value() << "]\n";
        cout << "Error description: " << result.description() << "\n";
        cout << "Error offset: " <<
                  result.offset << " (error at [..." <<
                  (file_name.c_str() + result.offset) << "]\n\n";
    }
}

void MainConfig::SaveToFile(const pugi::xml_document &doc, const string &file_name)
{
    bool saveSucceeded = doc.save_file(file_name.c_str());
}

void MainConfig::SerializeLogger(const XmlLog& logger, pugi::xml_node& root_node)
{
    pugi::xml_node logger_node = root_node.append_child(sLogs.c_str());
    logger_node.append_attribute(sType.c_str()).set_value(Logger::toString(logger.logger_type));
    if (logger.logger_type == LCONSOLE)
    {
        logger_node.set_value(logger.path_to_log.c_str());
    }
}

void MainConfig::DeserializeLogger(const pugi::xml_node& root_node, XmlLog& logger)
{
    pugi::xml_node log_node = root_node.child(sLogs.c_str());
    logger.logger_type = Logger::toType(log_node.attribute(sType.c_str()).as_string(""));
    logger.path_to_log = log_node.text().as_string("");
}

void MainConfig::SerializeFlow(const XmlFlow& flow, pugi::xml_node& root_node)
{
    pugi::xml_node flow_node = root_node.append_child(sFlow.c_str());
    flow_node.append_attribute(sType.c_str()).set_value(Flow::toString(flow.flow_type));
    flow_node.append_attribute(sAppCount.c_str()).set_value(flow.app_count);
    if(flow.flow_type == FFILE)
    {
        flow_node.set_value(flow.path_to_flow.c_str());
    }
}

void MainConfig::DeserializeFlow(const pugi::xml_node& root_node, XmlFlow& flow)
{
    pugi::xml_node flow_node = root_node.child(sFlow.c_str());
    flow.flow_type = Flow::toType(flow_node.attribute(sType.c_str()).as_string(""));
    flow.app_count = flow_node.text().as_int(0);
    flow.path_to_flow = flow_node.text().as_string("");
}