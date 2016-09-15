#pragma once
#include <list>
#include <map>
#include <fstream>
#include "Request.h"

typedef std::list<Request>::iterator ITERATOR;

class Cache
{
protected:
	double _request_counter;
	BYTE_SIZE _max_capasity;
	double _hit;
	double _miss;
	std::list<Request> _list_store;

public:
	BYTE_SIZE _curr_capasity;
	double _hit_rate;
	std::map<LBA, ITERATOR> _map_store;

	Cache();
	Cache(BYTE_SIZE capasity);
	~Cache();

	bool IsInCache(LBA cell_address);
	bool IsCacheFull(BYTE_SIZE request_size);
	double CalculateHitRate();
};