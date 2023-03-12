#include <iostream>
#include <cassert>
#include <ctime>
#include "misc/combinatorics.h"
#include "misc/PatternBuilder.h"
#include "fastPatternResolver.h"


/**
 * Проверка быстрого алгоритма поиска изоморфных подграфов
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
void testPattern(
        int testCnt, int minS, int maxS, int minP, int maxP, int minE, int maxE, int pCnt, double nonZeroPart,
        bool hardCheck
);

/**
 * Проверка быстрого алгоритма поиска изоморфных подграфов
 */
void test1() {
    testPattern(
            20, 12, 13, 5, 7, -100, 100,
            std::abs(std::rand()) % 10 + 2, 1.0,
            true
    );
}

/**
 * Проверка быстрого алгоритма поиска изоморфных подграфов
 */
void test3() {
    testPattern(
            20, 12, 13, 5, 7, -100, 100,
            std::abs(std::rand()) % 10 + 2, 0.5,
            true
    );
}

/**
 * Проверка быстрого алгоритма поиска изоморфных подграфов
 */void test5() {
    testPattern(
            20, 12, 13, 5, 7, -10, 10,
            std::abs(std::rand()) % 10 + 2, 0.3,
            false
    );
}


/**
 * Главный метод
 * @return код возрата
 */
int main() {
    long  ltime = time (nullptr);
    int stime = (unsigned int) ltime/2;
    srand(stime);
    test1();
    test3();
    test5();
}


/**
 * Проверка быстрого алгоритма поиска изоморфных подграфов
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
void testPattern(
        int testCnt, int minS, int maxS, int minP, int maxP, int minE, int maxE, int pCnt, double nonZeroPart,
        bool hardCheck
) {
    // повторяем testCnt раз
    for (int i = 0; i < testCnt; i++) {
        // получаем случайный размер матрицы
        int sourceSize = std::abs(std::rand()) % (maxS - minS) + minS;
        // формируем случайную матрицу-источник
        int **source = randomMatrix(sourceSize, minE, maxE, nonZeroPart);
        // получаем случайный размер матрицы
        int patternSize = std::abs(std::rand()) % (maxP - minP) + minP;
        // формируем случайную матрицу-паттерн
        int **pattern = randomMatrix(patternSize, minE, maxE, nonZeroPart);
        // создаём объект построителя паттернов
        PatternBuilder pb = PatternBuilder(source, sourceSize);

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

        // выводим информацию о добавленных паттернах
        std::cout << "ADD:" << std::endl;
        for (CombinatoricsData rp: genCombinatoricsData) {
            for (int k = 0; k < patternSize; k++)
                std::cout << rp.getData()[k] << " ";
            std::cout << std::endl;
        }

        // ищем паттерны с помощью быстрого алгоритма
        int **res = pb.getData();

        std::vector<CombinatoricsData> patternsList =
                fastGetAllPatterns(res, sourceSize, pattern, patternSize, hardCheck);
        std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
                patterns(patternsList.begin(), patternsList.end());

        // выводим найденные паттерны
        std::cout << "FOUND:" << std::endl;
        for (CombinatoricsData rp: patterns) {
            for (int k = 0; k < patternSize; k++)
                std::cout << rp.getData()[k] << " ";
            std::cout << std::endl;
        }

        for (CombinatoricsData cd: genCombinatoricsData)
            if (patterns.find(cd) == patterns.end())
                assert(false);

    }
}