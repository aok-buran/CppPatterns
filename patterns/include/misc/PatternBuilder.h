#pragma once

#include <stdexcept>
#include "CombinatoricsData.h"

/**
 * Построитель паттернов
 */
class PatternBuilder {
    /**
     * матрица флагов, не занята ли точка каким-то паттерном
     * каждое добавления паттерна соответствующие ячейки заполняются
     * значениями `true`
     */
    bool **isModified;
    /**
     * Текущая матрица связности
     */
    int **data;
    /**
     * Размер стороны матрицы
     */
    int sz;
public:
    /**
     * Конструктор
     *
     * @param data матрица-результат
     * @param sz   размер стороны матрицы
     */
    PatternBuilder(int **data, int sz);

    /**
     * Получить матрицу связности
     */
    int **getData();

    /**
     * Добавить паттерн
     *
     * @param pattern           паттерн
     * @param size              размер стороны паттерна
     * @param combinatoricsData комбинация точек результирующей матрицы в которые нужно добавить паттерн
     * @return флаг, получилось ли добавить
     */
    bool putPattern(int **pattern, int size, CombinatoricsData combinatoricsData);
};

