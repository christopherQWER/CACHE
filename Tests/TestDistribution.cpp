//
// Created by cat on 10/9/16.
//

#include "TestDistribution.h"
using namespace std;

TestDistribution::TestDistribution()
{

}

TestDistribution::~TestDistribution()
{

}

void TestDistribution::PdfTest()
{
    int count_experiments = 1000000;
    int k = 10;
    double a = 2;
    vector<int> values;
    vector<int> new_values;
    Generator gen = Generator();
    string output_file = "/home/cat/Documents/CACHE/Tests/Results/PDF.txt";
    string output_file_2 = "/home/cat/Documents/CACHE/Tests/Results/PDF_test.txt";

    for (int i = 0; i < count_experiments; i++)
    {
        values.push_back(gen.ParetoGenerator(k, a));
    }
    gen.GetPDF(values, count_experiments);
    Utils::WriteFile(output_file, gen._stack_dist);

    gen.GetRandomByPDF(new_values, count_experiments);
    gen.GetPDF(new_values, count_experiments);
    Utils::WriteFile(output_file_2, gen._stack_dist);
}

int TestDistribution::MainTester()
{
    PdfTest();
    return 0;
}

