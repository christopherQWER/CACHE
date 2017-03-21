//
// Created by cat on 10/4/16.
//

#pragma once
#include <iostream>
#include <string>
#include "../Utils/Types.h"
#define UTC (3)

enum LoggerType {LCONSOLE, LFILE};
enum Level {INFO, DEBUG, ERROR};

class Logger
{
public:
    time_t _start_time;
    time_t _end_time;

    virtual ~Logger(){};
    virtual void StartLog() = 0;

    /// \brief              [Show detailed info about request]
    /// \param log_Lvl
    /// \param req_number
    /// \param asu
    /// \param lba
    /// \param time
    virtual void ShowRequestInfo(Level log_Lvl, int req_number, Asu asu, Lba lba, Timestamp time) = 0;

    /// \brief          [Show log string]
    /// \param log_Lvl
    /// \param text
    virtual void ShowLogText(Level log_Lvl, const std::string &text) = 0;
    virtual void ShowHitRate(Level log_Lvl, HitRate hit_rate) = 0;
    virtual void ShowStackDistance(Level log_Lvl, StackDist stack_dist) = 0;
    virtual void EndLog() = 0;

    static Logger* CreateLogger(LoggerType type);
    static inline const char* toString(Level lvl)
    {
        switch (lvl)
        {
            case INFO:      return "[INFO]";
            case DEBUG:     return "[DEBUG]";
            case ERROR:     return "[ERROR]";
            default:        return "[Unknown level]";
        }
    }
    static inline const char* toString(LoggerType type)
    {
        switch (type)
        {
            case LCONSOLE:  return "LCONSOLE";
            case LFILE:     return "LFILE";
            default:        return "Unknown type";
        }
    }
};