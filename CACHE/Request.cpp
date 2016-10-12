//
// Created by cat on 9/25/16.
//

#include "Request.h"
using namespace std;

//For random generator
random_device rd;     /* Only used once to initialise (seed) engine */
mt19937 rng(rd());    /* Random-number engine used (Mersenne-Twister in this case) */


Request::Request()
{
    _asu = 0;
    _lba = 0;
    _size = 0;
    _opcode = ' ';
    _timestamp = time(0);
}

Request::Request(Asu asu, Lba lba, Byte_size size, Op_code opcode, Timestamp timestamp)
{
    _asu = asu;
    _lba = lba;
    _size = size;
    _opcode = opcode;
    _timestamp = timestamp;
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

void Request::ParseRequest(string request_string, deque<Request>& req_list)
{
    bool result = false;

    istringstream origs(request_string.c_str());
    Request req = Request();

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
        return;
    }

    unsigned int numberOfRequests = (unsigned int) (req._size / _CELL_SIZE_);
    for (int i = 0; i < numberOfRequests + 1; i++)
    {
        if (req._opcode != 'r')
        {
            return;
        }
        Request rq = Request(req._asu, req._lba + _CELL_SIZE_ * i, _CELL_SIZE_, req._opcode, req._timestamp);
        req_list.push_back(rq);
    }
}

Asu Request::GetRandomAsu()
{
    uniform_int_distribution<int> uni(1, 20); /* Guaranteed unbiased */
    return (Asu) uni(rng);
}

Lba Request::GetRandomLba()
{
    uniform_int_distribution<int> uni(LOW_ADDRESS_BOUND, UP_ADDRESS_BOUND); /* Guaranteed unbiased */
    return (Lba) uni(rng);
}

Op_code Request::GetReadOpCode()
{
    return 'r';
}

Op_code Request::GetWriteOpCode()
{
    return 'w';
}

Timestamp Request::GetCurrentTime()
{
    return time(0);
}