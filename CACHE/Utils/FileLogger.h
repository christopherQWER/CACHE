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
    //TODO: Fix signature of function: function must get unlimited number of args
    void ShowRequestInfo(int req_number, Asu asu, Lba lba, Timestamp time);
    void ShowLogText(std::string text);
    void ShowHitRate(Hit_rate hit_rate);
    void ShowStackDistance(Stack_dist stack_dist);
    void EndLog();
};


#endif //CACHE_FILELOGGER_H
