//
// Created by cat on 4/23/17.
//

#pragma once
#include "../MainConfig.h"

struct Sources{
    Asu asu;
    double switcher;
    std::list<std::string> input_pdf_dirs;
    Sources() : asu(0),
                  switcher(0),
                  input_pdf_dirs()
                  {}
};

struct XmlGenerate{
    XmlLog logger;
    XmlFlow flow;
    XmlLimit limit;
    std::list<Sources> source_for_apps;
    XmlGenerate() : logger(XmlLog()),
                    flow(XmlFlow()),
                    limit(XmlLimit()),
                    source_for_apps()
                    {}
};

const std::string sSources = "Sources";
const std::string sInputPdf = "InputPdf";
const std::string sSwitch = "Switch";

class XmlGenerateMode : public MainConfig {
public:

    static void Serialize(const XmlGenerate &gen_cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, XmlGenerate &gen_cnf);
};