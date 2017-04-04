//
// Created by cat on 10/2/16.
//

#include <cmath>
#include <ctime>
#include "Utils.h"
using namespace std;

void Utils::AppendToFile(const string &output_path, const string &text)
{
    ofstream density_file;
    density_file.open(output_path.c_str(), fstream::out | fstream::app);
    density_file << text;
    density_file << "\n";
    density_file.close();
}

void Utils::WriteLines(const string &output_path, vector<string> &lines)
{
    ofstream density_file;
    density_file.open(output_path.c_str(), fstream::out | fstream::app);
    for (int i = 0; i < lines.size(); i++)
    {
        density_file << lines[i];
        density_file << "\n";
    }
    density_file.close();
}

int Utils::DoubleToInt(double d_input)
{
    int value = 0;
    double int_part = 0;
    double fract_part = 0;
    fract_part = modf(d_input, &int_part);
    value = static_cast<int>(int_part);
    return value;
}

string Utils::GetCurrentUnixTime()
{
    time_t t = time(0);
    long int now = static_cast<long int>(t);
    string str_time = "";

    stringstream strstream;
    strstream << now;
    strstream >> str_time;

    return str_time;
}

string Utils::GetFileName(const string &path)
{
    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    string copy_path = path;
    const size_t last_slash_idx = copy_path.find_last_of("\\/");
    if (string::npos != last_slash_idx)
    {
        copy_path.erase(0, last_slash_idx + 1);
    }
    return copy_path;
}

string Utils::GetFileNameWithoutExt(const string &path)
{
    string name = GetFileName(path);
    size_t last_index = name.find_last_of(".");
    string clear_name = name.substr(0, last_index);
    return clear_name;
}

bool Utils::CreateDirectory(const string &dir_path)
{
//    int status = 0;
//    status = mkdir(dir_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//    return status == 0;

    bool bSuccess = false;
    int nRC = ::mkdir( dir_path.c_str(), 0775 );
    if( nRC == -1 )
    {
        switch( errno )
        {
            case ENOENT:
            {
                //parent didn't exist, try to create it
                if( CreateDirectory( dir_path.substr(0, dir_path.find_last_of('/')) ) )
                {
                    //Now, try to create again.
                    bSuccess = 0 == ::mkdir( dir_path.c_str(), 0775 );}
                else
                {
                    bSuccess = false;
                }
                break;
            }
            case EEXIST:
            {
                //Done!
                bSuccess = true;
                break;
            }
            default:
            {
                bSuccess = false;
                break;
            }
        }
    }
    else
    {
        bSuccess = true;
    }
    return bSuccess;
}

void Utils::ExecuteCmd(const string &input)
{
    int errorCode = system(input.c_str());
}

string Utils::SplitFilename (const string& file_path)
{
    string dir = "";
    size_t found = file_path.find_last_of("/\\");
    dir = file_path.substr(0, found - 1);
    return dir;
}

//string Utils::PathCombine(const char *fmt, const char* ...)
//{
//    string result_str = "";
//    va_list args;
//    va_start(args, fmt);
//    while (fmt != '\0')
//    {
//        result_str += va_arg(args, char*);
//        ++fmt;
//    }
//    va_end(args);
//    return result_str;
//}

//void Utils::OpenFile(const string file_path)
//{
//    trace_file.open(file_path.c_str());
//    if (! (trace_file.is_open()) )
//    {
//#ifdef DEBUG
//        Logger *logger = Logger::CreateLogger(TYPE);
//        logger->ShowLogText("Trace trace_file opening were faled.\n");
//#endif
//    }
//}