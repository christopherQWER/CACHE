//
// Created by cat on 2/19/17.
//
#include "XmlConfig.h"

void XmlConfig::Serialize(const Config &cnf, pugi::xml_document &doc)
{
    pugi::xml_node modelNode = doc.append_child(Model.c_str());

    pugi::xml_node sharedNode = modelNode.append_child(XmlSharedCache.c_str());
    sharedNode.append_attribute(Size.c_str()) = cnf.sharedCache.size;
    sharedNode.append_attribute(RequestNum.c_str()) = cnf.sharedCache.requestNum;
    sharedNode.append_child(XmlLogs.c_str());
    sharedNode.append_child(XmlFlow.c_str());

    pugi::xml_node partialNode = modelNode.append_child(PartialCache.c_str());
    partialNode.append_attribute(AppCount.c_str());
    partialNode.append_attribute(CommonSize.c_str());
}

void XmlConfig::Deserialize(const pugi::xml_document &doc, Config &cnf)
{

}

//From file
void XmlConfig::Serialize(const std::string &file_name, pugi::xml_document &doc)
{
    pugi::xml_parse_result result = doc.load_file(file_name.c_str());
}

//To file
void XmlConfig::Deserialize(const pugi::xml_document &doc, const std::string &file_name)
{
    bool saveSucceeded = doc.save_file(file_name.c_str());
}