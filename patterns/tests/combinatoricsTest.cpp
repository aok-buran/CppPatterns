#include <cassert>
#include <ctime>
#include "misc/combinatorics.h"

/**
 * Проверка на поэлементое равенство двух массивов
 * @param arr1 первый
 * @param arr2 второй
 * @param sz размер массивов
 * @return флаг, равны ли массивы поэлементно
 */
bool areEqual(const int *arr1, const int *arr2, int sz) {
    for (int i = 0; i < sz; i++)
        if (arr1[i] != arr2[i])
            return false;
    return true;
}

/**
 * Главный метод
 * @return код возрата
 */
int main() {
    long  ltime = time (nullptr);
    int stime = (unsigned int) ltime/2;
    srand(stime);

    for (int i = 0; i < 100; i++) {
        int sz = std::abs(rand()) % 1000 + 1;
        int *p = getRandomPermutation(sz);
        int *r = getReversePermutation(p, sz);
        int *rr = getReversePermutation(p, sz);
        assert(areEqual(r, rr, sz));
    }
}