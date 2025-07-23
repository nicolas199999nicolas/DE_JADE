#include "algorithm.h"
#include "functions.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

vector<double> differential_evolution(
    int D, int NP, int G, double p, double c, double minVal, double maxVal,
    function<double(const vector<double>&)> f
) {
    mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    uniform_real_distribution<> rand01(0.0, 1.0);
    uniform_int_distribution<> randint1D(1, D);

    // 行 03: 創建隨機初始種群
    vector<vector<double>> population;
    for (int i = 0; i < NP; ++i)
        population.push_back(generateRandomIndividual(D, minVal, maxVal, gen));
    // 輸出初始種群
    cout << "Population size: " << population.size() << "\n";

    // 行 04-05: 初始化外部檔案 A 和自適應參數 muCR, muF
    vector<vector<double>> A;
    double muCR = 0.5, muF = 0.5;

    // 行 04: 主迭代 G=世代
    for (int g = 1; g <= G; ++g) {
        // 行 05: 初始化成功參數集合
        vector<double> SF, SCR;
        cout << "Generation " << g << " running...\n";
        //輸出參數
        cout << "muCR: " << muCR << ", muF: " << muF << "\n";
        // 行 06: 遍歷種群 NP=個體數
        for (int i = 0; i < NP; ++i) {

            // 正態分佈生成 CRi，標轉差0.1，確保 CRi 在 [0,1] 範圍內
            normal_distribution<> randn(muCR, 0.1);
            double CRi = max(0.0, min(1.0, randn(gen)));

            // 柯西分佈生成 Fi，標準差0.1
            cauchy_distribution<> randc(muF, 0.1);
            double Fi = randc(gen);
            while (Fi <= 0.0) Fi = randc(gen);// 確保 Fi > 0

            // 行 08: 選擇前 100p% 的最佳個體
            vector<pair<double, int>> fitness;
            for (int idx = 0; idx < NP; ++idx)
                fitness.emplace_back(f(population[idx]), idx);
            // 按照適應度排序
            sort(fitness.begin(), fitness.end());
            int top = max(1, static_cast<int>(p * NP));
            uniform_int_distribution<> randTop(0, top - 1);
            int pbestIdx = fitness[randTop(gen)].second;
            const auto& xpbest = population[pbestIdx];

            // 行 09: 選擇 xr1,g != xi,g
            int r1;
            do { r1 = uniform_int_distribution<>(0, NP - 1)(gen); } while (r1 == i);
            const auto& xr1 = population[r1];

            // 行 10: 從 P ∪ A 選擇 xr2,g
            vector<vector<double>> P_union_A = population;
            P_union_A.insert(P_union_A.end(), A.begin(), A.end());
            int r2;
            do { r2 = uniform_int_distribution<>(0, P_union_A.size() - 1)(gen); } while (r2 == i || r2 == r1);
            const auto& xr2 = P_union_A[r2];

            // 行 11: 變異
            vector<double> vi(D);
            for (int j = 0; j < D; ++j)
                vi[j] = population[i][j] + Fi * (xpbest[j] - population[i][j]) + Fi * (xr1[j] - xr2[j]);

            // 行 12: 隨機維度
            int jrand = randint1D(gen) - 1;

            // 行 13-19: 交叉 D=維度
            vector<double> ui(D);
            for (int j = 0; j < D; ++j)
                ui[j] = (j == jrand || rand01(gen) < CRi) ? vi[j] : population[i][j];

            // 行 20: 評估 ui 的適應度
            if (f(population[i]) > f(ui)) {
                population[i] = ui;
                A.push_back(population[i]);
                SCR.push_back(CRi);
                SF.push_back(Fi);
            }
        }
        // 行 26: 維護外部檔案大小
        while (A.size() > NP) {
            int idx = uniform_int_distribution<>(0, A.size() - 1)(gen);
            A.erase(A.begin() + idx);
        }
        // 行 27-28: 更新自適應參數 muCR, muF
        if (!SCR.empty()) muCR = (1 - c) * muCR + c * meanA(SCR);
        if (!SF.empty()) muF = (1 - c) * muF + c * meanL(SF);
    }
    // 行 30: 返回最優解
    cout << "Optimization completed.\n";
    auto bestIt = min_element(population.begin(), population.end(),
        [&](const auto& a, const auto& b) { return f(a) < f(b); });
    return *bestIt;
}