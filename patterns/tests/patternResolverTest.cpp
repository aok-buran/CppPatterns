#include <iostream>
#include <cassert>
#include <ctime>
#include "misc/combinatorics.h"
#include "misc/PatternBuilder.h"
#include "patternResolver.h"


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
void testPatternLoop(
        int testCnt, int minS, int maxS, int minP, int maxP, int minE, int maxE, int pCnt, double nonZeroPart,
        bool hardCheck
) {
    // повторяем testCnt раз
    for (int i = 0; i < testCnt; i++) {
        int sourceSize = std::abs(std::rand()) % (maxS - minS) + minS;
        // формируем случайную матрицу-источник
        int **source = randomMatrix(sourceSize, minE, maxE, nonZeroPart);

        int patternSize = std::abs(std::rand()) % (maxP - minP) + minP;
        // формируем случайную матрицу-паттерн
        int **pattern = randomMatrix(patternSize, minE, maxE, nonZeroPart);

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
                getAllPatterns(res, sourceSize, pattern, patternSize, hardCheck);
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


/**
  * Проверка алгоритма поиска изоморфных подграфов перебором
  */
void testLoop1() {
    testPatternLoop(
            100, 5, 7, 2, 4, 0, 2,
            std::abs(rand()) % 10 + 2, 0.5,
            true
    );
}

/**
 * Проверка алгоритма поиска изоморфных подграфов перебором
 */
void testLoop2() {
    testPatternLoop(
            10, 12, 13, 5, 7, -100, 100,
            std::abs(rand()) % 10 + 2, 0.5,
            false
    );
}

/**
 * Проверка алгоритма поиска изоморфных подграфов перебором
 */
void testLoop3() {
    testPatternLoop(
            100, 4, 6, 2, 4, 0, 2,
            std::abs(rand()) % 10 + 2, 1.0,
            false
    );
}

/**
 * Проверка алгоритма поиска изоморфных подграфов перебором
 */
void testLoop4() {
    testPatternLoop(
            100, 4, 6, 2, 4, 0, 2,
            std::abs(rand()) % 10 + 2, 0.5,
            false
    );
}

/**
 * Проверка алгоритма поиска изоморфных подграфов перебором
 */
void testLoop5() {
    testPatternLoop(
            100, 4, 6, 2, 4, 0, 2,
            std::abs(rand()) % 10 + 2, 0.2,
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

    testLoop1();
    testLoop2();
    testLoop3();
    testLoop4();
    testLoop5();
}
