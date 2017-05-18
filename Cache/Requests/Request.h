//
// Created by cat on 9/25/16.

#pragma once
#include <iostream>
#include <deque>
#include <ctime>
#include <string>
#include "../Utils/Types.h"

/// Size of standard memory cell
#define _CELL_SIZE_ 512


class Request
{
public:
      /// Application specific unit
    Asu _asu;

     /// Logical block address
    Lba _lba;

     /// Size of data in bytes
    ByteSize _size;

     /// Read or write request
    OpCode _opcode;

     /// Time of start
    Timestamp _timestamp;

     /// Characteristic of request connected with cache
    StackDist _stack_distance;

     /// Default constructor
    Request();

     /// \brief                 Constructor
     /// \param asu             application specific unit
     /// \param lba             logical block address
     /// \param size            size of requested bytes
     /// \param opcode          operation code
     /// \param timestamp       incoming time
    Request(Asu asu, Lba lba, ByteSize size, OpCode opcode, Timestamp timestamp);
    ~Request();

     /// \brief                 Function generates request
     /// \param rq
    static void GenerateRequest(Request& rq);

    /// \brief
    /// \param traceLog
    /// \param reqList
    static void ParseRequest(const std::string &traceLog, std::deque<Request>& reqList);

    /// \brief                  Function gets all required fields from string
    /// \param request_string
    /// \param req
    /// \return
    static bool GetRequestFromString(const std::string& request_string, Request& req);

private:
    static Asu GetRandomAsu();
    static Lba GetRandomLba();
    static OpCode GetReadOpCode();
    static OpCode GetWriteOpCode();
    static Timestamp GetCurrentTime();
};