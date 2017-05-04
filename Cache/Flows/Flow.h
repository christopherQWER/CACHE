//
// Created by cat on 9/25/16.
//

#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include "../Generators/Request.h"
#include "../Utils/Utils.h"

enum FlowType { FFILE = 0, FGENERATOR };

class Flow
{
public:
    std::string flow_dir;

    Flow(const std::string &flow_name);
    virtual ~Flow(){};
    virtual Request* GetRequest() = 0;

    static Flow* CreateFlow(FlowType type);

    static inline const char* toString(FlowType type)
    {
        switch (type)
        {
            case FFILE:          return "FFILE";
            case FGENERATOR:     return "FGENERATOR";
            default:             return "Unknown flow type";
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