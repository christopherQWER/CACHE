//
// Created by cat on 10/4/16.
//

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Logger.h"

class FileLogger : public Logger
{
public:
    std::string current_log_path;
    FileLogger(std::string log_file = "");
    ~FileLogger();

    void StartLog();
    void ShowRequestInfo(Level log_Lvl, int req_number, Asu asu, Lba lba, Timestamp time);
    void ShowLogText(Level log_Lvl, const std::string &text);
    void ShowHitRate(Level log_Lvl, HitRate hit_rate);
    void ShowStackDistance(Level log_Lvl, StackDist stack_dist);
    void EndLog();
};