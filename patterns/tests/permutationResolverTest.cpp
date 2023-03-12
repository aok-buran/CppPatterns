#include <cassert>
#include <ctime>
#include <iostream>
#include "patternResolver.h"

/**
 * Ручной тест
 */
void test1() {

    int size = 7;

    int sourceArr[7][7]{
            {0, 1, 1, 0, 0, 0, 0},
            {1, 0, 0, 1, 1, 0, 0},
            {1, 0, 0, 0, 1, 0, 1},
            {0, 1, 0, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 0, 1},
            {0, 0, 0, 1, 0, 0, 1},
            {0, 0, 1, 1, 1, 1, 0}
    };

    int **source = new int *[size];
    for (int i = 0; i < size; i++) {
        source[i] = new int[size];
        for (int j = 0; j < size; j++)
            source[i][j] = sourceArr[i][j];
    }


    int targetArr[7][7]{
            {0, 1, 1, 0, 0, 0, 0}, // A
            {1, 0, 0, 1, 1, 0, 0}, // Б
            {1, 0, 0, 1, 0, 1, 0}, // В
            {0, 1, 1, 0, 1, 1, 0}, // Г
            {0, 1, 0, 1, 0, 1, 1}, // Д
            {0, 0, 1, 1, 1, 0, 1}, // Е
            {0, 0, 0, 0, 1, 1, 0}  // Ж
    };


    int **target = new int *[size];
    for (int i = 0; i < size; i++) {
        target[i] = new int[size];
        for (int j = 0; j < size; j++)
            target[i][j] = targetArr[i][j];
    }


    std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
            ps = getAllIsomorphicPermutations(source, target, 7, false);

    assert(ps.find(CombinatoricsData(
            new int[7]{0, 1, 2, 4, 3, 6, 5}, 7
    )) != ps.end());
    assert(ps.find(CombinatoricsData(
            new int[7]{0, 2, 1, 4, 6, 3, 5}, 7
    )) != ps.end());
}

/**
 * Тест для проверки, что если переставить матрицу по той или иной перестановке,
 * то при поиске перестановок она будет найдена
 */
void test2() {
    for (int i = 0; i < 100; i++) {
        std::cout << "i=" << i << std::endl;
        int n = std::rand() % 7 + 3;
        int **m = randomMatrix(n, -100, 100, 0.7);

        int *permutation = getRandomPermutation(n);

        int **pm = makePermute(m, n, permutation);

        std::cout << "PUT PERMUTATION: ";
        for (int k = 0; k < n; k++)
            std::cout << permutation[k] << " ";
        std::cout << std::endl;

        std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
                cds = getAllIsomorphicPermutations(m, pm, n, true);

        std::cout << "FOUND: " << std::endl;
        for (CombinatoricsData cd: cds) {
            for (int k = 0; k < cd.getSize(); k++)
                std::cout << cd.getData()[k] << " ";
            std::cout << std::endl;
        }


        assert(cds.find(CombinatoricsData(permutation, n)) != cds.end());

        for (CombinatoricsData cd: cds) {
            int **lmp = makePermute(m, n, cd.getData());
            assert(areEqual(lmp, pm, n));
        }
    }
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
    test1();
    std::cout << "TEST 2:" << std::endl;
    test2();
}