//
// Created by cat on 10/9/16.
//

#include <Generators/UniformReal.h>
#include <Generators/Pareto.h>
#include "TestDistribution.h"

using namespace std;

TestDistribution::TestDistribution()
{
}

TestDistribution::~TestDistribution()
{
}

void TestDistribution::GetRandByPDFTest()
{
    double rand_num = 0;
    double probability = 0;
    int count_experiments = 1000000;
    int k = 10;
    double a = 2;
    map<int, double> pdf_map;
    vector<int> rand_vector_1;
    vector<int> rand_vector_2;
    //Pareto gen = Pareto(k, a);

    string output_file = "/home/cat/Documents/CACHE/Tests/Results/PDF.txt";
    string output_file_2 = "/home/cat/Documents/CACHE/Tests/Results/PDF_test.txt";

    // Inicialize map with rand values and pdfs (only unical values)
    // Inicialize vector with random values
//    for (int i = 0; i < count_experiments; i++)
//    {
//        rand_num = gen.Generate();
//        probability = gen.GetPDF(rand_num);
//
//        if (pdf_map.find(static_cast<int>(int_part)) == pdf_map.end())
//            Utils::AppendToFile(output_file, static_cast<int>(int_part), gen.GetPDF(rand_num));
//
//        pdf_map.insert(pair<int, double>(int_part, prob));
//        rand_vector_1.push_back(static_cast<int>(int_part));
//    }
//
//    for (int i = 0; i < count_experiments; i++)
//    {
//        rand_num = gen.GetRandomByPDF(pdf_map.at(rand_vector_1[i]));
//        if (find(rand_vector_2.begin(), rand_vector_2.end(), static_cast<int>(int_part)) == rand_vector_2.end())
//            Utils::AppendToFile(output_file_2, static_cast<int>(int_part), gen.GetPDF(rand_num));
//        rand_vector_2.push_back(static_cast<int>(int_part));
//    }

    if (rand_vector_1 == rand_vector_2)
    {
        cout << "Generating random by PDF: OK" << endl;
    }
    else
    {
        cout << "Generating random by PDF: FAILED" << endl;
    }
}

void TestDistribution::GetCDFTest()
{
//    ChiSquare gen = ChiSquare(5.0);
//    gen.GetPDF(1000000, "/home/cat/Documents/CACHE/Inputs/Flows/Chi_Square_PDF.txt");
//    gen.GetCDF(1000000, "/home/cat/Documents/CACHE/Inputs/Flows/Chi_Square_CDF.txt");

    UniformReal uni_gen = UniformReal(1.0, 100.0);
    uni_gen.GetPDF(1000000, "/home/cat/Documents/CACHE/Inputs/Flows/Uniform_PDF.txt");
    uni_gen.GetCDF(1000000, "/home/cat/Documents/CACHE/Inputs/Flows/Uniform_CDF.txt");

//    Pareto pareto_gen = Pareto(1, 3);
//    pareto_gen.GetPDF(1000000, "/home/cat/Documents/CACHE/Inputs/Flows/Pareto_PDF.txt");
//    pareto_gen.GetCDF(1000000, "/home/cat/Documents/CACHE/Inputs/Flows/Pareto_CDF.txt");
}

void TestDistribution::GetPDFTest()
{
//    int rand_int_value = 0;
//    double rand_val = 0;
//    double pdf_val = 0;
//    double sum = 0;
//    int count_experiments = 1000000;
//    int k = 10;
//    double a = 2;
//    map<int, double> values;
//    map<int, double>::iterator it;
//    Pareto gen = Pareto(k, a);
//    string output_file = string("PDF.txt");
//
//    for (int i = 0; i < count_experiments; i++)
//    {
//        rand_val = gen.Generate();
//        pdf_val = gen.GetPDF(rand_val);
//        rand_int_value = Utils::DoubleToInt(rand_val);
//        it = values.find(rand_int_value);
//        if (it == values.end())
//        {
//            values.insert(pair<int, double>(rand_int_value, pdf_val));
//            sum += pdf_val;
//        }
//    }
//
//    for (it = values.begin(); it != values.end(); ++it)
//    {
//        Utils::AppendToFile(output_file, it->first, it->second);
//    }
//
//    if (sum > 0.99 && sum < 1.1)
//    {
//        cout << "PDF test: OK" << endl;
//    }
//    else
//    {
//        cout << "PDF test: FAILED" << endl;
//    }
}

int TestDistribution::MainTester()
{
    //GetPDFTest();
    //GetRandByPDFTest();
    GetCDFTest();
    return 0;
}