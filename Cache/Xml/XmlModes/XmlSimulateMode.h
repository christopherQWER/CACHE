//
// Created by cat on 4/23/17.
//

#pragma once
#include "../MainConfig.h"
#include "../../Utils/Enums.h"

struct XmlClient {
    Asu asu;
    double qos;
    ByteSize required_size;
    XmlClient(const Asu i, bool b) : asu(0), qos(0) {}
    bool operator < (XmlClient x)
    {
        return asu < x.asu;
    }

    friend bool operator== ( const XmlClient &n1, const XmlClient &n2)
    {
        return n1.asu == n2.asu;
    };
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
    XmlLimit limit;
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
                    limit(XmlLimit()),
                    plot_dir(""),
                    app_list() {}
};

static const std::string sWithPlots = "WithPlots";
static const std::string sApps = "Applications";
static const std::string sCommonSize = "CommonSize";
static const std::string sPlotDir = "PlotDir";
static const std::string sDivision = "Division";
static const std::string sRequiredSize = "RequiredSize";

class XmlSimulateMode : public MainConfig {
public:

    static void Serialize(const XmlSimulate &cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, XmlSimulate &cnf);
};