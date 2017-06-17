//
// Created by cat on 9/25/16.
//

#include "Lru.h"
#define LEVEL DEBUG
#define TYPE LCONSOLE
using namespace std;

Lru::Lru(ByteSize capacity) : Cache(capacity)
{
}

Lru::~Lru()
{
    _list_store.clear();
    _map_store.clear();
    _max_capacity = 0;
    _hit = 0;
    _miss = 0;
    _request_counter = 0;
    _curr_capacity = 0;
    _curr_size = 0;
}

void Lru::AddToCache(Request& newRequest)
{
    Logger *pLogger = Logger::CreateLogger(TYPE);
    StackDist stack_dist = 0;

    unordered_map<Lba, StorType::iterator>::iterator it = _map_store.begin();
    if (IsInCache(newRequest._lba, it))
    {
        stack_dist = distance(_list_store.begin(), it->second);
        ReorganizeCache(newRequest);
        _hit++;
        newRequest._is_Hit = true;
//        pLogger->ShowLogText(LEVEL, "Hit to cache. Time: " +
//                to_string(newRequest._timestamp) + "\n" );
    }
    else
    {
        if (IsCacheFull(newRequest._size))
        {
            stack_dist = _curr_size + 1;
            DeleteOldRequest();
            _miss++;
            //pLogger->ShowLogText(LEVEL, "\n\tCache is full...clear... ");
        }
        else
        {
            stack_dist = 0;
        }
        InsertNewRequest(newRequest);
        _curr_capacity += newRequest._size;
//        pLogger->ShowLogText(LEVEL, "Request added to cache! Time: " +
//                to_string(newRequest._timestamp) + "\n");
    }
    _request_counter++;
    newRequest._stack_distance = stack_dist;
//    pLogger->ShowLogText(LEVEL, "Current asu: " + to_string(newRequest._asu));
//    ShowCache(pLogger);
//    pLogger->ShowLogText(LEVEL, "Current stack dist: " + to_string(stack_dist));
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

void Lru::ShowCache(Logger *pLogger)
{
    for (Request& request_it : _list_store)
    {
        pLogger->ShowLogText(LEVEL, to_string(request_it._lba));
    }
}
