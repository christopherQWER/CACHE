//
// Created by cat on 10/8/16.
//

#include "StackDistFlow.h"
using namespace std;
UniformInt *uni_int_asu;
StackDistanceGen *stack_dist_gen;


StackDistFlow::StackDistFlow(int client_count,
                            const string& input_pdf_path,
                            Timestamp time)
{
    if (client_count > 0)
    {
        _app_count = client_count;
        _input_pdf = input_pdf_path;
        _common_time = time;
        _curr_request_time = 0;
        _common_request_num = 0;
        _curr_request_num = 0;
        uni_int_asu = new UniformInt(1, client_count);
    }
    stack_dist_gen = new StackDistanceGen(input_pdf_path);
}

StackDistFlow::~StackDistFlow()
{
    if (uni_int_asu != nullptr)
    {
        delete uni_int_asu;
    }
    if (stack_dist_gen != nullptr)
    {
        delete stack_dist_gen;
    }
}

Request* StackDistFlow::GetRequest()
{
    Request* req = new Request();
    if (_curr_request_time < _common_time)
    {
        if ( _request_queue.empty() )
        {
            list<Request> tmp;
            for (int i = 0; i < _app_count; i++)
            {
                Request request = RequestGenerator::GenerateRequest(GenerateAsu(),
                        GenerateStackDistance());
                tmp.push_back(request);
            }
            tmp.sort();
            for (auto request : tmp)
            {
                _request_queue.push_back(request);
            }
        }
        _curr_request_time = _request_queue.front()._timestamp;
        *req = _request_queue.front();
        _request_queue.pop_front();
        return req;
    }
    else
    {
        return nullptr;
    }
}

Asu StackDistFlow::GenerateAsu()
{
    return static_cast<Asu>(uni_int_asu->GetRandomValue());
}

StackDist StackDistFlow::GenerateStackDistance()
{
    return static_cast<StackDist>(stack_dist_gen->GetRandomValue());
}

bool StackDistFlow::IsEndOfFlow()
{
    return _curr_request_time > _common_time;
}