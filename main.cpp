#include <iostream>
#include <vector>
#include "algorithm.h"
#include "functions.h"
using namespace std;

int main() {
    // 選擇目標函數
    auto targetFunction = F6; // 只需更改這一行即可切換目標函數

    // 參數設置
    const int D = 30; // 維度
    const int NP = 100; // 種群大小
    const int G = 100; // 迭代次數
    const double p = 0.05; //取前幾%的個體
    const double c = 0.1; //自適應參數
    
    //函數邊界
    const double minVal = -32;
    const double maxVal = 32;

    cout << "Initializing parameters:\n";
    cout << "D: " << D << ", NP: " << NP << ", G: " << G << ", p: " << p << ", c: " << c << "\n";

    // 呼叫演算法
    vector<double> best = differential_evolution(D, NP, G, p, c, minVal, maxVal, targetFunction);

    // 輸出最佳解
    cout << "Best solution: ";
    for (double val : best) cout << val << " ";
    cout << "\nFitness: " << targetFunction(best) << "\n";
    system("pause");
    return 0;
}