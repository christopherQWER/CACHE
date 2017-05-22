//
// Created by cat on 4/23/17.
//

#pragma once
#include "../MainConfig.h"
#include "../../Storages/StaticPartial.h"

struct XmlClient {
    Asu asu;
    double qos;
    XmlClient() : asu(0), qos(0) {}
};


struct XmlSimulate {
    StorageType stor_type;
    DivisionType div_type;
    ByteSize app_count;
    ByteSize common_size;
    ByteSize request_num;
    bool with_plots;
    XmlLog logger;
    XmlFlow flow;
    std::string plot_dir;
    std::list<XmlClient> app_list;

    XmlSimulate() : stor_type(SHARED),
                    div_type(EQUAL),
                    app_count(0),
                    request_num(0),
                    common_size(0),
                    with_plots(false),
                    logger(XmlLog()),
                    flow(XmlFlow()),
                    plot_dir(""),
                    app_list(std::list<XmlClient>()) {}
};

static const std::string sWithPlots = "WithPlots";
static const std::string sApps = "Applications";
static const std::string sCommonSize = "CommonSize";
static const std::string sPlotDir = "PlotDir";

class XmlSimulateMode : public MainConfig {
public:

    static void Serialize(const XmlSimulate &cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, XmlSimulate &cnf);
};