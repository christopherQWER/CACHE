//
// Created by cat on 10/5/16.
//

#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include <list>
#include <map>
#ifndef CACHE_TYPES_H
#define CACHE_TYPES_H

//Types definition
typedef unsigned int Lba;
typedef unsigned int Asu;
typedef unsigned long long Byte_size;
typedef char Op_code;
typedef double Timestamp;
typedef long double Stack_dist;
typedef double Hit_rate;
typedef std::map<int, int>::iterator Map_itr;
typedef std::multimap<double, double>::iterator Mmap_itr;
typedef std::list<double>::iterator List_itr;

#endif //CACHE_TYPES_H
