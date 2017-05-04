//
// Created by cat on 4/23/17.
//

#pragma once

#include "MainConfig.h"

struct XmlGenerate{
    XmlLog logger;
    XmlFlow flow;
};

class GenerateConfig : public MainConfig {
public:

    static void Serialize(const XmlGenerate &gen_cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, XmlGenerate &gen_cnf);
};