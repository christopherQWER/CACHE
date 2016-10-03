//
// Created by cat on 10/4/16.
//

#include "FileLogger.h"
using namespace std;

FileLogger::FileLogger()
{
    ofstream file;
    file.open(LOG_PATH, fstream::out);
    file.close();
}


FileLogger::~FileLogger()
{

}