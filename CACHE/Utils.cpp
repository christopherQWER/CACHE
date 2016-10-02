//
// Created by cat on 10/2/16.
//

#include "Utils.h"
using namespace std;

void Utils::WriteFile(std::string output_path, map<int, double> collection)
{
    ofstream density_file;
    density_file.open(output_path.c_str(), fstream::out);
    for (map<int, double>::iterator it = collection.begin(); it != collection.end(); it++)
    {
        density_file << it->first;
        density_file << "\t";
        density_file << it->second;
        density_file << "\n";
    }
    density_file.close();
}
