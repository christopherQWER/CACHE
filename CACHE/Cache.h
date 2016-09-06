#pragma once
#include <list>
#include <map>
#include <fstream>
#include "Request.h"
using namespace std;

typedef list<REQUEST>::iterator ITERATOR;

class CACHE
{
protected:
	double _request_counter;
	BYTE_SIZE _max_capasity;
	double _hit;
	double _miss;
	list<REQUEST> _list_store;

public:
	BYTE_SIZE _curr_capasity;
	double _hit_rate;
	map<LBA, ITERATOR> _map_store;

	CACHE();
	CACHE(BYTE_SIZE capasity);
	~CACHE();

	bool IsInCache(LBA cell_address);
	bool IsCacheFull(BYTE_SIZE request_size);
	double CalculateHitRate();
};