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
    double rand_num = 0;
    double int_part = 0;
    double fract_part = 0;
    double prob = 0;
    int count_experiments = 1000000;
    int k = 10;
    double a = 2;
    map<int, double> pdf_map;
    vector<int> rand_vector_1;
    vector<int> rand_vector_2;
    Pareto gen = Pareto(k, a);

    string output_file = "/home/cat/Documents/CACHE/Tests/Results/PDF.txt";
    string output_file_2 = "/home/cat/Documents/CACHE/Tests/Results/PDF_test.txt";

    // Inicialize map with rand values and pdfs (only unical values)
    // Inicialize vector with random values
    for (int i = 0; i < count_experiments; i++)
    {
        rand_num = gen.Generate();
        fract_part = modf(rand_num, &int_part);
        prob = gen.GetPDFTheor(rand_num);

        if (pdf_map.find(static_cast<int>(int_part)) == pdf_map.end())
            Utils::AppendToFile(output_file, static_cast<int>(int_part), gen.GetPDFTheor(rand_num));

        pdf_map.insert(pair<int, double>(int_part, prob));
        rand_vector_1.push_back(static_cast<int>(int_part));
    }

    for (int i = 0; i < count_experiments; i++)
    {
        rand_num = gen.GetRandomByPDF(pdf_map.at(rand_vector_1[i]));
        fract_part = modf(rand_num, &int_part);
        if (find(rand_vector_2.begin(), rand_vector_2.end(), static_cast<int>(int_part)) == rand_vector_2.end())
            Utils::AppendToFile(output_file_2, static_cast<int>(int_part), gen.GetPDFTheor(rand_num));
        rand_vector_2.push_back(static_cast<int>(int_part));
    }

    if (rand_vector_1 == rand_vector_2)
    {
        cout << "Generating random by PDF: OK" << endl;
    }
    else
    {
        cout << "Generating random by PDF: FAILED" << endl;
    }
}

void TestDistribution::PDFTest()
{
    double rand_num = 0;
    double int_part = 0;
    double fract_part = 0;
    double probabilities = 0;
    int count_experiments = 1000000;
    int k = 10;
    double a = 2;
    set<int> values;
    Pareto gen = Pareto(k, a);

    for (int i = 0; i < count_experiments; i++)
    {
        rand_num = gen.Generate();
        fract_part = modf(rand_num, &int_part);
        values.insert(static_cast<int>(int_part));
    }

    for (set<int>::iterator it = values.begin(); it != values.end(); ++it)
    {
        probabilities += gen.GetPDFTheor(*it);
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
    //PDFTest();
    GeneratingRandomTest();
    return 0;
}