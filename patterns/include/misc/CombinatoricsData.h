#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

/**
 * Класс данных для работы с комбинаторикой;
 * Хранит последовательность неотрицательных чисел в массиве, также
 * переопределён оператор проверки на равенство и
 * добавлена структура HashFunction для хранения в хэш-множестве
 */
class CombinatoricsData {
    /**
     * Элементы последовательности
     */
    int *data;
    /**
     * Размер последовательности
     */
    int sz;
public:
    /**
     * Конструктор
     *
     * @param data элементы комбинации
     * @param sz   размер последовательности
     */
    CombinatoricsData(const int *data, int sz);

    /**
     * Получить элементы последовательности
     * @return элементы последовательности
     */
    int *getData();

    /**
     * Получить размер последовательности
     * @return размер последовательности
     */
    int getSize() const;

    /**
     * Хэш-функция для хранения в хэш-множестве
     */
    struct HashFunction {
        /**
         * Переопределение оператора ()
         * @param cd - последовательность чисел
         * @return хэш последовательности
         */
        std::size_t operator()(const CombinatoricsData &cd) const {
            std::size_t res = 1;
            for (int i = 0; i < cd.sz; i++)
                res = 31 * res + cd.data[i];

            return res;
        }
    };

    /**
     * Переопределение оператора проверки на равенство
     * @param cd1 первая последовательность
     * @param cd2 вторая последовательность
     * @return флаг, равны ли последовательности
     */
    friend bool operator==(const CombinatoricsData &cd1, const CombinatoricsData &cd2) {
        // если у последовательностей разный размер
        if (cd1.getSize() != cd2.getSize())
            // возвращаем флаг, что они не равны
            return false;

        // сравниваем последовательности поэлементно
        for (int i = 0; i < cd1.getSize(); i++)
            // если два соответствующих элемента не равны
            if (cd1.data[i] != cd2.data[i])
                // возвращаем флаг, что не равны и исходные последовательности
                return false;

        // если мы дошли до конца, значит ве элементы равны
        // возвращаем флаг, что последовательности совпадают
        return true;
    }
};

