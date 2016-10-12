//
// Created by cat on 9/25/16.
//
#pragma once
#include "Cache.h"
#include "Utils/Logger.h"
#ifndef CACHE_LRU_H
#define CACHE_LRU_H

class Lru : public Cache
{
public:
    Lru(Byte_size capasity);
    ~Lru();

    void LRU(Request newRequest);
    void ReorganizeCache(Request newRequest);
    void InsertNewRequest(Request newRequest);
    void DeleteOldRequest();
};


#endif //CACHE_LRU_H
