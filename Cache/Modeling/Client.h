//
// Created by cat on 1/21/17.
//

#pragma once
#include <iostream>
#include <string>
#include "../Utils/Types.h"
#include "../Caches/Lru.h"
#include "../Generators/Request.h"

typedef std::map<StackDist, int> DistStor;

class Client {
public:
    /// Counter of sended requests from this application
    int _request_counter;

    /// Client id
    Asu _application_id;

    /// Frequency of stack distances occurances
    DistStor stack_dist_map;

    std::string pdf_dir_path;
    std::string cdf_dir_path;

    Client();
    virtual ~Client();

    void SaveStackDist(StackDist stack_dist);
    void Init(Request* request, std:: string results_dir);
    void SavePdfPlotDots(const std::string& file_path);
    void SaveCdfPlotDots(const std::string& file_path);

private:

    bool IsInStorage(StackDist value);
};