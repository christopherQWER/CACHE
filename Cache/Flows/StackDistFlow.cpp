//
// Created by cat on 10/8/16.
//

#include "StackDistFlow.h"
using namespace std;
UniformInt *uni_int_asu;
deque<StackDistanceGen*> stack_dist_gen_queue;


StackDistFlow::StackDistFlow(int client_count,
                            const list<std::string>& input_pdf_paths,
                            Limit type,
                            ByteSize limit_value,
                            double switcher)
{
    if (client_count > 0)
    {
        _app_count = client_count;

        _common_time = limit_value;
        _curr_request_time = 0;

        _switcher = switcher;

        _common_request_num = limit_value;
        _curr_request_num = 0;

        _specified_limit = type;
        uni_int_asu = new UniformInt(1, client_count);
    }

    for (auto pdf_source : input_pdf_paths)
    {
        stack_dist_gen_queue.push_back(new StackDistanceGen(pdf_source));
    }
}

StackDistFlow::~StackDistFlow()
{
    if (uni_int_asu != nullptr)
    {
        delete uni_int_asu;
    }
    for (std::deque<StackDistanceGen*>::iterator it = stack_dist_gen_queue.begin();
         it != stack_dist_gen_queue.end(); ++it)
    {
        delete *it;
    }
    if (!stack_dist_gen_queue.empty())
    {
        stack_dist_gen_queue.clear();
    }
}

Request* StackDistFlow::GetRequest()
{
    switch (_specified_limit)
    {
        case TIME:
        {
            return TimeBasedGeneration();
        }
        case REQUEST_NUMBER:
        {
            return ReqNumberBasedGeneration();
        }
    }
}

Request* StackDistFlow::TimeBasedGeneration()
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

Request* StackDistFlow::ReqNumberBasedGeneration()
{
    Request* req = new Request();
    if (_curr_request_num < _common_request_num)
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
        *req = _request_queue.front();
        _request_queue.pop_front();
        _curr_request_num++;
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
    if (_switcher != 0)
    {
        if (_curr_request_time >= _switcher)
        {
            StackDistanceGen* st_dst_gen = stack_dist_gen_queue.front();
            stack_dist_gen_queue.pop_front();
            stack_dist_gen_queue.push_back(st_dst_gen);
        }
    }
    return static_cast<StackDist>(stack_dist_gen_queue.front()->GetRandomValue());
}

bool StackDistFlow::IsEndOfFlow()
{
    if (_specified_limit == TIME)
    {
        return _curr_request_time > _common_time;
    }
    else
    {
        return _curr_request_num > _common_request_num;
    }
}

StackDistFlow::StackDistFlow()
{

}