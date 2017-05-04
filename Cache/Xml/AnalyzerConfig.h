//
// Created by cat on 4/23/17.
//

#pragma once
#include <iostream>
#include "../Modeling/TraceAnalyzer.h"
#include "MainConfig.h"

/// <Trace Name="WebSearch_1">path</Trace>
struct XmlTrace {
    std::string name;
    std::string path;
    XmlTrace() : name(std::string("")), path(std::string("")) {}
};

struct XmlTraceAnalyze {
    AnalyzerType type;
    std::list<XmlTrace> trace_list;
    XmlTraceAnalyze()
            :type(DETAILED), trace_list() { }
};

static const std::string sTrace = "Trace";

class AnalyzerConfig : public MainConfig {
public:

    static void Serialize(const XmlTraceAnalyze &analyze_cnf, pugi::xml_document &doc);
    static void Deserialize(const pugi::xml_document &doc, XmlTraceAnalyze &cnf);
};