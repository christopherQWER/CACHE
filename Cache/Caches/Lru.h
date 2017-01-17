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
typedef std::map<StackDist, int> DistStor;

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

    void LRU(const Request &newRequest);
    void ReorganizeCache(const Request &newRequest);
    void InsertNewRequest(const Request &newRequest);
    void DeleteOldRequest();

    void PDFGistogramm(const std::string &file_path);
    void CDFGistogramm(const std::string &file_path);
    void SaveStackDist(StackDist stack_dist);
    bool IsInStorage(StackDist value);

private:
    /**
     * [Frequency of stack distances occurances]
     */
    DistStor stack_dist_frequency;
};


#endif //CACHE_LRU_H
