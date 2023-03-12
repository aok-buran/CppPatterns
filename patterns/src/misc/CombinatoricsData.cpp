#include "misc/CombinatoricsData.h"

/**
 * Конструктор
 *
 * @param data элементы комбинации
 * @param sz размер последовательности
 */
CombinatoricsData::CombinatoricsData(const int *data, int sz) {
    this->data = new int[sz];
    for (int i = 0; i < sz; i++)
        this->data[i] = data[i];
    this->sz = sz;
}

/**
 * Получить элементы последовательности
 * @return элементы последовательности
 */
int *CombinatoricsData::getData() {
    return this->data;
}

/**
 * Получить размер последовательности
 * @return размер последовательности
 */
int CombinatoricsData::getSize() const {
    return this->sz;
}

