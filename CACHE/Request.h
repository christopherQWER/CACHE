//
// Created by cat on 9/25/16.
//
#pragma once
#include <iostream>
#include <deque>
#include <random>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Utils/Types.h"

#ifndef CACHE_REQUEST_H
#define CACHE_REQUEST_H

//Size of standard memory cell
#define _CELL_SIZE_ 512

#define LOW_ADDRESS_BOUND 5000
#define UP_ADDRESS_BOUND 500000

class Request
{
public:
    Asu _asu;					/* Application specific unit */
    Lba _lba;					/* Logical block address */
    Byte_size _size;			/* Size of data in bytes */
    Op_code _opcode;			/* Read or write request */
    Timestamp _timestamp;		/* Time of start */


    Request();
    Request(Asu asu, Lba lba, Byte_size size, Op_code opcode, Timestamp timestamp);
    ~Request();
    static void GenerateRequest(Request& rq);
    static void ParseRequest(std::string traceLog, std::deque<Request>& reqList);


    static Asu GetRandomAsu();
    static Lba GetRandomLba();
    static Op_code GetReadOpCode();
    static Op_code GetWriteOpCode();
    static Timestamp GetCurrentTime();
};

typedef std::list<Request>::iterator list_itr;
#endif //CACHE_REQUEST_H
