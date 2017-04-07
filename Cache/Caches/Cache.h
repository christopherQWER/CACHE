//
// Created by cat on 9/25/16.
//

#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include "../Generators/Request.h"
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

    /// Average stack distance in all experiments
    StackDist _avg_stack_dist;

    /// Inner storage
    StorType _list_store;

public:
    /// Number of requests since experiment has begun
    int _request_counter;

    /// Average hit rate of requests
    HitRate _hit_rate;

    /// Current capaсity of the cache in bytes
    ByteSize _curr_capacity;

    /// Current number of element
    ByteSize _curr_size;

     /// Storage, contains logical block address as key and
     /// iterator pointed to corresponding request body as value
     MapStorage _map_store;

    /// \brief
    /// \param capacity [Specifies the common cache size (_max_capaсity)]
    Cache(ByteSize capacity);

    ///
    virtual ~Cache(){};

     /// \brief                 [Checks, if request has already been in cache.]
     /// \param cell_address
     /// \param it
     /// \return                [true if request is already existed in cache and false otherwise]
    bool IsInCache(Lba cell_address, std::unordered_map<Lba, StorType::iterator>::iterator &it);

    ///
    /// \param request_size
    /// \return
    bool IsCacheFull(ByteSize request_size) const;

    ///
    /// \param new_capasity
    void ChangeCacheCapasity(ByteSize new_capasity);

    ///
    /// \return
    HitRate CalculateHitRate();

    ///
    /// \return
    StackDist CalculateAvgStackDistance();
};