//
// Created by cat on 9/25/16.
//
#pragma once
#include "Cache.h"
#define DEBUG

#ifndef CACHE_LRU_H
#define CACHE_LRU_H


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
