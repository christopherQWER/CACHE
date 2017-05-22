//
// Created by cat on 5/22/17.
//

#include "SizeGen.h"


ByteSize SizeGen::GetRandomValue()
{
    int rand_degree = uni_gen.GetRandomValue();
    return _CELL_SIZE_ * pow(2, rand_degree);
}
