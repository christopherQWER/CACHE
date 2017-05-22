//
// Created by cat on 4/23/17.
//

#include "XmlGenerateMode.h"
using namespace std;

void XmlGenerateMode::Serialize(const XmlGenerate& gen_cnf, pugi::xml_document& doc)
{
    pugi::xml_node simulation_node = doc.append_child(sGenerate.c_str());
    SerializeLogger(gen_cnf.logger, simulation_node);
    SerializeFlow(gen_cnf.flow, simulation_node);
    simulation_node.append_child(sSystemTime.c_str()).set_value(to_string(gen_cnf.system_time).c_str());
    simulation_node.append_child(sInputPdf.c_str()).set_value(gen_cnf.input_pdf_dir.c_str());
}

void XmlGenerateMode::Deserialize(const pugi::xml_document& doc, XmlGenerate& gen_cnf)
{
    pugi::xml_node simulation_node = doc.child(sGenerate.c_str());
    DeserializeLogger(simulation_node, gen_cnf.logger);
    DeserializeFlow(simulation_node, gen_cnf.flow);
    gen_cnf.system_time = simulation_node.child(sSystemTime.c_str()).text().as_double(0);
    gen_cnf.input_pdf_dir = simulation_node.child(sInputPdf.c_str()).text().as_string("");
}
