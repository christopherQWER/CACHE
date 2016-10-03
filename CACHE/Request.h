//
// Created by cat on 9/25/16.
//
#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#ifndef CACHE_REQUEST_H
#define CACHE_REQUEST_H

//Size of standard memory cell
#define _CELL_SIZE_ 512

//Types definition
typedef unsigned int LBA;
typedef unsigned int ASU;
typedef unsigned long long BYTE_SIZE;
typedef char OP_CODE;
typedef double TIMESTAMP;

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


#endif //CACHE_REQUEST_H
