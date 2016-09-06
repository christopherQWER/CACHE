#pragma once
#include "Cache.h"
#define DEBUG

class Lru : public CACHE
{
public:
	Lru(BYTE_SIZE capasity);
	~Lru();

	void LRU(REQUEST newRequest);

	void ReorganizeCache(REQUEST newRequest);
	void InsertNewRequest(REQUEST newRequest);
	void DeleteOldRequest();
};

