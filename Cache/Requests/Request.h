//
// Created by cat on 9/25/16.

#pragma once
#include <iostream>
#include <deque>
#include <ctime>
#include "../Utils/Types.h"


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

    /// Is it request hits to cache
    bool _is_Hit;

     /// Default constructor
    Request();

     /// \brief                 Constructor
     /// \param asu             application specific unit
     /// \param lba             logical block address
     /// \param size            size of requested bytes
     /// \param opcode          operation code
     /// \param timestamp       incoming time
    Request(Asu asu, Lba lba, ByteSize size, OpCode opcode, Timestamp timestamp);

    bool operator < (Request x)
    {
        return _timestamp < x._timestamp;
    }
};