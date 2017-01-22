//
// Created by cat on 9/25/16.
//
#pragma once
#include <list>
#include <unordered_map>
#include <fstream>
#include "../Generators/Request.h"
#include "../Utils/Utils.h"
#include "../Utils/Types.h"
#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H
typedef std::list<Request> StorType;

class Cache
{
protected:
    double _hit;
    double _miss;

    /**
     * [Maximal capacity of cache]
     */
    ByteSize _max_capacity;

    /**
     * [Average stack distance in all experiments]
     */
    StackDist _avg_stack_dist;
    StorType _list_store;

public:
    /**
     * [Number of requests since experiment has begun]
     */
    int _request_counter;

    /**
     * [Average hit rate of requests]
     */
    HitRate _hit_rate;

    /**
     * [Current capaсity of the cache]
     */
    ByteSize _curr_capacity;

    /**
     * [Current number of element]
     */
    ByteSize _curr_size;
    /**
     * [Storage, contains logical block address as key and
     * iterator pointed to corresponding request body as value]
     */
    std::unordered_map<Lba, StorType::iterator> _map_store;

    /**
     * [Default constructor]
     */
    Cache();

    /**
     * [Constructor]
     * @param capaсity [Specifies the common cache size (_max_capaсity).]
     */
    Cache(ByteSize capacity);

    /**
     * [Virtual destructor]
     */
    virtual ~Cache(){};

    /**
     * [Checks, if request has already been in cache.]
     * @param cell_address
     * @return [true if request is already existed in cache and false otherwise]
     */
    bool IsInCache(Lba cell_address, std::unordered_map<Lba, StorType::iterator>::iterator &it);
    bool IsCacheFull(ByteSize request_size) const;
    void ChangeCacheCapasity(ByteSize new_capasity);
    HitRate CalculateHitRate();
    StackDist CalculateAvgStackDistance();
};


#endif //CACHE_CACHE_H
