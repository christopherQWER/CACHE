//
// Created by cat on 4/23/17.
//

#pragma once

#include "../MainConfig.h"

struct XmlGenerate{
    XmlLog logger;
    XmlFlow flow;
    double system_time;
    std::string input_pdf_dir;

    XmlGenerate() : logger(XmlLog()),
                    flow(XmlFlow()),
                    system_time(0),
                    input_pdf_dir("")
                    {}
};

const std::string sSystemTime = "SystemTime";
const std::string sInputPdf = "InputPdf";

class XmlGenerateMode : public MainConfig {
public:

    static void Serialize(const XmlGenerate &gen_cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, XmlGenerate &gen_cnf);
};