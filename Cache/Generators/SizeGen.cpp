//
// Created by cat on 5/22/17.
//

#include "SizeGen.h"
UniformInt uni_gen = UniformInt(1, 10);
using namespace std;


ByteSize SizeGen::GetRandomValue()
{
    //int rand_degree = uni_gen.GetRandomValue();
    //return _CELL_SIZE_ * pow(2, rand_degree);
    return _CELL_SIZE_;
}
