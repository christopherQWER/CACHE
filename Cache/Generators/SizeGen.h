//
// Created by cat on 5/22/17.
//
#pragma once
#include "RandomValue.h"
#include "UniformInt.h"
#include "../Utils/Types.h"
#include "../Utils/DefinedConstants.h"


class SizeGen : public RandomValue {
public:

    ByteSize GetRandomValue();
};

