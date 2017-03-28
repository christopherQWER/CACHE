//
// Created by cat on 12/13/16.
//

#include "TraceAnalyzer.h"
#include "../Generators/Request.h"
#include "../Utils/Paths.h"
using namespace std;

TraceAnalyzer::TraceAnalyzer(const string file_path, string output_file)
{
    _reads = 0;
    _writes = 0;
    _avg_req_size = 0;
    _line_num = 0;
    _input_file = file_path;
    _output_file = output_file;
    _trace_stream.open(file_path);
}

TraceAnalyzer::~TraceAnalyzer()
{
    _trace_stream.close();
    cout << "LOX" << endl;
}

void TraceAnalyzer::GetCommonStat()
{
    if (!_trace_stream.is_open())
    {
        return;
    }

    string buffer = "";
    bool result = false;
    while (getline(_trace_stream, buffer))
    {
        istringstream origs(buffer.c_str());
        Request req = Request();

        string part;
        result = getline(origs, part, ',') &&
                 (istringstream(part) >> req._asu) &&
                 getline(origs, part, ',') &&
                 (istringstream(part) >> req._lba) &&
                 getline(origs, part, ',') &&
                 (istringstream(part) >> req._size) &&
                 getline(origs, part, ',') &&
                 ( (part.size() == 1) ? (req._opcode = part.at(0), true) : false) &&
                 getline(origs, part, ',') &&
                 (istringstream(part) >> req._timestamp);

        if (!result && origs)
        {
            origs.setstate(ios::failbit);
            return;
        }

        if (tolower(req._opcode) == 'r')
        {
            _reads++;
        }
        else
        {
            _writes++;
        }
        _avg_req_size += req._size;
        _line_num++;
    }
    _avg_req_size /= _line_num;
    AppendToFile(_output_file);
}

void TraceAnalyzer::GetDetailedStat()
{
    map<Asu, AppInfo> app_map;
    map<Asu, AppInfo>::iterator map_it;
    if (!_trace_stream.is_open())
    {
        return;
    }

    string buffer = "";
    bool result = false;
    while (getline(_trace_stream, buffer))
    {
        istringstream origs(buffer.c_str());
        Request req = Request();

        string part;
        result = getline(origs, part, ',') &&
                (istringstream(part) >> req._asu) &&
                getline(origs, part, ',') &&
                (istringstream(part) >> req._lba) &&
                getline(origs, part, ',') &&
                (istringstream(part) >> req._size) &&
                getline(origs, part, ',') &&
                ( (part.size() == 1) ? (req._opcode = part.at(0), true) : false) &&
                getline(origs, part, ',') &&
                (istringstream(part) >> req._timestamp);

        if (!result && origs)
        {
            origs.setstate(ios::failbit);
            return;
        }

        map_it = app_map.find(req._asu);
        if(map_it == app_map.end())
        {
            AppInfo app_info = AppInfo();
            if (tolower(req._opcode) == 'r')
            {
                app_info.reads++;
            }
            else
            {
                app_info.writes++;
            }
            app_info.avg_req_size += req._size;
            _line_num++;
            app_map.insert(std::pair<Asu, AppInfo>(req._asu, app_info));
        }
        else
        {
            map_it->second.line_num++;
            map_it->second.avg_req_size += req._size;
            if (tolower(req._opcode) == 'r')
            {
                map_it->second.reads++;
            }
            else
            {
                map_it->second.writes++;
            }
        }
    }

    for (map_it = app_map.begin(); map_it != app_map.end(); map_it++)
    {
        map_it->second.avg_req_size /= map_it->second.line_num;
    }
    AppendToXml(_output_file, app_map);
}


void TraceAnalyzer::AppendToFile(const std::string& output_path)
{
    ofstream density_file;
    density_file.open(_STAT_TXT_, fstream::out | fstream::app);

    density_file << output_path;
    density_file << "\t";

    density_file << "Reads: ";
    density_file << _reads;
    density_file << "\t";

    density_file << "Writes: ";
    density_file << _writes;
    density_file << "\t";

    density_file << "All: ";
    density_file << _line_num;
    density_file << "\t";

    density_file << "Average bytes IO: ";
    density_file << _avg_req_size;
    density_file << "\n";

    density_file.close();
}

void TraceAnalyzer::AppendToXml(const std::string& output_path, const std::map<Asu, AppInfo>& app_map)
{
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("TraceFile");
    root.append_attribute("TracePath").set_value(_input_file.c_str());

    for(map<Asu, AppInfo>::const_iterator it = app_map.begin(); it != app_map.end(); it++)
    {
        pugi::xml_node app = root.append_child("App");
        app.append_attribute("Unit").set_value(it->first);
        app.append_attribute("Reads").set_value(it->second.reads);
        app.append_attribute("Writes").set_value(it->second.writes);
        app.append_attribute("AvgBytes").set_value(static_cast<unsigned long>(it->second.avg_req_size));
    }
    doc.save_file(_output_file.c_str());
}