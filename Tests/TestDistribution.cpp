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

void TestDistribution::GeneratingRandomTest()
{
    int rand_num = 0;
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
        rand_num = gen.ParetoGenerator(k, a);
        values.push_back(rand_num);
        if (gen.IsInMap(rand_num))
        {
            gen._stack_dist[rand_num]++;
        }
        else
        {
            gen._stack_dist.insert(pair<int, double>(rand_num, 1));
        }
    }

    gen.GetPDF(count_experiments);
    Utils::WriteFile(output_file, gen._stack_dist);

    gen.GetRandomByPDF(new_values, count_experiments);
    gen.Clear();

    for (int i = 0; i < count_experiments; i++)
    {
        if (gen.IsInMap(new_values[i]))
        {
            gen._stack_dist[new_values[i]]++;
        }
        else
        {
            gen._stack_dist.insert(pair<int, double>(new_values[i], 1));
        }
    }
    gen.GetPDF(count_experiments);
    Utils::WriteFile(output_file_2, gen._stack_dist);
}

void TestDistribution::PDFTest()
{
    int rand_num = 0;
    int count_experiments = 1000000;
    int k = 10;
    double a = 2;
    vector<int> values;
    Generator gen = Generator();

    for (int i = 0; i < count_experiments; i++)
    {
        rand_num = gen.ParetoGenerator(k, a);
        values.push_back(rand_num);
        if (gen.IsInMap(rand_num))
        {
            gen._stack_dist[rand_num]++;
        }
        else
        {
            gen._stack_dist.insert(pair<int, double>(rand_num, 1));
        }
    }

    gen.GetPDF(count_experiments);
    double probabilities = 0;
    for (Map_itr it = gen._stack_dist.begin(); it != gen._stack_dist.end(); ++it)
    {
        probabilities += it->second;
    }

    if (probabilities >= 1)
    {
        cout << "PDF test: OK" << endl;
    }
    else
    {
        cout << "PDF test: FAILED" << endl;
    }
}

int TestDistribution::MainTester()
{
    PDFTest();
    GeneratingRandomTest();
    return 0;
}