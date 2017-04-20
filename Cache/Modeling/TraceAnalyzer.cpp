//
// Created by cat on 12/13/16.
//

#include "TraceAnalyzer.h"
#include "../Generators/Request.h"
using namespace std;

TraceAnalyzer::TraceAnalyzer(const string &file_path, string &output_file)
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
    while (getline(_trace_stream, buffer))
    {
        Request req = Request();
        if (!Request::SetRequest(buffer, req))
        {
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
    ByteSize common_length = 0;
    map<Asu, AppInfo> app_map;
    map<Asu, AppInfo>::iterator map_it;
    if (!_trace_stream.is_open())
    {
        return;
    }

    string buffer = "";
    while (getline(_trace_stream, buffer))
    {
        Request req = Request();
        if (!Request::SetRequest(buffer, req))
        {
            return;
        }

        // find application with required asu
        map_it = app_map.find(req._asu);

        // if app is not in map
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
            app_info.req_num++;
            app_info.unit = req._asu;
            app_map.insert(pair<Asu, AppInfo>(req._asu, app_info));
        }
        else
        {
            // increment number of requests for app
            map_it->second.req_num++;
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
        common_length++;
    }

    TraceInfo trace_info = TraceInfo();
    trace_info.length = common_length;
    trace_info.input_file = _input_file;
    trace_info.output_file = _output_file;

    // getting average number of request size for app unit
    for (map_it = app_map.begin(); map_it != app_map.end(); map_it++)
    {
        map_it->second.avg_req_size /= map_it->second.req_num;
        trace_info.apps.push_back(map_it->second);
    }
    pugi::xml_document doc;
    AnalyzeConfig::Serialize(trace_info, doc);
    AnalyzeConfig::SaveToFile(doc, _output_file);
    app_map.clear();
}

void TraceAnalyzer::AppendToFile(const string& output_path)
{
    ofstream density_file;
    density_file.open(output_path, fstream::out | fstream::app);

    density_file << output_path;
    density_file << "\n";

    density_file << "Reads: ";
    density_file << _reads;
    density_file << "\n";

    density_file << "Writes: ";
    density_file << _writes;
    density_file << "\n";

    density_file << "All: ";
    density_file << _line_num;
    density_file << "\n";

    density_file << "Average bytes IO: ";
    density_file << _avg_req_size;
    density_file << "\n";

    density_file.close();
}

TraceAnalyzer::TraceAnalyzer()
{

}