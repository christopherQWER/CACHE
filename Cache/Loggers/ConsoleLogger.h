//
// Created by cat on 9/25/16.
//

#pragma once
#include <iostream>
#include <string>
#include "Logger.h"

class ConsoleLogger : public Logger
{
public:
    ConsoleLogger();
    ~ConsoleLogger();

    void StartLog();
    void ShowRequestInfo(Level log_Lvl, int req_number, Asu asu, Lba lba, Timestamp time);
    void ShowLogText(Level log_Lvl, const std::string &text);
    void ShowHitRate(Level log_Lvl, HitRate hit_rate);
    void ShowStackDistance(Level log_Lvl, StackDist stack_dist);
    void EndLog();
};