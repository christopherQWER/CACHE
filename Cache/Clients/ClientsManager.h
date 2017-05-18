//
// Created by cat on 5/8/17.
//
#include "../Utils/Types.h"
#include "../Utils/GnuPlot.h"
#include "../Utils/Paths.h"
#include "../Xml/Modes/XmlSimulateMode.h"
#include "Client.h"
typedef std::map<Asu, Client> ClientMap;

class ClientsManager {
public:
    ClientMap clients_map;
    ClientsManager(std::list<XmlClient> list);

    void DrawPDFPlot(const std::string &trace_name);
    void DrawCDFPlot(const std::string &trace_name);
    void CommonPlot(const std::string &flow_file_name);

private:
    bool IsInMap(Asu asu);
};