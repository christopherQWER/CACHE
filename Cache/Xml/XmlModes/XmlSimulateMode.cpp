//
// Created by cat on 4/23/17.
//

#include "XmlSimulateMode.h"

void XmlSimulateMode::Serialize(const XmlSimulate& sim_cnf, pugi::xml_document& doc)
{
    pugi::xml_node simulation_node = doc.append_child(sSimulate.c_str());
    simulation_node.append_attribute(sType.c_str()).set_value(Storage::toString(sim_cnf.stor_type));
    simulation_node.append_attribute(sAppCount.c_str()).set_value(static_cast<unsigned long>(sim_cnf.app_count));
    simulation_node.append_attribute(sCommonSize.c_str()).set_value(static_cast<unsigned long>(sim_cnf.common_size));
    simulation_node.append_attribute(sRequestNum.c_str()).set_value(static_cast<unsigned long>(sim_cnf.request_num));
    simulation_node.append_attribute(sWithPlots.c_str()).set_value(sim_cnf.with_plots);

    SerializeLogger(sim_cnf.logger, simulation_node);
    SerializeFlow(sim_cnf.flow, simulation_node);
    pugi::xml_node plot_dir_node = simulation_node.append_child(sPlotDir.c_str());
    plot_dir_node.set_value(sim_cnf.plot_dir.c_str());

    pugi::xml_node clients = simulation_node.append_child(sApps.c_str());
    for (auto &client : sim_cnf.app_list)
    {
        pugi::xml_node cache_node = clients.append_child(sApplication.c_str());
        cache_node.append_attribute(sXmlAsu.c_str()).set_value(client.asu);
        cache_node.append_attribute(sQoS.c_str()).set_value(client.qos);
    }
}

void XmlSimulateMode::Deserialize(const pugi::xml_document& doc, XmlSimulate& sim_cnf)
{
    pugi::xml_node simulation_node = doc.child(sSimulate.c_str());
    sim_cnf = XmlSimulate();
    sim_cnf.stor_type = Storage::toType(simulation_node.attribute(sType.c_str()).as_string(""));
    sim_cnf.app_count = simulation_node.attribute(sAppCount.c_str()).as_uint(0);
    sim_cnf.request_num = simulation_node.attribute(sRequestNum.c_str()).as_uint(1000000);
    sim_cnf.common_size = static_cast<ByteSize>(simulation_node.attribute(sCommonSize.c_str()).as_int(1));
    sim_cnf.with_plots = simulation_node.attribute(sWithPlots.c_str()).as_bool(false);

    DeserializeLogger(simulation_node, sim_cnf.logger);
    DeserializeFlow(simulation_node, sim_cnf.flow);
    sim_cnf.plot_dir = simulation_node.child(sPlotDir.c_str()).text().as_string("");

    pugi::xml_node caches_node = simulation_node.child(sApps.c_str());
    for (pugi::xml_node child = caches_node.child(sApplication.c_str()); child;
                        child = child.next_sibling(sApplication.c_str()))
    {
        XmlClient client_obj = XmlClient();
        client_obj.asu = child.attribute(sXmlAsu.c_str()).as_uint(0);
        client_obj.qos = child.attribute(sQoS.c_str()).as_double(0.2);
        sim_cnf.app_list.push_back(client_obj);
    }
}