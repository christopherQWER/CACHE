//
// Created by cat on 5/20/17.
//
#pragma once
#include "Request.h"
#include "../Generators/UniformReal.h"
#include "../Generators/UniformInt.h"
#include "../Generators/LbaGen.h"
#include "../Generators/TimeGen.h"
#include "../Generators/StackDistanceGen.h"
#include "../Generators/SizeGen.h"

LbaGen lba_gen = LbaGen();
TimeGen time_gen = TimeGen();
SizeGen size_gen = SizeGen();

class RequestGenerator : public Request {
public:

    RequestGenerator();
    ~RequestGenerator();

    /// \brief                  Function generates request
    /// \param asu
    /// \param stack_dist
    /// \return
    static Request GenerateRequest(Asu asu, StackDist stack_dist);

private:
    static Lba GenerateLba(StackDist stack_dist);
    static OpCode GetReadOpCode();
    static Timestamp GenerateTime();
    static OpCode GetWriteOpCode();
    static ByteSize GenerateByteSize();
};