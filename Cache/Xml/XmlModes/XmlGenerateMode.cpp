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

    pugi::xml_node pdfs_node = simulation_node.append_child(sInputPdfs.c_str());
    for (auto pdf_sources : gen_cnf.source_for_apps)
    {
        pdfs_node.append_attribute(sSwitch.c_str()).set_value(pdf_sources.switcher);
        pdfs_node.append_attribute(sXmlAsu.c_str()).set_value(pdf_sources.asu);
        for(string one_source : pdf_sources.input_pdf_dirs)
        {
            pdfs_node.append_child(sInputPdf.c_str()).set_value(one_source.c_str());
        }
    }
}

void XmlGenerateMode::Deserialize(const pugi::xml_document& doc, XmlGenerate& gen_cnf)
{
    pugi::xml_node simulation_node = doc.child(sGenerate.c_str());
    DeserializeLogger(simulation_node, gen_cnf.logger);
    DeserializeFlow(simulation_node, gen_cnf.flow);
    gen_cnf.system_time = simulation_node.child(sSystemTime.c_str()).text().as_double(0);

    for(pugi::xml_node my_child = simulation_node.child(sInputPdfs.c_str()); my_child;
        my_child = my_child.next_sibling(sInputPdfs.c_str()))
    {
        pugi::xml_node pdfs_node = my_child.child(sInputPdf.c_str());
        XmlInputPdfs new_input = XmlInputPdfs();

        new_input.asu = my_child.attribute(sXmlAsu.c_str()).as_uint(0);
        new_input.switcher = my_child.attribute(sSwitch.c_str()).as_double(0);

        for (pugi::xml_node child = my_child.child(sInputPdf.c_str()); child;
             child = my_child.next_sibling(sInputPdf.c_str()))
        {
            new_input.input_pdf_dirs.push_back(child.text().as_string(""));
        }
        gen_cnf.source_for_apps.push_back(new_input);
    }
}
