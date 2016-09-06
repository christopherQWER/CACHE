#include "Cache.h"


CACHE::CACHE(BYTE_SIZE capasity)
{
	_max_capasity = capasity;
	_curr_capasity = 0;
	_request_counter = 0;
	_hit = 0;
	_miss = 0;
	_hit_rate = 0;
}

CACHE::~CACHE()
{

}

bool CACHE::IsInCache(LBA cell_address)
{
	if (_map_store.find(cell_address) == _map_store.end())
	{
		return false;
	}
	return true;
}

bool CACHE::IsCacheFull(BYTE_SIZE request_size)
{
	if (_curr_capasity + request_size <= _max_capasity)
	{
		return false;
	}
	return true;
}

double CACHE::CalculateHitRate()
{
	if (_request_counter == 0)
	{
		return 0;
	}
	_hit_rate = (double)_hit / (double)_request_counter;
	return _hit_rate;
}
