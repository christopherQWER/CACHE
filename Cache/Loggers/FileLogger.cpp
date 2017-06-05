//
// Created by cat on 10/4/16.
//
#include <cstdio>
#include "FileLogger.h"
#include "../Utils/Paths.h"
#include "../Utils/Utils.h"
using namespace std;

ofstream log_file;

FileLogger::FileLogger(string log_file_path)
{
    if (log_file_path == "")
    {
        log_file_path = Utils::GetCurrentStringUnixTime() + ".txt";
    }
    current_log_path = Utils::PathCombine(string(_LOG_DIR_), log_file_path);
    _start_time = 0;
    _end_time = 0;
    log_file.open(current_log_path, fstream::out | fstream::app);
}

FileLogger::~FileLogger()
{
    log_file.close();
    delete this;
}

void FileLogger::StartLog()
{
    struct tm *ptm;
    time(&_start_time);
    ptm = gmtime(&_start_time);
    log_file << "I'm started at: " << ((ptm->tm_hour + UTC) % 24) << ":" <<
             ptm->tm_min << endl;
}

void FileLogger::ShowRequestInfo(Level log_Lvl, int req_number, Asu asu, Lba lba, Timestamp time)
{
    if (log_Lvl == DEBUG)
    {
        log_file << "Request " << req_number << ": " <<
                    "asu - " << asu << ", " <<
                    "lba - " << lba << ", " <<
                    "timestamp - " << time << ". " << endl;
    }
}

void FileLogger::ShowLogText(Level log_Lvl, const std::string &text)
{
    log_file << toString(log_Lvl)<< ": " << text.c_str() << endl;
}

void FileLogger::ShowHitRate(Level log_Lvl, HitRate hit_rate)
{
    if (log_Lvl == DEBUG)
    {
        log_file << "Hitrate: " << hit_rate << endl;
    }
}

void FileLogger::ShowStackDistance(Level log_Lvl, StackDist stack_dist)
{
    if (log_Lvl == DEBUG)
    {
        log_file << "Stack distance: " << stack_dist << endl;
    }
}

void FileLogger::EndLog()
{
    struct tm *ptm;
    time(&_end_time);
    ptm = gmtime(&_end_time);
    log_file << "I'm ended at: " << ((ptm->tm_hour + UTC) % 24) << ":" << ptm->tm_min << endl;
}
