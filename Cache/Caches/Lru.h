//
// Created by cat on 9/25/16.
//

#pragma once
#include "Cache.h"

class Lru : public Cache
{
public:
    /// \brief
    /// \param capacity []
    Lru(ByteSize capacity);

    ///
    ~Lru();

    ///
    /// \param newRequest []
    void LRU(Request &newRequest);

    ///
    /// \param newRequest []
    void ReorganizeCache(const Request &newRequest);

    ///
    /// \param newRequest []
    void InsertNewRequest(const Request &newRequest);

    ///
    void DeleteOldRequest();
};