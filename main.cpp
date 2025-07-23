#include <iostream>
#include <vector>
#include "algorithm.h"
#include "functions.h"
using namespace std;

int main() {
    // 參數設置
    const int D = 30;
    const int NP = 100;
    const int G = 500;
    const double p = 0.05;
    const double c = 0.1;
    const double minVal = -32;
    const double maxVal = 32;

    cout << "Initializing parameters:\n";
    cout << "D: " << D << ", NP: " << NP << ", G: " << G << ", p: " << p << ", c: " << c << "\n";

    // 呼叫演算法
    vector<double> best = differential_evolution(D, NP, G, p, c, minVal, maxVal, ackley);

    // 輸出最佳解
    cout << "Best solution: ";
    for (double val : best) cout << val << " ";
    cout << "\nFitness: " << ackley(best) << endl;

    system("pause");
    return 0;
}