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
    BYTE_SIZE _max_capasity;
    STACK_DIST _stack_dist;
    std::list<Request> _list_store;

public:
    HIT_RATE _hit_rate;
    BYTE_SIZE _curr_capasity;
    std::map<LBA, LIST_ITR> _map_store;

    Cache();
    Cache(BYTE_SIZE capasity);
    virtual ~Cache(){};

    bool IsInCache(LBA cell_address);
    bool IsCacheFull(BYTE_SIZE request_size) const;
    HIT_RATE CalculateHitRate();
    STACK_DIST CalculateStackDistance();
};


#endif //CACHE_CACHE_H
