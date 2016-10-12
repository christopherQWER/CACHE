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
}


void ConsoleLogger::StartLog()
{
    struct tm *ptm;
    time(&_start_time);
    ptm = gmtime(&_start_time);
    printf("I'm started at: %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
    printf("\n");
}

void ConsoleLogger::ShowRequestInfo(int req_number, Asu asu, Lba lba, Timestamp time)
{
    printf("Request %d: asu - %u, lba - %u, timestamp - %f. ", req_number, asu, lba, time);
}

void ConsoleLogger::ShowLogText(string text)
{
    printf("%s", text.c_str());
}

void ConsoleLogger::ShowHitRate(Hit_rate hit_rate)
{
    cout << endl;
    cout << "Hitrate: " << hit_rate << endl;
}

void ConsoleLogger::ShowStackDistance(Stack_dist stack_dist)
{
    cout << endl;
    cout << "Stack distance: " << stack_dist << endl;
}

void ConsoleLogger::EndLog()
{
    struct tm *ptm;
    time(&_end_time);
    ptm = gmtime(&_end_time);
    printf("\nI'm ended at: %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
    printf("\n");
}
