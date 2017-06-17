//
// Created by cat on 10/5/16.
//

#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include <list>
#include <map>

typedef unsigned int Lba;
typedef unsigned int Asu;
typedef unsigned long long ByteSize;
typedef char OpCode;
typedef double Timestamp;
typedef long double StackDist;
typedef double HitRate;
typedef std::map<double, StackDist> ProportionalMap;
typedef std::map<StackDist, double> PairStorage;