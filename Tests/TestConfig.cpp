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

    MainConfig::LoadFromFile(_XML_CONFIG_, doc);

    Config main_config = Config();
    MainConfig::Deserialize(doc, main_config);

    MainConfig::Serialize(main_config, doc2);
    MainConfig::SaveToFile(doc2, "//home//cat//Documents//CACHE//Config1.xml");
}