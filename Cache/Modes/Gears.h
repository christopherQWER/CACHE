//
// Created by cat on 6/13/17.
//

#pragma once

#include "../Flows/TraceFileFlow.h"
#include "../Flows/StackDistFlow.h"
#include "../Xml/MainConfig.h"

class Gears {
public:
    static Flow* CreateFlowInst(const XmlFlow& xmlFlow,
            const XmlLimit& xmlLimit,
            const std::list<std::string>& input_pdf);

};

