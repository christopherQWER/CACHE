//
// Created by cat on 9/25/16.
//

#include "Cache.h"
using namespace std;

Cache::Cache(ByteSize capacity)
{
    _max_capacity = capacity;
    _curr_capacity = 0;
    _curr_size = 0;
    _request_counter = 0;
    _hit = 0;
    _miss = 0;
    _hit_rate = 0;
    _avg_stack_dist = 0;
}

Cache::Cache()
{
}

bool Cache::IsInCache(Lba cell_address, std::unordered_map<Lba, StorType::iterator>::iterator &it)
{
    it = _map_store.find(cell_address);
    return !(it == _map_store.end());
}

bool Cache::IsCacheFull(ByteSize request_size) const
{
    return _curr_capacity + request_size > _max_capacity;
}

HitRate Cache::CalculateHitRate()
{
    if (_request_counter == 0)
    {
        return -1;
    }
    _hit_rate = _hit / _request_counter;
    return _hit_rate;
}

StackDist Cache::CalculateAvgStackDistance()
{
    if (_hit == 0)
    {
        return -1;
    }
    _avg_stack_dist = _avg_stack_dist / _hit;
    return _avg_stack_dist;
}

void Cache::ChangeCacheCapasity(ByteSize new_capasity)
{
    _max_capacity = new_capasity;
}
