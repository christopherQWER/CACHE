//
// Created by cat on 10/4/16.
//

#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Types.h"
#define UTC (3)
#ifndef CACHE_LOGGER_H
#define CACHE_LOGGER_H

enum LoggerType {CONSOLE_LOGGER = 0, FILE_LOGGER};

class Logger
{
public:
    time_t _start_time;
    time_t _end_time;

    virtual ~Logger(){};
    virtual void StartLog() = 0;
    //TODO: Fix signature of function: function must get unlimited number of args
    virtual void ShowRequestInfo(int req_number, Asu asu, Lba lba, Timestamp time) = 0;
    virtual void ShowLogText(std::string text) = 0;
    virtual void ShowHitRate(Hit_rate hit_rate) = 0;
    virtual void ShowStackDistance(Stack_dist stack_dist) = 0;
    virtual void EndLog() = 0;

    static Logger* CreateLogger(LoggerType type);
};
#endif //CACHE_LOGGER_H
