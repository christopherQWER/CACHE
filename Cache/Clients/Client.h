//
// Created by cat on 1/21/17.
//

#pragma once
#include <iostream>
#include <string>
#include "../Utils/Types.h"
#include "../Caches/Lru.h"
#include "../Flows/Flow.h"
#include "../Requests/Request.h"
typedef std::map<StackDist, int> StackDistMap;

class Client {
public:

    double _QoS;
    Asu _application_id;
    int _request_counter;

    Client();
    Client(Asu asu, double qos);
    ~Client();

    void AddStackDistToMap(StackDist stack_dist);
    void SavePdfPlotDots(const std::string& file_path);
    void SaveCdfPlotDots(const std::string& file_path);


private:
    StackDistMap _stack_dist_map;

    bool IsInStorage(StackDist value);
};