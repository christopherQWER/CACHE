//
// Created by cat on 10/27/16.
//

#include "StaticPartial.h"
#include "../Flows/TraceFileFlow.h"
#include "../Utils/Paths.h"
#include "../Utils/Utils.h"
#include "../Loggers/Logger.h"
#define TYPE LCONSOLE
using namespace std;

void StaticPartial::PercentPartial()
{

}

void StaticPartial::EqualPartial(list<AppClass> clientList, const string& file_name)
{
    Logger *logger = Logger::CreateLogger(TYPE);
    logger->ShowLogText(INFO, "=================Start: WebSearch1.spc=================");

    Request *request;
    Flow *flow = new TraceFileFlow(file_name);
    string results_dir = _GISTS_DIR_ + string("//") + Utils::GetFileNameWithoutExt(file_name);


    int counter = 0;
    int gist_counter = 0;
}
