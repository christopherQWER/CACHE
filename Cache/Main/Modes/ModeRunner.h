//
// Created by cat on 4/2/17.
//
#include "../../Xml/MainConfig.h"
#include "../../Xml/XmlModes/XmlAnalyzeMode.h"
#include "../../Xml/XmlModes/XmlGenerateMode.h"
#include "../../Xml/XmlModes/XmlSimulateMode.h"
#include "../../Flows/TraceFileFlow.h"
#include "../../Flows/StackDistFlow.h"
#include "../../Storages/SharedStorage.h"
#include "../../Storages/StaticPartial.h"

// Enumeration for program modes
enum Mode{
    TRACE_ANALYZE = 1,
    GENERATE,
    SIMULATE,
    EXIT
};

/// \brief         [Function turn elements of Mode type to string representation]
/// \param mode    [program mode]
/// \return        [string representation of Mode]
static const char* toString(Mode mode)
{
    switch (mode)
    {
        case TRACE_ANALYZE: { return "TRACE_ANALYZE";}
        case GENERATE:      { return "GENERATE";}
        case SIMULATE:      { return "SIMULATE";}
        case EXIT:          { return "EXIT";}
        default:            { return "UNKNOWN";}
    }
}

void RunTraceAnalyseMode(Config my_config);
void RunSimulateMode(Config my_config);
void RunGenerateMode(Config my_config);