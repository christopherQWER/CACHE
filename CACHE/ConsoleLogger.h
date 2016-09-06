#pragma once
#include <iostream>
#include <ctime>
using namespace std;

#pragma warning(disable : 4996)
#define UTC (3)

class ConsoleLogger
{
public:
	ConsoleLogger();
	~ConsoleLogger();

	static void StartLog();
	//TODO: Fix signature of function: function must get unlimited number of args
	static void ShowRequestInfo(int req_number, unsigned int asu, unsigned int lba);
	static void ShowHitRate(double hit_rate);
	static void EndLog();
};

