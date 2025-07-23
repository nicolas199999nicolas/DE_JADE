#include "functions.h"
#include <cmath>
#include <algorithm>
#define M_PI 3.14159265358979323846
double ackley(const std::vector<double>& x) {
    const double a = 20.0, b = 0.2, c = 2 * M_PI;
    int D = x.size();
    double sum1 = 0.0, sum2 = 0.0;
    for (double val : x) {
        sum1 += val * val;
        sum2 += cos(c * val);
    }
    return -a * exp(-b * sqrt(sum1 / D)) - exp(sum2 / D) + a + exp(1.0);
}

std::vector<double> generateRandomIndividual(int D, double min, double max, std::mt19937& gen) {
    std::vector<double> individual(D);
    std::uniform_real_distribution<> dis(min, max);
    for (int j = 0; j < D; ++j)
        individual[j] = dis(gen);
    return individual;
}

double meanA(const std::vector<double>& S) {
    if (S.empty()) return 0.0;
    double sum = 0.0;
    for (double val : S) sum += val;
    return sum / S.size();
}

double meanL(const std::vector<double>& S) {
    if (S.empty()) return 0.0;
    double sumF = 0.0, sumF2 = 0.0;
    for (double f : S) {
        sumF += f;
        sumF2 += f * f;
    }
    return sumF2 / sumF;
}