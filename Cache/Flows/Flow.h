//
// Created by cat on 9/25/16.
//

#pragma once
#include "../Generators/Request.h"
enum FlowType {FFILE, FGENERATOR};

class Flow
{
public:
    virtual ~Flow(){};
    virtual Request* GetRequest() = 0;

    static inline const char* toString(FlowType type)
    {
        switch (type)
        {
            case FFILE:          return "FFILE";
            case FGENERATOR:     return "FGENERATOR";
            default:             return "Unknown flow type";
        }
    }
};