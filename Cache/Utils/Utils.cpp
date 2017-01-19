//
// Created by cat on 10/2/16.
//

#include "Utils.h"
using namespace std;

void Utils::AppendToFile(const std::string &output_path, int i_var, double d_var)
{
    ofstream density_file;
    density_file.open(output_path.c_str(), fstream::out | fstream::app);

    density_file << i_var;
    density_file << "\t";
    density_file << d_var;
    density_file << "\n";

    density_file.close();
}

void Utils::AppendToFile(const std::string &output_path, const std::string &text)
{
    ofstream density_file;
    density_file.open(output_path.c_str(), fstream::out | fstream::app);
    density_file << text;
    density_file << "\n";
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

std::string Utils::GetCurrentUnixTime()
{
    time_t t = time(0);
    long int now = static_cast<long int>(t);
    string str_time = "";

    std::stringstream strstream;
    strstream << now;
    strstream >> str_time;

    return str_time;
}

std::string Utils::GetFileName(const string &path)
{
    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    string copy_path = path;
    const size_t last_slash_idx = copy_path.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        copy_path.erase(0, last_slash_idx + 1);
    }
    return copy_path;
}

std::string Utils::GetFileNameWithoutExt(const std::string &path)
{
    string name = GetFileName(path);
    size_t last_index = name.find_last_of(".");
    string clear_name = name.substr(0, last_index);
    return clear_name;
}

bool Utils::CreateDirectory(const std::string &dir_path)
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
                //parent didn't exist, try to create it
                if( CreateDirectory( dir_path.substr(0, dir_path.find_last_of('/')) ) )
                    //Now, try to create again.
                    bSuccess = 0 == ::mkdir( dir_path.c_str(), 0775 );
                else
                    bSuccess = false;
                break;
            case EEXIST:
                //Done!
                bSuccess = true;
                break;
            default:
                bSuccess = false;
                break;
        }
    }
    else
        bSuccess = true;
    return bSuccess;
}

//void Utils::OpenFile(const std::string file_path)
//{
//    file.open(file_path.c_str());
//    if (! (file.is_open()) )
//    {
//#ifdef DEBUG
//        Logger *logger = Logger::CreateLogger(CONSOLE);
//        logger->ShowLogText("Trace file opening were faled.\n");
//#endif
//    }
//}