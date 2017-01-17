//
// Created by cat on 9/25/16.
//
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "../Generators/Request.h"
#ifndef CACHE_FLOW_H
#define CACHE_FLOW_H

class Flow
{
public:
    virtual ~Flow(){};
    virtual Request* GetRequest() = 0;
};


#endif //CACHE_FLOW_H
