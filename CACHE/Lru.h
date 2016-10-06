//
// Created by cat on 9/25/16.
//
#pragma once
#include "Cache.h"
#include "Utils/Logger.h"
#ifndef CACHE_LRU_H
#define CACHE_LRU_H
#define _1_GB_IN_BYTES_ 1073741824

class Lru : public Cache
{
public:
    Lru(BYTE_SIZE capasity);
    ~Lru();

    void LRU(Request newRequest);

    void ReorganizeCache(Request newRequest);
    void InsertNewRequest(Request newRequest);
    void DeleteOldRequest();
};


#endif //CACHE_LRU_H
