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
    static void WriteFile(std::string output_path, std::map<int, double> collection);
};


#endif //CACHE_UTILS_H
