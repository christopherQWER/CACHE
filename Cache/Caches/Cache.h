//
// Created by cat on 9/25/16.
//

#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include "../Requests/Request.h"
#include "../Utils/Types.h"

typedef std::list<Request> StorType;
typedef std::unordered_map<Lba, std::list<Request>::iterator> MapStorage;

class Cache
{
protected:
    double _hit;
    double _miss;

    /// Maximal capacity of cache in bytes
    ByteSize _max_capacity;

    /// Inner storage
    StorType _list_store;

public:
    /// Number of requests since experiment has begun
    int _request_counter;

    /// Current capaсity of the cache in bytes
    ByteSize _curr_capacity;

    /// Current number of element
    ByteSize _curr_size;

    /// Storage, contains logical block address as key and
    /// iterator pointed to corresponding request body as value
    MapStorage _map_store;

    Cache(ByteSize capacity);

    ///
    virtual ~Cache(){};
    bool IsInCache(Lba cell_address, std::unordered_map<Lba, StorType::iterator>::iterator &it);
    bool IsCacheFull(ByteSize request_size) const;
};