//
// Created by cat on 10/2/16.
//
#pragma once
#ifndef CACHE_UTILS_H
#define CACHE_UTILS_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

class Utils
{
public:

    static void AppendToFile(const std::string &output_path, int i_var, double d_var);
};


#endif //CACHE_UTILS_H
