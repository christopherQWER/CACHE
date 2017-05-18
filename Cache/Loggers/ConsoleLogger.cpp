//
// Created by cat on 9/25/16.
//

#include "ConsoleLogger.h"
using namespace std;

ConsoleLogger::ConsoleLogger()
{
    _start_time = 0;
    _end_time = 0;
}

ConsoleLogger::~ConsoleLogger()
{
    delete this;
}


void ConsoleLogger::StartLog()
{
    struct tm *ptm;
    time(&_start_time);
    ptm = gmtime(&_start_time);
    printf("I'm started at: %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
    printf("\n");
}

void ConsoleLogger::ShowRequestInfo(Level log_Lvl, int req_number, Asu asu, Lba lba, Timestamp time)
{
    if (log_Lvl == DEBUG)
    {
        printf("Request %d: asu - %u, lba - %u, timestamp - %f. ", req_number, asu, lba, time);
    }
}

void ConsoleLogger::ShowLogText(Level log_Lvl, const string &text)
{
    if (log_Lvl == DEBUG)
    {
        printf("%s: %s", toString(log_Lvl), text.c_str());
    }
}

void ConsoleLogger::ShowHitRate(Level log_Lvl, HitRate hit_rate)
{
    if (log_Lvl == DEBUG)
    {
        cout << endl;
        cout << "Hitrate: " << hit_rate << endl;
    }
}

void ConsoleLogger::ShowStackDistance(Level log_Lvl, StackDist stack_dist)
{
    if (log_Lvl == DEBUG)
    {
        cout << endl;
        cout << "Stack distance: " << stack_dist << endl;
    }
}

void ConsoleLogger::EndLog()
{
    struct tm *ptm;
    time(&_end_time);
    ptm = gmtime(&_end_time);
    printf("\nI'm ended at: %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
    printf("\n");
}
