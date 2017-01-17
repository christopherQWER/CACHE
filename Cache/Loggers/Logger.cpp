//
// Created by cat on 10/5/16.
//

#include "Logger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

Logger* Logger::CreateLogger(LoggerType type)
{
    Logger *p = nullptr;
    switch (type)
    {
        case CONSOLE_LOGGER:
            p = new ConsoleLogger();
            break;

        case FILE_LOGGER:
            p = new FileLogger();
            break;

        default:
            printf("There is no such logger type!");
    }
    return p;
}
