#include <iostream>
#include <chrono>
#include "misc/combinatorics.h"
#include "misc/PatternBuilder.h"
#include "patternResolver.h"
#include "fastPatternResolver.h"
#include <fstream>

/**
 * Сверка результатов поиска изоморфных подграфов с помощью быстрого алгоритма и с помощью полного перебора
 *
 * @param testCnt     кол-во тестов
 * @param minS        минимальный размер матрицы-источника
 * @param maxS        максимальный размер матрицы-источника
 * @param minP        минимальный размер матрицы-паттерна
 * @param maxP        максимальный размер матрицы-паттерна
 * @param minE        минимальное значение элементов матриц
 * @param maxE        максимальный значение элементов матриц
 * @param pCnt        кол-во добавленных паттернов
 * @param nonZeroPart доля ненулевых элементов
 * @param hardCheck   флаг, нужна ли жёсткая сверка
 */
std::vector<std::pair<long long, long long>> compare(
        int testCnt, int minS, int maxS, int minP, int maxP, int minE, int maxE, int pCnt, double nonZeroPart,
        bool hardCheck
) {

    std::vector<std::pair<long long, long long>> timeList;

    // повторяем testCnt раз
    for (int i = 0; i < testCnt; i++) {
        int sourceSize = std::abs(std::rand()) % (maxS - minS) + minS;
        // формируем случайную матрицу-источник
        int **source = randomMatrix(sourceSize, minE, maxE, nonZeroPart);

        // формируем случайную матрицу-паттерн
        int patternSize = std::abs(std::rand()) % (maxP - minP) + minP;
        int **pattern = randomMatrix(patternSize, minE, maxE, nonZeroPart);

        std::cout << patternSize << " " << sourceSize << " " << std::endl;
        // создаём объект построителя паттернов
        PatternBuilder pb(source, sourceSize);
        // создаём список комбинаций, согласно которым был добавлен паттерн
        std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
                genCombinatoricsData;
        // повторяем, пока количество добавленных паттернов меньше pCnt
        for (int j = 0; j < pCnt;) {
            // получить случайную комбинацию
            CombinatoricsData rComb = getRandomCombination(sourceSize, patternSize);

            // если получилось добавить в дата-граф паттерн по полученной случайной комбинации
            if (pb.putPattern(pattern, patternSize, rComb)) {
                // увеличиваем количество добавленных паттернов
                j++;
                // добавляем комбинацию в список
                genCombinatoricsData.insert(rComb);
            }
        }
        // ищем паттерны с помощью быстрого алгоритма
        int **res = pb.getData();

        auto start = std::chrono::high_resolution_clock::now();

        std::vector<CombinatoricsData> patternsList =
                getAllPatterns(res, sourceSize, pattern, patternSize, hardCheck);
        std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
                patterns(patternsList.begin(), patternsList.end());

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(
                elapsed).count();

        start = std::chrono::high_resolution_clock::now();


        std::vector<CombinatoricsData> fastPatternsList =
                fastGetAllPatterns(res, sourceSize, pattern, patternSize, hardCheck);
        std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
                fastPatterns(patternsList.begin(), patternsList.end());

        elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microsecondsFast = std::chrono::duration_cast<std::chrono::microseconds>(
                elapsed).count();

        timeList.emplace_back(microseconds, microsecondsFast);
    }
    return timeList;
}


int main() {

    long  ltime = time (nullptr);
    int stime = (unsigned int) ltime/2;
    srand(stime);

    std::vector<std::pair<long long, long long>> resList;

    for (int i = 2; i < 4; i++) {
        std::cout << i << std::endl;
        for (double nz = 0.2; nz <= 1.0; nz += 0.2) {
            auto timeList = compare(
                    20, i * 3, i * 4, i * 2, i * 3, -100, 100,
                    std::abs(std::rand()) % 10 + 2, nz,
                    true
            );
            resList.insert(std::end(resList), std::begin(timeList), std::end(timeList));
        }
    }

    std::ofstream myfile;
    myfile.open("stats.txt");
    std::sort(resList.begin(), resList.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    for (auto &p: resList) {
        myfile << p.first << " " << p.second << std::endl;
    }

    myfile.close();
    return 0;
}
