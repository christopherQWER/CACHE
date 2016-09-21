#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

class DistributionGenerator
{
public:
	DistributionGenerator();
	~DistributionGenerator();

	/*
		k - is a location parameter (specifies minimal possible value)
		a - is a shape parameter (defines the tail of the distribution)
	*/
	static void Pareto(std::vector<double>& values, int value_count, int k, double a);
	static void ShowDistributionDensity(std::vector<double>& values, int value_count, int interval_count);
};

