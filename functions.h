#pragma once
#include <vector>
#include <random>

double ackley(const std::vector<double>& x);
std::vector<double> generateRandomIndividual(int D, double min, double max, std::mt19937& gen);
double meanA(const std::vector<double>& S);
double meanL(const std::vector<double>& S);