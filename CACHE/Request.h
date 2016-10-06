//
// Created by cat on 9/25/16.
//
#pragma once
#include <iostream>
#include <vector>
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
    ASU _asu;					/* Application specific unit */
    LBA _lba;					/* Logical block address */
    BYTE_SIZE _size;			/* Size of data in bytes */
    OP_CODE _opcode;			/* Read or write request */
    TIMESTAMP _timestamp;		/* Time of start */


    Request();
    Request(ASU asu, LBA lba, BYTE_SIZE size, OP_CODE opcode, TIMESTAMP timestamp);
    ~Request();
    static void GenerateRequest(Request& rq);
    static void ParseRequest(std::string traceLog, std::vector<Request>& reqList);


    static ASU GetRandomAsu();
    static LBA GetRandomLba();
    static OP_CODE GetReadOpCode();
    static OP_CODE GetWriteOpCode();
    static TIMESTAMP GetCurrentTime();
};

typedef std::list<Request>::iterator LIST_ITR;
#endif //CACHE_REQUEST_H
