//
// Created by cat on 5/22/17.
//
#pragma once
#include "RandomValue.h"
#include "UniformInt.h"
#include "../Utils/Types.h"
UniformInt uni_gen = UniformInt(1, 10);

/// Size of standard memory cell
#define _CELL_SIZE_ 512

class SizeGen : public RandomValue {
public:

    ByteSize GetRandomValue();
};

