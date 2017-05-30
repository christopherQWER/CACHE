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

    double required_qos;
    double experimental_qos;

    Asu application_id;
    int request_counter;
    double avg_hit_rate;
    double hits;

    /// Counter of preparing histograms
    int result_hist_counter;

    /// File with results, for example: "App_1.txt"
    std::string output_file_name;

    Client(Asu asu, double qos);
    ~Client();

    void AddStackDistToMap(StackDist stack_dist);
    void SavePdfPlotDots(const std::string& file_path);
    void SaveCdfPlotDots(const std::string& file_path);

    StackDist GetMinStackDistance();
    StackDist GetMaxStackDistance();

private:
    StackDistMap _stack_dist_map;
    bool IsInStorage(StackDist value);
};