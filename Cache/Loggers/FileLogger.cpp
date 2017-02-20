//
// Created by cat on 10/4/16.
//

#include "FileLogger.h"
using namespace std;

FILE * file;

FileLogger::FileLogger()
{
    _start_time = 0;
    _end_time = 0;
    file = fopen(LOG_PATH, "a");
    if (file)
    {
        fclose(file);
    }
}

FileLogger::~FileLogger()
{
}

void FileLogger::StartLog()
{
    file = fopen(LOG_PATH, "a");
    struct tm *ptm;
    time(&_start_time);
    ptm = gmtime(&_start_time);
    fprintf(file, "I'm started at: %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
    fprintf(file, "\n");
    fclose(file);
}

void FileLogger::ShowRequestInfo(Level log_Lvl, int req_number, Asu asu, Lba lba, Timestamp time)
{
    if (log_Lvl == DEBUG)
    {
        file = fopen(LOG_PATH, "a");
        fprintf(file, "Request %d: asu - %u, lba - %u, timestamp - %f. ", req_number, asu, lba, time);
        fclose(file);
    }
}

void FileLogger::ShowLogText(Level log_Lvl, const std::string &text)
{
    file = fopen(LOG_PATH, "a");
    fprintf(file, "%s: %s", toString(log_Lvl), text.c_str());
    fclose(file);
}

void FileLogger::ShowHitRate(Level log_Lvl, HitRate hit_rate)
{
    if (log_Lvl == DEBUG)
    {
        file = fopen(LOG_PATH, "a");
        fprintf(file, "Hitrate: %f\n", hit_rate);
        fclose(file);
    }
}

void FileLogger::ShowStackDistance(Level log_Lvl, StackDist stack_dist)
{
    if (log_Lvl == DEBUG)
    {
        file = fopen(LOG_PATH, "a");
        fprintf(file, "Stack distance: %Lfll", stack_dist);
        fclose(file);
    }
}

void FileLogger::EndLog()
{
    file = fopen(LOG_PATH, "a");
    struct tm *ptm;
    time(&_end_time);
    ptm = gmtime(&_end_time);
    fprintf(file, "\nI'm ended at: %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
    fprintf(file, "\n");
    fclose(file);
}
