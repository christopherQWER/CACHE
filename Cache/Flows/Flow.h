//
// Created by cat on 9/25/16.
//

#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include "../Requests/Request.h"
#include "../Utils/Utils.h"
#include "../Utils/Enums.h"

class Flow
{
public:
    FlowType current_type;
    std::string flow_dir_name;

    //static Flow* CreateFlow(FlowType type);
    virtual ~Flow() {};
    virtual Request* GetRequest() = 0;
    virtual bool IsEndOfFlow() = 0;

    static inline std::string toString(FlowType type)
    {
        switch (type)
        {
            case FFILE:          return std::string("FFILE");
            case FGENERATOR:     return std::string("FGENERATOR");
            default:             return std::string("Unknown flow stor_type");
        }
    }
    static inline FlowType toType(const char* str_repr)
    {
        if (strcmp(str_repr, "FFILE") == 0)
            return FFILE;
        else if (strcmp(str_repr, "FGENERATOR") == 0)
            return FGENERATOR;
    }
};