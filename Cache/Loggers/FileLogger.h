//
// Created by cat on 10/4/16.
//

#pragma once
#include <iostream>
#include <fstream>
#include "Logger.h"
#ifndef CACHE_FILELOGGER_H
#define CACHE_FILELOGGER_H
#define LOG_PATH "logs/log.txt"

class FileLogger : public Logger
{
public:
    FileLogger();
    ~FileLogger();

    void StartLog();
    void ShowRequestInfo(Level log_Lvl, int req_number, Asu asu, Lba lba, Timestamp time);
    void ShowLogText(Level log_Lvl, const std::string &text);
    void ShowHitRate(Level log_Lvl, HitRate hit_rate);
    void ShowStackDistance(Level log_Lvl, StackDist stack_dist);
    void EndLog();
};


#endif //CACHE_FILELOGGER_H
