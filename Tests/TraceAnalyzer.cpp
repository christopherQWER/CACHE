//
// Created by cat on 12/13/16.
//

#include "TraceAnalyzer.h"
using namespace std;

TraceAnalyzer::TraceAnalyzer(const std::string& file_path)
{
    _reads = 0;
    _writes = 0;
    _avg_req_size = 0;
    _line_num = 0;
    _trace_file.open(file_path.c_str());
}

TraceAnalyzer::~TraceAnalyzer()
{
    _trace_file.close();
    cout << "LOX" << endl;
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

void TraceAnalyzer::GetStat()
{
    if (!_trace_file.is_open())
    {
        return;
    }

    string buffer = "";
    bool result = false;
    while (getline(_trace_file, buffer))
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

        if (tolower(req._opcode) != 'r')
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
}
