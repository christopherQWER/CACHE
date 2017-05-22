//
// Created by cat on 9/25/16.
//

#include "Request.h"
using namespace std;

Request::Request()
{
    _asu = 0;
    _lba = 0;
    _size = 0;
    _opcode = ' ';
    _timestamp = time(0);
}

Request::Request(Asu asu, Lba lba, ByteSize size, OpCode opcode, Timestamp timestamp)
{
    _asu = asu;
    _lba = lba;
    _size = size;
    _opcode = opcode;
    _timestamp = timestamp;
    _stack_distance = 0;
}