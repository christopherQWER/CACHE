//
// Created by cat on 9/25/16.
//

#include <sstream>
#include <algorithm>
#include "Request.h"
#include "../Generators/UniformReal.h"
#include "../Generators/UniformInt.h"
#include "../Generators/LbaGen.h"
using namespace std;
LbaGen lba_gen = LbaGen();
UniformInt uni_int_asu = UniformInt(1, 20);

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

Request::~Request()
{
}

void Request::GenerateRequest(Request& rq)
{
    rq._asu = GetRandomAsu();
    rq._lba = GetRandomLba();
    rq._opcode = GetReadOpCode();
    rq._size = _CELL_SIZE_;
    rq._timestamp = GetCurrentTime();
}

void Request::ParseRequest(const string &request_string, deque<Request>& req_list)
{
    Request req = Request();
    if (!GetRequestFromString(request_string, req))
        return;

    unsigned int numberOfRequests = (unsigned int) (req._size / _CELL_SIZE_);
    for (int i = 0; i < numberOfRequests + 1; i++)
    {
        if (tolower(req._opcode) != 'r')
        {
            return;
        }
        Request rq = Request(req._asu,
                            req._lba + _CELL_SIZE_ * i,
                            _CELL_SIZE_,
                            req._opcode,
                            req._timestamp);
        req_list.push_back(rq);
    }
}

Asu Request::GetRandomAsu()
{
    return static_cast<Asu>(uni_int.GetRandom());
}

Lba Request::GetRandomLba()
{
    return lba_gen.GetRandom();
}

OpCode Request::GetReadOpCode()
{
    return 'r';
}

OpCode Request::GetWriteOpCode()
{
    return 'w';
}

Timestamp Request::GetCurrentTime()
{
    return time(0);
}

bool Request::GetRequestFromString(const string& request_string, Request& req)
{
    bool result = false;
    istringstream origs(request_string.c_str());
    string part;
    result = getline(origs, part, ',') &&
            (istringstream(part) >> req._asu) &&
            getline(origs, part, ',') &&
            (istringstream(part) >> req._lba) &&
            getline(origs, part, ',') &&
            (istringstream(part) >> req._size) &&
            getline(origs, part, ',') &&
            ( (part.size() == 1) ? (req._opcode = part.at(0), true) : false) &&
            getline(origs, part, ',') &&
            (istringstream(part) >> req._timestamp);

    if (!result && origs)
    {
        origs.setstate(ios::failbit);
        return false;
    }
    return true;
}