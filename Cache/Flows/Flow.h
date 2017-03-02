//
// Created by cat on 9/25/16.
//

#ifndef CACHE_FLOW_H
#define CACHE_FLOW_H

#include <iostream>
#include <vector>
#include <list>
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


#endif //CACHE_FLOW_H
