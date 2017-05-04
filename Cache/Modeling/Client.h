//
// Created by cat on 1/21/17.
//

#pragma once
#include <iostream>
#include <string>
#include "../Utils/Types.h"
#include "../Caches/Lru.h"
#include "../Flows/Flow.h"
#include "../Generators/Request.h"

typedef std::map<StackDist, int> DistStorage;

class Client {
public:
    /// Counter of sent requests from this application
    int _request_counter;
    Asu _application_id;
    double _QoS;
    DistStorage stack_dist_map;
    Flow *flow;
    std::string pdf_dir_path;
    std::string cdf_dir_path;

    Client();
    virtual ~Client();

    void AddStackDistToMap(StackDist stack_dist);
    void Init(Asu asu, std:: string results_dir);

    void SavePdfPlotDots(const std::string& file_path);
    void SaveCdfPlotDots(const std::string& file_path);

private:

    bool IsInStorage(StackDist value);
};