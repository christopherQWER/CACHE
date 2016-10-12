//
// Created by cat on 9/25/16.
//
#pragma once
#include <list>
#include <map>
#include <fstream>
#include "Request.h"

#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

class Cache
{
protected:
    double _hit;
    double _miss;
    double _request_counter;
    Byte_size _max_capasity;
    Stack_dist _stack_dist;
    std::list<Request> _list_store;

public:
    Hit_rate _hit_rate;
    Byte_size _curr_capasity;
    std::map<Lba, list_itr> _map_store;

    Cache();
    Cache(Byte_size capasity);
    virtual ~Cache(){};

    bool IsInCache(Lba cell_address);
    bool IsCacheFull(Byte_size request_size) const;
    Hit_rate CalculateHitRate();
    Stack_dist CalculateStackDistance();
};


#endif //CACHE_CACHE_H
