//
// Created by cat on 5/8/17.
//

#pragma once
#include <list>
#include <algorithm>
#include "../Utils/Types.h"
#include "../Utils/GnuPlot.h"
#include "../Utils/Paths.h"
#include "../Xml/XmlModes/XmlSimulateMode.h"
#include "Client.h"
typedef std::map<Asu, Client*> ClientMap;

class ClientsManager {
public:
    /// Paths to histograms (pdf and cdf) from simulation algorithm for all clients in this scope
    std::string pdf_dir;
    std::string cdf_dir;

    /// Number of histograms steps
    int common_hist_counter;

    ClientMap clients_map;
    ClientsManager();
    ~ClientsManager();
    ClientsManager(const std::list<XmlClient>& list);
    void Clear();

    void InitAllRequiredFields(Request *request);
    void QosComparator(Logger*& logger);
    void DrawPDFPlot(const std::string &trace_name);
    void DrawCDFPlot(const std::string &trace_name);
    void DrawHrVSCacheSizePlot(const std::string algorithm_name,
                                ByteSize max_cache_capacity,
                                ByteSize cache_size_step);
    void SaveRequiredCacheSizesByQoS(Logger*& logger,
                                    std::list<XmlClient>& app_list,
                                    ByteSize current_cache_size);
    void CommonPlot(const std::string &flow_file_name);


private:

    bool IsInMap(Asu asu);
    void FindLimitsByX(StackDist& min, StackDist& max);
};