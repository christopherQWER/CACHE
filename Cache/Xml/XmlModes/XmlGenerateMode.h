//
// Created by cat on 4/23/17.
//

#pragma once
#include "../MainConfig.h"

struct XmlInputPdfs{
    Asu asu;
    double switcher;
    std::list<std::string> input_pdf_dirs;
    XmlInputPdfs() : asu(0),
                  switcher(0),
                  input_pdf_dirs()
                  {}
};

struct XmlGenerate{
    XmlLog logger;
    XmlFlow flow;
    double system_time;
    std::list<XmlInputPdfs> source_for_apps;
    XmlGenerate() : logger(XmlLog()),
                    flow(XmlFlow()),
                    system_time(0),
                    source_for_apps()
                    {}
};

const std::string sSystemTime = "SystemTime";
const std::string sInputPdfs = "InputPdfs";
const std::string sInputPdf = "InputPdf";
const std::string sSwitch = "Switch";

class XmlGenerateMode : public MainConfig {
public:

    static void Serialize(const XmlGenerate &gen_cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, XmlGenerate &gen_cnf);
};