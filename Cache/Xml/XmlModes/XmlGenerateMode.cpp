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

    pugi::xml_node limit_node = doc.append_child(sLimit.c_str());
    limit_node.append_attribute(sType.c_str()).set_value(toString(gen_cnf.limit.limit_type).c_str());
    limit_node.set_value(Utils::convert(gen_cnf.limit.limit_value).c_str());

    pugi::xml_node pdfs_node = simulation_node.append_child(sSources.c_str());
    for (auto pdf_sources : gen_cnf.source_for_apps)
    {
        pdfs_node.append_attribute(sSwitch.c_str()).set_value(pdf_sources.switcher);
        pdfs_node.append_attribute(sXmlAsu.c_str()).set_value(pdf_sources.asu);
        pdfs_node.append_attribute(sLowAddressBound.c_str()).set_value(pdf_sources.low_address);
        pdfs_node.append_attribute(sRequestNum.c_str()).
                set_value(static_cast<unsigned long>(pdf_sources.request_num));
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

    pugi::xml_node limit_node = simulation_node.child(sLimit.c_str());
    gen_cnf.limit.limit_type = toType(limit_node.attribute(sType.c_str()).as_string(""));
    gen_cnf.limit.limit_value = limit_node.text().as_uint(0);

    for(pugi::xml_node app_sources = simulation_node.child(sSources.c_str()); app_sources;
        app_sources = app_sources.next_sibling(sSources.c_str()))
    {
        Sources new_input = Sources();

        new_input.asu = app_sources.attribute(sXmlAsu.c_str()).as_uint(0);
        new_input.low_address = app_sources.attribute(sLowAddressBound.c_str()).as_uint(400000);
        new_input.switcher = app_sources.attribute(sSwitch.c_str()).as_double(0);
        new_input.request_num = app_sources.attribute(sRequestNum.c_str()).as_uint(100000);

        for (pugi::xml_node input_pdf = app_sources.child(sInputPdf.c_str()); input_pdf;
             input_pdf = input_pdf.next_sibling(sInputPdf.c_str()))
        {
            new_input.input_pdf_dirs.push_back(input_pdf.text().as_string(""));
        }
        gen_cnf.source_for_apps.push_back(new_input);
    }
}
