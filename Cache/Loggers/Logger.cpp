//
// Created by cat on 10/5/16.
//

#include "Logger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

Logger* Logger::CreateLogger(Type type)
{
    Logger *p = nullptr;
    switch (type)
    {
        case LCONSOLE:
            p = new ConsoleLogger();
            break;

        case LFILE:
            p = new FileLogger();
            break;

        default:
            printf("There is no such logger type!");
    }
    return p;
}
