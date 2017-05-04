//
// Created by cat on 5/1/17.
//

#include "Flow.h"
#include "StackDistFlow.h"
#include "TraceFileFlow.h"
using namespace std;

Flow* Flow::CreateFlow(FlowType type)
{
    Flow *flow;
    switch (type)
    {
        case FFILE:
        {
            flow = new TraceFileFlow(std::string());
            break;
        }
        case FGENERATOR:
        {
            flow = new StackDistFlow(<#initializer#>, <#initializer#>);
            break;
        }
        default:
        {
            break;
        }
    }
    return flow;
}

Flow::Flow(const std::string &flow_name)
{
    flow_dir = flow_name;
    Utils::CreateDirectory(flow_dir);
}
