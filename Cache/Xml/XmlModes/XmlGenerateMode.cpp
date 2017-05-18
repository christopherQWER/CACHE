//
// Created by cat on 4/23/17.
//

#include "XmlGenerateMode.h"

void XmlGenerateMode::Serialize(const XmlGenerate& gen_cnf, pugi::xml_document& doc)
{
    pugi::xml_node simulation_node = doc.append_child(sGenerate.c_str());
    SerializeLogger(gen_cnf.logger, simulation_node);
    SerializeFlow(gen_cnf.flow, simulation_node);
}

void XmlGenerateMode::Deserialize(const pugi::xml_document& doc, XmlGenerate& gen_cnf)
{
    pugi::xml_node simulation_node = doc.child(sGenerate.c_str());
    DeserializeLogger(simulation_node, gen_cnf.logger);
    DeserializeFlow(simulation_node, gen_cnf.flow);
}
