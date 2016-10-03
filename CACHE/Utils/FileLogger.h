//
// Created by cat on 10/4/16.
//

#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#ifndef CACHE_FILELOGGER_H
#define CACHE_FILELOGGER_H
#define UTC (3)
#define LOG_PATH "logs/log.txt"


class FileLogger {
public:
    FileLogger();
    ~FileLogger();
};


#endif //CACHE_FILELOGGER_H
