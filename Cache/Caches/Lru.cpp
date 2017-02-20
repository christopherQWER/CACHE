//
// Created by cat on 9/25/16.
//

#include "Lru.h"
using namespace std;
#define LEVEL INFO
#define TYPE LCONSOLE

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

    std::unordered_map<Lba, StorType::iterator>::iterator it = _map_store.begin();
    if (IsInCache(newRequest._lba, it))
    {
        stack_dist = distance(_list_store.begin(), it->second) + 1;
        ReorganizeCache(newRequest);
        _hit++;
        pLogger->ShowLogText(DEBUG, "Hit to cache.\n");
    }
    else
    {
        if (IsCacheFull(newRequest._size))
        {
            stack_dist = _curr_size + 1;
            DeleteOldRequest();
            _miss++;
#ifdef DEBUG
            pLogger->ShowLogText("\n\tCache is full...clear... ");
#endif
        }
        else
        {
            stack_dist = 1;
        }
        InsertNewRequest(newRequest);
        _curr_capacity += newRequest._size;
#ifdef DEBUG
        pLogger->ShowLogText("Request added to cache!\n");
#endif
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