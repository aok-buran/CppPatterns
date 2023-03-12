#pragma once

#include <stdexcept>
#include <unordered_set>
#include <random>
#include <algorithm>
#include "CombinatoricsData.h"

/**
 * Шаг перебора комбинаций
 *
 * @param consumer    обработчик для каждой найденной комбинации
 * @param combination текущая комбинация
 * @param min         минимальное значение для перебора
 * @param max         максимальное значение для перебора
 * @param pos         индекс текущего элемента
 * @param consumer    обработчик для каждой найденной комбинации (const int *c)->{}
 */
template<typename F>
void combineStep(int *combination, int sz, int min, int max, int pos, const F &consumer);

/**
 * Запустить перебор комбинаций
 *
 * @param n        общее число элементов
 * @param k        размер комбинации
 * @param consumer обработчик для каждой найденной комбинации (const int *c)->{}
 */
template<typename F>
void combine(int n, int k, const F &consumer) {
    if (k > n)
        throw std::invalid_argument(
                "combine() arr size: " + std::to_string(n) + " elements count " + std::to_string(k)
        );
    // запускаем первый шаг перебора комбинаций
    combineStep(new int[k], k, 0, n - 1, 0, consumer);
}

/**
 * функция-генератор перестановок
 *
 * @param p         текущая перестановка
 * @param pos       положение
 * @param source    матрица-источник
 * @param target    матрица-цель
 * @param sourceSum суммы у источника
 * @param targetSum суммы цели
 * @param hardCheck флаг, нужна ли жёсткая проверка
 * @param consumer  обработчик найденной перестановки лямбда выражение (int *c)->{}
 */

template<typename F>
void generatePermutationsStep(int sz, int *p, int pos, const F &consumer) {
    // Если мы дошли до последнего элемента
    if (pos == sz - 1) {
        consumer(p);
    } else  // иначе
        // Перебираем все оставшиеся элементы
        for (int i = pos; i < sz; i++) {
            // меняем местами текущий элемент и перебираемый
            std::swap(p[i], p[pos]);
            // Вызываем рекурсию для следующего элемента
            generatePermutationsStep(sz, p, pos + 1, consumer);
            // меняем местами обратно
            std::swap(p[i], p[pos]);
        }
}

/**
 * функция-генератор перестановок
 *
 * @param size     количество элементов перестановка
 * @param consumer обработчик найденной перестановки лямбда выражение (int *c)->{}
 */
template<typename F>
void generatePermutations(int size, const F &consumer) {
    // стартовая перестановка - последовательность индексов от 0 до target.length-1
    int startP[size];
    for (int i = 0; i < size; i++)
        startP[i] = i;

    // запускаем генерацию перестановок
    generatePermutationsStep(size, startP, 0, consumer);
}

/**
 * Шаг перебора комбинаций
 *
 * @param consumer    обработчик для каждой найденной комбинации
 * @param combination текущая комбинация
 * @param min         минимальное значение для перебора
 * @param max         максимальное значение для перебора
 * @param pos         индекс текущего элемента
 */
template<typename F>
void combineStep(int *combination, int sz, int min, int max, int pos, const F &consumer) {
    // если индекс текущего элемента равен длине комбинации,
    if (pos == sz)
        // значит, она составлена, передаём её обработчику
        consumer(combination);
        // если минимальное значение перебора не больше максимального
    else if (min <= max) {
        // приравниваем текущий элемент комбинации минимальному значению перебора
        combination[pos] = min;
        // делаем первый вызов рекурсии, увеличивая на 1 и минимальное значение перебора,
        // и индекс текущего элемента комбинации
        combineStep(combination, sz, min + 1, max, pos + 1, consumer);
        // когда закончатся все рекуррентные вызовы предыдущей команды;
        // Она перебрала все комбинации, у которых после элемента с
        // индексом `pos` нет значений, равных `min+1`; теперь
        // запускаем перебор комбинаций, у которых есть `min+1`
        combineStep(combination, sz, min + 1, max, pos, consumer);
    }
}

/**
 * Получить обратную перестановку
 *
 * @param arr исходная перестановка
 * @return обратная перестановка
 */
int *getReversePermutation(const int *arr, int sz);


/**
 * Применить перестановку к массиву
 *
 * @param source источник
 * @param p      перестановка
 * @return обратная перестановка
 */
int *makePermute(const int *source, int sz, const int *p);


/**
 * Применить перестановку к матрице
 *
 * @param source источник
 * @param p      перестановка
 * @return переставленная матрица
 */
int **makePermute(int **source, int sz, const int *p);

/**
 * Получить случайную комбинацию
 *
 * @param n общее количество элементов
 * @param k количество элементов комбинации
 * @return случайная комбинация
 */
CombinatoricsData getRandomCombination(int n, int k);


/**
 * Получить случайную перестановку
 *
 * @param size размер матрицы
 * @return случайная перестановка
 */
int *getRandomPermutation(int size);

/**
 * Получить подматрицу по массиву используемых индексов
 *
 * @param source источник
 * @param select массив используемых индексов
 * @return подматрица
 */
int **getSubMatrix(int **source, const int *select, int selectSize);


/**
 * Проверка на равенство двух матриц
 *
 * @param a первая матрица
 * @param b вторая матрица
 * @return флаг, равны ли матрицы
 */
bool areEqual(int **a, int **b, int sz);

/**
 * Получить случайную матрицу
 *
 * @param min         минимальный размер матрицы
 * @param max         максимальный размер матрицы
 * @param minVal      максимальное значение матрицы по модулю
 * @param maxVal      максимальное значение матрицы по модулю
 * @param nonZeroPart доля ненулевых элементов
 * @return случайная матрица
 */
int **randomMatrix(int n, int minVal, int maxVal, double nonZeroPart);

