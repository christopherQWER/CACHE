//
// Created by cat on 9/25/16.
//
#pragma once
#include <ctime>
#include "Cache.h"
#include "../Utils/Utils.h"
#include "../Loggers/Logger.h"
#ifndef CACHE_LRU_H
#define CACHE_LRU_H

class Lru : public Cache
{
public:
    /**
     * [Constructor]
     * @param capacity [cache capasity]
     */
    Lru(ByteSize capacity);

    /**
     * [Destructor]
     */
    ~Lru();

    void LRU(Request &newRequest);
    void ReorganizeCache(const Request &newRequest);
    void InsertNewRequest(const Request &newRequest);
    void DeleteOldRequest();
};


#endif //CACHE_LRU_H
