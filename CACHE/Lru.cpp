#include "Lru.h"
#include "ConsoleLogger.h"
using namespace std;

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
		ConsoleLogger::ShowLogText("Hit to cache.\n");
	}
	else
	{
		if (IsCacheFull(newRequest._size))
		{
			DeleteOldRequest();
			_miss++;
			ConsoleLogger::ShowLogText("\n\tCache is full...clear... ");
		}
		InsertNewRequest(newRequest);
		_curr_capasity += newRequest._size;
		ConsoleLogger::ShowLogText("Request added to cache!\n");
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
	ITERATOR it = _list_store.begin();
	_map_store.insert(pair<LBA, ITERATOR>(newRequest._lba, it));
}

void Lru::DeleteOldRequest()
{
	//pointer to the last element which must be erased
	ITERATOR it_last = --(_list_store.end());
	_curr_capasity -= it_last->_size;

	_map_store.erase(it_last->_lba);
	_list_store.pop_back();
}