

#include <cassert>
#include <ctime>
#include "misc/combinatorics.h"
#include "misc/PatternBuilder.h"
#include "patternResolver.h"
#include "fastPatternResolver.h"

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
void compare(
        int testCnt, int minS, int maxS, int minP, int maxP, int minE, int maxE, int pCnt, double nonZeroPart,
        bool hardCheck
) {
    // повторяем testCnt раз
    for (int i = 0; i < testCnt; i++) {
        int sourceSize = std::abs(std::rand()) % (maxS - minS) + minS;
        // формируем случайную матрицу-источник
        int **source = randomMatrix(sourceSize, minE, maxE, nonZeroPart);

        // формируем случайную матрицу-паттерн
        int patternSize = std::abs(std::rand()) % (maxP - minP) + minP;
        int **pattern = randomMatrix(patternSize, minE, maxE, nonZeroPart);

        // std::cout << "sourceSize " << sourceSize << " patternSize " << patternSize << std::endl;

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
        std::vector<CombinatoricsData> patternsList =
                getAllPatterns(res, sourceSize, pattern, patternSize, hardCheck);
        std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
                patterns(patternsList.begin(), patternsList.end());

        //  std::cout << "got pattern list" << std::endl;

        std::vector<CombinatoricsData> fastPatternsList =
                fastGetAllPatterns(res, sourceSize, pattern, patternSize, hardCheck);
        std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
                fastPatterns(patternsList.begin(), patternsList.end());
        //   std::cout << "got fast pattern list" << std::endl;


        for (CombinatoricsData cd: patterns)
            if (fastPatterns.find(cd) == fastPatterns.end())
                assert(false);

        for (CombinatoricsData cd: fastPatterns)
            if (patterns.find(cd) == patterns.end())
                assert(false);
    }
}

/**
 * Сверка результатов поиска изоморфных подграфов с помощью быстрого алгоритма и с помощью полного перебора
 */
void compareTest1() {
    compare(
            20, 12, 13, 5, 7, -100, 100,
            std::abs(std::rand()) % 10 + 2, 0.5,
            true
    );
}

/**
 * Сверка результатов поиска изоморфных подграфов с помощью быстрого алгоритма и с помощью полного перебора
 */
void compareTest2() {
    compare(
            20, 12, 13, 5, 7, -100, 100,
            std::abs(std::rand()) % 10 + 2, 0.5,
            false
    );
}

/**
 * Сверка результатов поиска изоморфных подграфов с помощью быстрого алгоритма и с помощью полного перебора
 */
void compareTest3() {
    compare(
            20, 12, 13, 5, 7, -100, 100,
            std::abs(std::rand()) % 10 + 2, 1.0,
            true
    );
}

/**
 * Сверка результатов поиска изоморфных подграфов с помощью быстрого алгоритма и с помощью полного перебора
 */
void compareTest4() {
    compare(
            20, 12, 13, 5, 7, -100, 100,
            std::abs(std::rand()) % 10 + 2, 1.0,
            true
    );
}

/**
 * Сверка результатов поиска изоморфных подграфов с помощью быстрого алгоритма и с помощью полного перебора
 */
void compareTest5() {
    compare(
            20, 12, 13, 5, 7, -100, 100,
            std::abs(std::rand()) % 10 + 2, 1.0,
            false
    );
}

/**
 * Сверка результатов поиска изоморфных подграфов с помощью быстрого алгоритма и с помощью полного перебора
 */
void compareTest6() {
    compare(
            20, 12, 13, 5, 7, -100, 100,
            std::abs(std::rand()) % 10 + 2, 1.0,
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

    std::cout << "TEST 1:" << std::endl;
    compareTest1();
    std::cout << "TEST 2:" << std::endl;
    compareTest2();
    std::cout << "TEST 3:" << std::endl;
    compareTest3();
    std::cout << "TEST 4:" << std::endl;
    compareTest4();
    std::cout << "TEST 5:" << std::endl;
    compareTest5();
    std::cout << "TEST 6:" << std::endl;
    compareTest6();
}



