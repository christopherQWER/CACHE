//
// Created by cat on 6/13/17.
//

#include "Gears.h"
using namespace std;

Flow* Gears::CreateFlowInst(const XmlFlow& xmlFlow,
        const XmlLimit& xmlLimit,
        const list<string>& input_pdf)
{
    Flow* flow;
    switch (xmlFlow.flow_type)
    {
        case FFILE:
        {
            flow = new TraceFileFlow(xmlFlow.path_to_flow,
                    xmlLimit.limit_type, xmlLimit.limit_value);
            break;
        }
//        case FGENERATOR:
//        {
//            flow = new StackDistFlow(xmlFlow.app_count, input_pdf,
//                    xmlLimit.limit_type, xmlLimit.limit_value);
//            break;
//        }
        default:
        {
            break;
        }
    }
    return flow;
}