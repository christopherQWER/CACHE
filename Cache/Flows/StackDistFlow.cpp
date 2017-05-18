//
// Created by cat on 10/8/16.
//

#include "StackDistFlow.h"
#include "../Generators/Exponential.h"
#include "../Generators/LbaGen.h"
using namespace std;
Exponential exp_gen = Exponential(3.5);
LbaGen lba_gen = LbaGen();

StackDistFlow::StackDistFlow()
{
    _beginning_time = 0;
}

StackDistFlow::~StackDistFlow()
{
    _address_buffer.clear();
    _stack_dist_ = 0;
    curr_buffer_size = 0;
    _beginning_time = 0;
}

Request *StackDistFlow::GetRequest()
{
    Request *request = new Request();
    Request::GenerateRequest(*request);
    _beginning_time += exp_gen.GetRandom();
    request->_timestamp = _beginning_time;
    Lba needed_lba = 0;
    //int size = GetBufferSize();


    return request;
}

