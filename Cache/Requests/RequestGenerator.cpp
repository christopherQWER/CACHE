//
// Created by cat on 5/20/17.
//

#include "RequestGenerator.h"
using namespace std;


RequestGenerator::RequestGenerator()
{
}

RequestGenerator::~RequestGenerator()
{
}

Request RequestGenerator::GenerateRequest(Asu asu, StackDist stack_dist)
{
    Request rq = Request();
    rq._asu = asu;
    rq._lba = GenerateLba(stack_dist);
    rq._opcode = GetReadOpCode();
    rq._size = GenerateByteSize();
    rq._timestamp = GenerateTime();
    return  rq;
}

Lba RequestGenerator::GenerateLba(StackDist stack_dist)
{
    return static_cast<Lba>(lba_gen.GetRandomValue(stack_dist));
}

OpCode RequestGenerator::GetReadOpCode()
{
    return 'r';
}

OpCode RequestGenerator::GetWriteOpCode()
{
    return 'w';
}

Timestamp RequestGenerator::GenerateTime()
{
    return time_gen.GetRandom();
}

ByteSize RequestGenerator::GenerateByteSize()
{
    return size_gen.GetRandomValue();
}
