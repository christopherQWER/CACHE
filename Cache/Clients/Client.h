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
    ByteSize required_cache_size;
    Asu application_id;

    int request_counter;
    double avg_hit_rate;
    StackDist avg_stack_dist;
    double hits;

    /// Counter of preparing histograms
    int result_hist_counter;

    /// File with results, for example: "App_1.txt"
    std::string output_file_name;
    std::string qos_file_name;

    Client(Asu asu, double qos);
    ~Client();
    void Clear();

    HitRate CalculateHitRate();
    StackDist CalculateAvgStackDistance();

    void AddStackDistToMap(StackDist stack_dist);

    void SavePdfPlotDots(const std::string& file_path);
    void SaveCdfPlotDots(const std::string& file_path);
    void SaveQoSPlotDots(const std::string& file_path);

    ByteSize GetRequiredSizeByQoS();

    void LoadPdfPlotDots(const std::string& file_path, ProportionalMap &pdf_map);
    void LoadCdfPlotDots(const std::string& file_path);

    StackDist GetMinStackDistance();
    StackDist GetMaxStackDistance();

private:

    StackDistMap _stack_dist_map;
    bool IsInStorage(StackDist value);
    bool GetPairFromString(const std::string& pdf_string, std::pair<double, StackDist> &new_pair);
};