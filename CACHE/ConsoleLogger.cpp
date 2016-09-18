#include "ConsoleLogger.h"
using namespace std;

time_t _start_time;
time_t _end_time;

ConsoleLogger::ConsoleLogger()
{
	_start_time = NULL;
	_end_time = NULL;
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

void ConsoleLogger::ShowRequestInfo(int req_number, unsigned int asu, unsigned int lba)
{
	printf("Request %d: asu - %u, lba - %u. ", req_number, asu, lba);
}

void ConsoleLogger::ShowLogText(string text)
{
	printf("%s", text.c_str());
}

void ConsoleLogger::ShowHitRate(double hit_rate)
{
	cout << endl;
	cout << "Hitrate: " << hit_rate << endl;
}

void ConsoleLogger::EndLog()
{
	struct tm *ptm;
	time(&_end_time);
	ptm = gmtime(&_end_time);
	printf("\nI'm ended at: %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
	printf("\n");
}
