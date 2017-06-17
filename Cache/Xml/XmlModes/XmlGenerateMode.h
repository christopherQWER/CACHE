//
// Created by cat on 4/23/17.
//

#pragma once
#include "../MainConfig.h"

struct Sources{
    Asu asu;
    Lba low_address;
    double switcher;
    std::list<std::string> input_pdf_dirs;
    ByteSize request_num;
    Sources() : asu(0),
                low_address(400000),
                  switcher(0),
                  input_pdf_dirs(),
                  request_num(0)
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
const std::string sLowAddressBound = "LowAddressBound";

class XmlGenerateMode : public MainConfig {
public:

    static void Serialize(const XmlGenerate &gen_cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, XmlGenerate &gen_cnf);
};