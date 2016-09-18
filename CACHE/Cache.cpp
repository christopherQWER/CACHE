#include "Cache.h"
using namespace std;

Cache::Cache(BYTE_SIZE capasity)
{
	_max_capasity = capasity;
	_curr_capasity = 0;
	_request_counter = 0;
	_hit = 0;
	_miss = 0;
	_hit_rate = 0;
	_stack_dist = 0;
}

Cache::~Cache()
{

}

bool Cache::IsInCache(LBA cell_address)
{
	if (_map_store.find(cell_address) == _map_store.end())
	{
		return false;
	}
	return true;
}

bool Cache::IsCacheFull(BYTE_SIZE request_size) const
{
	if (_curr_capasity + request_size <= _max_capasity)
	{
		return false;
	}
	return true;
}

double Cache::CalculateHitRate()
{
	if (_request_counter == 0)
	{
		return -1;
	}
	_hit_rate = (double)_hit / (double)_request_counter;
	return _hit_rate;
}

unsigned long long Cache::CalculateStackDistance()
{
	if (_request_counter == 0)
	{
		return -1;
	}
	_stack_dist = _stack_dist / _request_counter;
	return _stack_dist;
}
