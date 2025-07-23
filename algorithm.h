#pragma once
#include <vector>
#include <functional>

// 傳入目標函數
std::vector<double> differential_evolution(
    int D, int NP, int G, double p, double c, double minVal, double maxVal,
    std::function<double(const std::vector<double>&)> func
);