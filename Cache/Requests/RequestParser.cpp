//
// Created by cat on 5/20/17.
//

#include "RequestParser.h"
#include "../Generators/SizeGen.h"
using namespace std;

bool RequestParser::ParseRequest(const string &request_string, deque<Request>& req_list)
{
    Request req = Request();
    if (!GetRequestFromString(request_string, req))
    {
        return false;
    }

    unsigned int numberOfRequests = (unsigned int) (req._size / _CELL_SIZE_);
    for (int i = 0; i < numberOfRequests; i++)
    {
        if (tolower(req._opcode) != 'r')
        {
            return false;
        }
        Request rq = Request(req._asu,
                            req._lba,
                            _CELL_SIZE_,
                            req._opcode,
                            req._timestamp);
        req_list.push_back(rq);
    }
}

bool RequestParser::GetRequestFromString(const string& request_string, Request& req)
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

string RequestParser::GetStringFromRequest(const Request& request)
{
    string req_string = "";
    stringstream ss;
    ss << request._asu << "," <<
          request._lba << "," <<
          request._size << "," <<
          request._opcode << "," <<
          request._timestamp;
    req_string = ss.str();
    return req_string;
}