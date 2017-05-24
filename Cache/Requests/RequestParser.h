//
// Created by cat on 5/20/17.
//
#pragma once
#include <string>
#include <sstream>
#include "Request.h"

class RequestParser : public Request{

public:

    /// \brief
    /// \param traceLog
    /// \param reqList
    static void ParseRequest(const std::string &traceLog, std::deque<Request>& reqList);

    static std::string GetStringFromRequest(const Request& request);

    /// \brief                  Function gets all required fields from string
    /// \param request_string
    /// \param req
    /// \return
    static bool GetRequestFromString(const std::string& request_string, Request& req);
};