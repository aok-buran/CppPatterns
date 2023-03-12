#include "misc/combinatorics.h"

/**
 * Получить обратную перестановку
 *
 * @param arr исходная перестановка
 * @param sz размер перестановки
 * @return обратная перестановка
 */
int *getReversePermutation(const int *arr, int sz) {
    int *reverse = new int[sz];
    for (int i = 0; i < sz; i++)
        reverse[arr[i]] = i;
    return reverse;
}

/**
 * Применить перестановку к массиву
 *
 * @param source источник
 * @param sz     размер перестановки
 * @param p      перестановка
 * @return обратная перестановка
 */
int *makePermute(const int *source, int sz, const int *p) {
    int *res = new int[sz];
    for (int i = 0; i < sz; i++)
        res[p[i]] = source[i];
    return res;
}


/**
 * Применить перестановку к матрице
 *
 * @param source источник
 * @param sz     размер перестановки
 * @param p      перестановка
 * @return переставленная матрица
 */
int **makePermute(int **source, int sz, const int *p) {
    int **res = new int *[sz];
    for (int i = 0; i < sz; i++)
        res[i] = new int[sz];

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            res[i][j] = source[p[i]][p[j]];

    return res;
}

/**
 * Получить случайную комбинацию
 *
 * @param n общее количество элементов
 * @param k количество элементов комбинации
 * @return случайная комбинация
 */
CombinatoricsData getRandomCombination(int n, int k) {
    if (k > n)
        throw std::invalid_argument(
                "getRandomCombination() arr size: " + std::to_string(n) + " elems cnt " + std::to_string(k)
        );

    // создаём множество значений случайной комбинации
    std::unordered_set<int> combination;

    // пока не набралось достаточное количество значений в множестве
    while (combination.size() < k)
        // добавляем в него случайное значение от 0 до n
        combination.insert(std::abs(std::rand()) % n);

    // переводим комбинацию из множества в список
    std::vector<int> lst(combination.begin(), combination.end());


    // перемешиваем этот список
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(lst), std::end(lst), rng);

    // массив итоговой комбинации
    int *res = new int[k];
    // заполняем массив, начиная с нулевого индекса
    int pos = 0;
    for (int e: lst)
        res[pos++] = e;

    return {res, k};
}


/**
 * Получить случайную перестановку
 *
 * @param size размер матрицы
 * @return случайная перестановка
 */
int *getRandomPermutation(int size) {
    if (size < 1)
        throw std::invalid_argument(
                "getRandomPermutation() permutation size is not acceptable: " + std::to_string(size)
        );

    // заполняем массив данных заданной длины случайными числами
    int *r = new int[size];
    for (int i = 0; i < size; i++)
        r[i] = std::rand() % 20000 - 10000;

    // заполняем массив заданной длины индексами
    int *rc = new int[size];
    for (int i = 0; i < size; i++)
        rc[i] = i;

    // сортируем совместно два массива по значению из массива данных
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (r[i] < r[j]) {
                int c = r[i];
                r[i] = r[j];
                r[j] = c;

                c = rc[i];
                rc[i] = rc[j];
                rc[j] = c;
            }
    // возвращаем отсортированный по значениям массива данных
    // массив индексов
    return rc;
}

/**
 * Получить случайную перестановку матрицы
 *
 * @param m  исходная матрица
 * @param sz размер перестановки
 * @return переставленная матрица
 */
int **randomPermute(int **m, int sz) {
    // получаем случайную перестановку
    int *p = getRandomPermutation(sz);
    // применяем её к исходной матрице
    return makePermute(m, sz, p);
}

/**
 * Получить подматрицу по массиву используемых индексов
 *
 * @param source источник
 * @param select массив используемых индексов
 * @param selectSize размер массива используемых индексов
 * @return подматрица
 */
int **getSubMatrix(int **source, const int *select, int selectSize) {
    int **res = new int *[selectSize];
    for (int i = 0; i < selectSize; i++)
        res[i] = new int[selectSize];

    for (int i = 0; i < selectSize; i++)
        for (int j = 0; j < selectSize; j++)
            res[i][j] = source[select[i]][select[j]];

    return res;
}


/**
 * Проверка на равенство двух матриц
 *
 * @param a  первая матрица
 * @param b  вторая матрица
 * @param sz размер стороны матрицы
 * @return флаг, равны ли матрицы
 */
bool areEqual(int **a, int **b, int sz) {
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            if (a[i][j] != b[i][j])
                return false;

    return true;
}


/**
 * Получить случайную матрицу
 *
 * @param n           размер стороны матрицы
 * @param minVal      максимальное значение элемента матрицы
 * @param maxVal      максимальное значение элемента матрицы
 * @param nonZeroPart доля ненулевых элементов
 * @return случайная матрица
 */
int **randomMatrix(int n, int minVal, int maxVal, double nonZeroPart) {
    int **r = new int *[n];
    for (int i = 0; i < n; i++)
        r[i] = new int[n];

    // и заполняем её случайными значениями
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if ((double) rand() / RAND_MAX < nonZeroPart)
                r[i][j] = minVal + std::abs(rand()) % (maxVal - minVal);

    return r;
}
