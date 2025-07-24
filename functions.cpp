#include "functions.h"
#include <cmath>
#include <algorithm>
#include <random> // 確保使用隨機數生成器
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
double F1(const std::vector<double>& x) {
    double sum = 0.0;
    for (double val : x) {
        sum += val * val;
    }
    return sum;
}

double F3(const std::vector<double>& x) {
    double sum = 0.0;
    for (double val : x) {
        sum += fabs(val);
    }
    return sum*sum;
}
double F5(const std::vector<double>& x) {
    double sum = 0.0;
    int D = x.size();
    for (int i = 0; i < D - 1; ++i) {
        double term1 = 100 * pow((x[i + 1] - x[i] * x[i]), 2);
        double term2 = pow((x[i] - 1), 2);
        sum += term1 + term2;
    }
    return sum;
}
double F6(const std::vector<double>& x) {
    double sum = 0.0;
    for (double val : x) {
        sum += pow(fabs(val + 0.5), 2);
    }
    return sum;
}
double F7(const std::vector<double>& x) {
    double sum = 0.0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> rand01(0.0, 1.0); // 隨機生成 [0, 1]

    for (int i = 0; i < x.size(); ++i) {
        sum += pow(x[i], 4) * (i + 1) + rand01(gen);
    }
    return sum;
}
double F8(const std::vector<double>& x) {
    double sum = 0.0;
    for (double val : x) {
        sum += -val * sin(sqrt(fabs(val)));
    }
    return sum + x.size() * 418.98288727243369; // D * 418.98288727243369
}
double F9(const std::vector<double>& x) {
    double sum = 0.0;
    for (double val : x) {
        sum += pow(val, 2) - 10 * cos(2 * M_PI * val) + 10;
    }
    return sum;
}
double F10(const std::vector<double>& x) {
    const double a = 20.0, b = 0.2, c = 2 * M_PI;
    int D = x.size();
    double sum1 = 0.0, sum2 = 0.0;
    for (double val : x) {
        sum1 += val * val;
        sum2 += cos(c * val);
    }
    return -a * exp(-b * sqrt(sum1 / D)) - exp(sum2 / D) + a + exp(1.0);
}