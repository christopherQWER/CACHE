//
// Created by cat on 9/25/16.
//

#include "Cache.h"
using namespace std;

Cache::Cache(Byte_size capasity)
{
    _max_capasity = capasity;
    _curr_capasity = 0;
    _request_counter = 0;
    _hit = 0;
    _miss = 0;
    _hit_rate = 0;
    _stack_dist = 0;
}

Cache::Cache()
{

}

bool Cache::IsInCache(Lba cell_address)
{
    return !(_map_store.find(cell_address) == _map_store.end());
}

bool Cache::IsCacheFull(Byte_size request_size) const
{
    return _curr_capasity + request_size > _max_capasity;
}

Hit_rate Cache::CalculateHitRate()
{
    if (_request_counter == 0)
    {
        return -1;
    }
    _hit_rate = _hit / _request_counter;
    return _hit_rate;
}

Stack_dist Cache::CalculateStackDistance()
{
    if (_hit == 0)
    {
        return -1;
    }
    _stack_dist = _stack_dist / _hit;
    return _stack_dist;
}
