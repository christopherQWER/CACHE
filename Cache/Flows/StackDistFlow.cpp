//
// Created by cat on 10/8/16.
//

#include "StackDistFlow.h"
using namespace std;


StackDistFlow::StackDistFlow(Asu asu,
                            Lba low_address,
                            const list<std::string>& input_pdf_paths,
                            ByteSize limit_value,
                            double switcher)
{
    counter = 0;
    _client_asu = asu;

    _low_address_bound = low_address;
    //_common_time = limit_value;
    //_curr_request_time = 0;

    //needed if two or more sources of pdf
    _switcher = switcher;

    _common_request_num = limit_value;
    _curr_request_num = 0;

    // Because only one pdf source for one application
    dist_gen = new StackDistanceGen(*input_pdf_paths.begin());
    gen = new RequestGenerator();
}

StackDistFlow::~StackDistFlow()
{
    if (uni_int_asu != NULL)
    {
        delete uni_int_asu;
    }
    if (dist_gen != NULL)
    {
        delete dist_gen;
    }
}

Request* StackDistFlow::GetRequest()
{
    return ReqNumberBasedGeneration();
}

//Request* StackDistFlow::TimeBasedGeneration()
//{
//    Request* req = new Request();
//    if (_curr_request_time < _common_time)
//    {
//        if ( _request_queue.empty() )
//        {
//            list<Request> tmp;
////            for (int i = 0; i < _app_count; i++)
////            {
//                Request request = gen->GenerateRequest(GenerateAsu(),
//                        GenerateStackDistance());
//                tmp.push_back(request);
//            //}
//            tmp.sort();
//            for (auto request : tmp)
//            {
//                _request_queue.push_back(request);
//            }
//        }
//        _curr_request_time = _request_queue.front()._timestamp;
//        *req = _request_queue.front();
//        _request_queue.pop_front();
//        return req;
//    }
//    else
//    {
//        return nullptr;
//    }
//}

Request* StackDistFlow::ReqNumberBasedGeneration()
{
    Request* req = new Request();
    if (_curr_request_num < _common_request_num)
    {
        StackDist st_dst = GenerateStackDistance();
        *req = gen->GenerateRequest(_client_asu, st_dst, _low_address_bound);

        _curr_request_time += req->_timestamp;
        req->_timestamp = _curr_request_time;

        _curr_request_num++;
        return req;
    }
    else
    {
        return NULL;
    }
}


//Asu StackDistFlow::GenerateAsu()
//{
//    Asu asu = static_cast<Asu>(uni_int_asu->GetRandomValue());
//    return asu;
//}

StackDist StackDistFlow::GenerateStackDistance()
{
    StackDist st_dst = dist_gen->GetRandomValue();
    return static_cast<StackDist>(st_dst);
}

bool StackDistFlow::IsEndOfFlow()
{
    bool flag = _curr_request_num >= _common_request_num;
    if (flag)
    {
        return flag;
    }
    return flag;
}

StackDistFlow::StackDistFlow()
{

}

void StackDistFlow::SaveTestPdf()
{
    dist_gen->WritePairsToFile(Utils::PathCombine(string("//home//cat//Documents//CACHE//Inputs//Flows"),
            string("Uniform_PDF_test.txt")));
}