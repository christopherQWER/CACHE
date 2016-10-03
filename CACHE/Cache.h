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
typedef std::list<Request>::iterator LIST_ITR;

class Cache
{
protected:
    double _request_counter;
    BYTE_SIZE _max_capasity;
    double _hit;
    double _miss;
    unsigned long long _stack_dist;
    std::list<Request> _list_store;

public:
    BYTE_SIZE _curr_capasity;
    double _hit_rate;
    std::map<LBA, LIST_ITR> _map_store;

    Cache();
    Cache(BYTE_SIZE capasity);
    ~Cache();

    bool IsInCache(LBA cell_address);
    bool IsCacheFull(BYTE_SIZE request_size) const;
    double CalculateHitRate();
    long long CalculateStackDistance();
};


#endif //CACHE_CACHE_H
