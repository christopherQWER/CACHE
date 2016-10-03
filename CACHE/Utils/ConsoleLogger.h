//
// Created by cat on 9/25/16.
//
#pragma once
#include <iostream>
#include <ctime>
#ifndef CACHE_CONSOLELOGGER_H
#define CACHE_CONSOLELOGGER_H
#define UTC (3)

class ConsoleLogger
{
public:
    ConsoleLogger();
    ~ConsoleLogger();

    static void StartLog();
    //TODO: Fix signature of function: function must get unlimited number of args
    static void ShowRequestInfo(int req_number, unsigned int asu, unsigned int lba);
    static void ShowLogText(std::string text);
    static void ShowHitRate(double hit_rate);
    static void ShowStackDistance(unsigned long long stack_dist);
    static void EndLog();
};


#endif //CACHE_CONSOLELOGGER_H
