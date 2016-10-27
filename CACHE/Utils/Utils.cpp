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