//
// Created by cat on 10/8/16.
//

#pragma once
#include <iostream>
#include <algorithm>
#include "../Requests/Request.h"
#include "../Utils/Types.h"
#include "Flow.h"


class StackDistFlow : public Flow
{
public:
    StackDistFlow();
    ~StackDistFlow();

    Request* GetRequest();

private:
    /// Time since begin of experiment
    Timestamp _beginning_time;
};