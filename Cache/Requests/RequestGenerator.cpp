//
// Created by cat on 5/20/17.
//

#include "RequestGenerator.h"
using namespace std;


RequestGenerator::RequestGenerator() : Request()
{
    lba_gen = new LbaGen();
    time_gen = new TimeGen();
    size_gen = new SizeGen();
}

RequestGenerator::~RequestGenerator()
{
    if (lba_gen != NULL)
    {
        delete lba_gen;
    }
    if (time_gen != NULL)
    {
        delete time_gen;
    }
    if (size_gen != NULL)
    {
        delete size_gen;
    }
}

Request RequestGenerator::GenerateRequest(Asu asu, StackDist stack_dist, Lba low_address_bound)
{
    Request rq = Request();
    rq._asu = asu;
    rq._lba = GenerateLba(stack_dist, low_address_bound);
    rq._opcode = GetReadOpCode();
    rq._size = GenerateByteSize();
    rq._timestamp = GenerateTime();
    rq._stack_distance = 0;
    return  rq;
}

Lba RequestGenerator::GenerateLba(StackDist stack_dist, Lba low_address_bound)
{
    Lba lba = lba_gen->GetRandomValue(stack_dist, low_address_bound);
    return lba;
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
    return time_gen->GetRandom();
}

ByteSize RequestGenerator::GenerateByteSize()
{
    return size_gen->GetRandomValue();
}