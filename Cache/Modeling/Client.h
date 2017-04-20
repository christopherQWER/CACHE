//
// Created by cat on 1/21/17.
//

#pragma once
#include <iostream>
#include <string>
#include "../Utils/Types.h"
#include "../Caches/Lru.h"
#include "../Generators/Request.h"

typedef std::map<StackDist, int> DistStorage;

class Client {
public:
    /// Counter of sent requests from this application
    int _request_counter;

    /// Client id
    Asu _application_id;

    /// Quality of service for current client
    double _QoS;

    /// Frequency of stack distances occurrences
    DistStorage stack_dist_map;

    /// Path to directory with pdf plots
    std::string pdf_dir_path;

    /// Path to directory with cdf plots
    std::string cdf_dir_path;

    /// Field of cache: using only if algorithm is partial!!!
    Lru* _cache;

    Client();
    virtual ~Client();

    void AddStackDistToMap(StackDist stack_dist);
    void Init(Asu asu, std:: string results_dir);

    void SavePdfPlotDots(const std::string& file_path);
    void SaveCdfPlotDots(const std::string& file_path);

private:

    bool IsInStorage(StackDist value);
};