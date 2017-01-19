//
// Created by cat on 9/25/16.
//
#pragma once
#include "Logger.h"
#ifndef CACHE_CONSOLELOGGER_H
#define CACHE_CONSOLELOGGER_H


class ConsoleLogger : public Logger
{
public:
    ConsoleLogger();
    ~ConsoleLogger();

    void StartLog();
    //TODO: Fix signature of function: function must get unlimited number of args
    void ShowRequestInfo(int req_number, Asu asu, Lba lba, Timestamp time);
    void ShowLogText(const std::string &text);
    void ShowHitRate(HitRate hit_rate);
    void ShowStackDistance(StackDist stack_dist);
    void EndLog();
};


#endif //CACHE_CONSOLELOGGER_H