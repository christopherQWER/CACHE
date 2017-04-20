//
// Created by cat on 9/25/16.
//

#include "Lru.h"
#include "../Loggers/Logger.h"

#define LEVEL INFO
#define TYPE LCONSOLE
using namespace std;

Lru::Lru(ByteSize capacity) : Cache(capacity)
{
}

Lru::~Lru()
{
}

void Lru::LRU(Request &newRequest)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);
    StackDist stack_dist = 0;

    unordered_map<Lba, StorType::iterator>::iterator it = _map_store.begin();
    if (IsInCache(newRequest._lba, it))
    {
        stack_dist = distance(_list_store.begin(), it->second) + 1;
        ReorganizeCache(newRequest);
        _hit++;
//        pLogger->ShowLogText(DEBUG, "Hit to cache. Time: " +
//                to_string(newRequest._timestamp) + "\n" );
    }
    else
    {
        if (IsCacheFull(newRequest._size))
        {
            stack_dist = _curr_size + 1;
            DeleteOldRequest();
            _miss++;
//            pLogger->ShowLogText(DEBUG, "\n\tCache is full...clear... ");
        }
        else
        {
            stack_dist = 1;
        }
        InsertNewRequest(newRequest);
        _curr_capacity += newRequest._size;
//        pLogger->ShowLogText(DEBUG, "Request added to cache! Time: " +
//                to_string(newRequest._timestamp) + "\n");
    }
    _request_counter++;
    newRequest._stack_distance = stack_dist;
}


void Lru::ReorganizeCache(const Request &newRequest)
{
    _list_store.erase(_map_store[newRequest._lba]);
    _list_store.push_front(newRequest);
    _map_store[newRequest._lba] = _list_store.begin();
}

void Lru::Resize(ByteSize new_size)
{
    _max_capacity = new_size;
    if (_curr_capacity > _max_capacity)
    {
        ByteSize diff = _curr_capacity - _max_capacity;
        ByteSize number_of_pos = 0;
        if( (diff % _CELL_SIZE_) == 0)
        {
            number_of_pos = diff / _CELL_SIZE_;
        }
        else
        {
            number_of_pos = diff / _CELL_SIZE_ + 1;
        }
        for (int i = 0; i < number_of_pos; i++)
        {
            DeleteOldRequest();
        }
    }
}

void Lru::InsertNewRequest(const Request &newRequest)
{
    _list_store.push_front(newRequest);
    _curr_size++;
    StorType::iterator it = _list_store.begin();
    _map_store.insert(pair<Lba, StorType::iterator>(newRequest._lba, it));
}

void Lru::DeleteOldRequest()
{
    //pointer to the last element which must be erased
    StorType::iterator it_last = --(_list_store.end());
    _curr_capacity -= it_last->_size;

    _map_store.erase(it_last->_lba);
    _list_store.pop_back();
    _curr_size--;
}