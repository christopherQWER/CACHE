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


class RequestGenerator : public Request {
public:

    RequestGenerator();
    ~RequestGenerator();

    /// \brief                  Function generates request
    /// \param asu
    /// \param stack_dist
    /// \return
    Request GenerateRequest(Asu asu, StackDist stack_dist, Lba low_address_bound);

private:
    Lba GenerateLba(StackDist stack_dist, Lba low_address_bound);
    OpCode GetReadOpCode();
    Timestamp GenerateTime();
    OpCode GetWriteOpCode();
    ByteSize GenerateByteSize();

    LbaGen *lba_gen;
    TimeGen *time_gen;
    SizeGen *size_gen;
};