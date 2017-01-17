//
// Created by cat on 9/25/16.
//

#include "Lru.h"
using namespace std;
//#define DEBUG
#define CONSOLE CONSOLE_LOGGER

Lru::Lru(ByteSize capacity) : Cache(capacity)
{
}

Lru::~Lru()
{
}

void Lru::LRU(const Request &newRequest)
{
#ifdef DEBUG
    Logger *pLogger = Logger::CreateLogger(CONSOLE);
#endif
    StackDist stack_dist = 0;

    if (IsInCache(newRequest._lba))
    {
        stack_dist = distance(_list_store.begin(), _map_store.find(newRequest._lba)->second) + 1;
        ReorganizeCache(newRequest);
        _hit++;
#ifdef DEBUG
        pLogger->ShowLogText("Hit to cache.\n");
#endif
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
    SaveStackDist(stack_dist);
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

void Lru::PDFGistogramm(const std::string &file_path)
{
    int count = 0;
    for (DistStor::iterator it = stack_dist_frequency.begin(); it != stack_dist_frequency.end(); ++it)
    {
        if (it->first == count)
        {
            Utils::AppendToFile(file_path, it->first,
                                static_cast<double>(it->second) / static_cast<double>(_request_counter));
        }
        else
        {
            Utils::AppendToFile(file_path, count, 0);
        }
        count++;
    }
}

void Lru::CDFGistogramm(const std::string &file_path)
{
    double val = 0;
    for (DistStor::iterator it = stack_dist_frequency.begin(); it != stack_dist_frequency.end(); ++it)
    {
        Utils::AppendToFile(file_path, it->first,
                            val + (static_cast<double>(it->second) / static_cast<double>(_request_counter)));

        val += (static_cast<double>(it->second) / static_cast<double>(_request_counter));
    }
}

void Lru::SaveStackDist(StackDist stack_dist)
{
    if (IsInStorage(stack_dist))
    {
        stack_dist_frequency[stack_dist]++;
    }
    else
    {
        stack_dist_frequency.insert(pair<StackDist, int>(stack_dist, 1));
    }
}

bool Lru::IsInStorage(StackDist value)
{
    return !(stack_dist_frequency.find(value) == stack_dist_frequency.end());
}