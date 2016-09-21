#include "DistributionGenerator.h"
using namespace std;


DistributionGenerator::DistributionGenerator()
{
}


DistributionGenerator::~DistributionGenerator()
{
}

void DistributionGenerator::Pareto(std::vector<double>& values, int value_count, int k, double a)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	for (int i = 0; i < value_count; i++)
	{
		//get uniform number
		double number = distribution(generator);

		//get pareto value
		double value = static_cast<double>(k) / static_cast<double>(pow(number, static_cast<double>(1.0 / static_cast<double>(a))));
		values.push_back(value);
	}
}

void DistributionGenerator::ShowDistributionDensity(std::vector<double>& values, int value_count, int interval_count)
{
	double low_bound = *min_element(values.begin(), values.end());
	double up_bound = *max_element(values.begin(), values.end());
	int step = ((up_bound - low_bound) / static_cast<double>(interval_count)) + 1;
	vector<double> counter(interval_count);

	for (int i = 0; i < value_count; i++)
	{
		int val = values[i] / step;
		counter[val]++;
	}

	ofstream density_file;
	density_file.open("Pareto_density.txt");
	for (int i = 0; i < interval_count; i++)
	{
		counter[i] /= static_cast<double>(value_count);
		density_file << counter[i] << endl;
	}
	density_file.close();
}


