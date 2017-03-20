//
// Created by cat on 3/2/17.
//

#include "TestConfig.h"

TestConfig::TestConfig()
{
}

TestConfig::~TestConfig()
{
}

 void TestConfig::MainTester()
{
    pugi::xml_document doc;
    pugi::xml_document doc2;

    XmlConfig::LoadFromFile(_XML_CONFIG_, doc);

    Config main_config;
    XmlConfig::Deserialize(doc, main_config);

    XmlConfig::Serialize(main_config, doc2);
    XmlConfig::SaveToFile(doc2, "//home//cat//Documents//CACHE//Config1.xml");
}