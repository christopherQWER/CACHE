#pragma once
#include "Cache.h"
#define DEBUG

class Lru : public Cache
{
public:
	Lru(BYTE_SIZE capasity);
	~Lru();

	void LRU(Request newRequest);

	void ReorganizeCache(Request newRequest);
	void InsertNewRequest(Request newRequest);
	void DeleteOldRequest();
};

