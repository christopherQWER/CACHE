//
// Created by cat on 9/25/16.
//

#pragma once
#include "Cache.h"
#include "../Utils/DefinedConstants.h"
#include "../Loggers/Logger.h"

class Lru : public Cache
{
public:


    Lru(ByteSize capacity);
    ~Lru();

    void ShowCache(Logger *pLogger);
    void AddToCache(Request& newRequest);
    void ReorganizeCache(const Request& newRequest);
    void InsertNewRequest(const Request& newRequest);
    void DeleteOldRequest();
};