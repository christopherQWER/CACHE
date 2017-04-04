//
// Created by cat on 4/2/17.
//
#include "../Xml/MainConfig.h"

// Enumeration for program modes
enum Mode{
    TRACE_ANALYZE = 1,
    SHARED_CACHE,
    PARTIAL_CACHE,
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
    case SHARED_CACHE: { return "SHARED_CACHE";}
    case PARTIAL_CACHE: { return "PARTIAL_CACHE";}
    case EXIT: {return "EXIT";}
    default: { return "UNKNOWN";}
    }
}

void RunTraceAnalyseMode(Config my_config);
void RunSharedCacheMode(Config my_config);
void RunPartialCacheMode(Config my_config);