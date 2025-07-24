#pragma once
#include <vector>
#include <random>

double ackley(const std::vector<double>& x);
std::vector<double> generateRandomIndividual(int D, double min, double max, std::mt19937& gen);
double meanA(const std::vector<double>& S);
double meanL(const std::vector<double>& S);
double F1(const std::vector<double>& x);
double F3(const std::vector<double>& x);
double F5(const std::vector<double>& x);
double F6(const std::vector<double>& x);
double F7(const std::vector<double>& x);
double F8(const std::vector<double>& x);
double F9(const std::vector<double>& x);
double F10(const std::vector<double>& x);
