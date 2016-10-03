//
// Created by cat on 9/25/16.
//

#include "Lru.h"
#include "Utils/ConsoleLogger.h"
using namespace std;

#define DEBUG

Lru::Lru(BYTE_SIZE capasity) : Cache(capasity)
{

}

Lru::~Lru()
{
}


void Lru::LRU(Request newRequest)
{
    if (IsInCache(newRequest._lba))
    {
        _stack_dist += distance(_list_store.begin(), _map_store.find(newRequest._lba)->second) + 1;
        ReorganizeCache(newRequest);
        _hit++;
#ifdef DEBUG
        ConsoleLogger::ShowLogText("Hit to cache.\n");
#endif
    }
    else
    {
        if (IsCacheFull(newRequest._size))
        {
            DeleteOldRequest();
            _miss++;
#ifdef DEBUG
            ConsoleLogger::ShowLogText("\n\tCache is full...clear... ");
#endif
        }
        InsertNewRequest(newRequest);
        _curr_capasity += newRequest._size;
#ifdef DEBUG
        ConsoleLogger::ShowLogText("Request added to cache!\n");
#endif
    }
    _request_counter++;
}


void Lru::ReorganizeCache(Request newRequest)
{
    _list_store.erase(_map_store[newRequest._lba]);
    _list_store.push_front(newRequest);
    _map_store[newRequest._lba] = _list_store.begin();
}

void Lru::InsertNewRequest(Request newRequest)
{
    _list_store.push_front(newRequest);
    LIST_ITR it = _list_store.begin();
    _map_store.insert(pair<LBA, LIST_ITR>(newRequest._lba, it));
}

void Lru::DeleteOldRequest()
{
    //pointer to the last element which must be erased
    LIST_ITR it_last = --(_list_store.end());
    _curr_capasity -= it_last->_size;

    _map_store.erase(it_last->_lba);
    _list_store.pop_back();
}