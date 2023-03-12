#include "misc/PatternBuilder.h"

/**
 * Конструктор
 *
 * @param data матрица-результат
 * @param sz   размер стороны матрицы
 */
PatternBuilder::PatternBuilder(int **data, int sz) {
    // заполняем массив флагов значениями `false`
    this->isModified = new bool *[sz];
    for (int i = 0; i < sz; i++) {
        this->isModified[i] = new bool[sz];
        for (int j = 0; j < sz; j++)
            this->isModified[i][j] = false;
    }

    this->data = data;
}

/**
 * Добавить паттерн
 *
 * @param pattern           паттерн
 * @param size              размер стороны паттерна
 * @param combinatoricsData комбинация точек результирующей матрицы в которые нужно добавить паттерн
 * @return флаг, получилось ли добавить
 */
bool PatternBuilder::putPattern(int **pattern, int size, CombinatoricsData combinatoricsData) {
    if (size != combinatoricsData.getSize())
        throw std::invalid_argument(
                "PatternBuilder::putPattern() pattern size: " + std::to_string(size) +
                " not equal to combination size" +
                std::to_string(combinatoricsData.getSize())
        );

    // перебираем пары элементов комбинаций
    for (int i = 0; i < combinatoricsData.getSize(); i++)
        for (int j = 0; j < combinatoricsData.getSize(); j++) {
            // получаем две координаты по соответствующим элементам из перебираемой пары
            int posX = combinatoricsData.getData()[i];
            int posY = combinatoricsData.getData()[j];
            // если элемент в матрице уже занят другим паттерном и при
            // этом значение в матрице не совпадает с новым
            if (isModified[posX][posY] && pattern[i][j] != data[posX][posY])
                // возвращаем флаг, что не удалось добавить паттерн
                return false;
        }

    // перебираем пары элементов комбинаций
    for (int i = 0; i < combinatoricsData.getSize(); i++)
        for (int j = 0; j < combinatoricsData.getSize(); j++) {
            // получаем две координаты по соответствующим элементам из перебираемой пары
            int posX = combinatoricsData.getData()[i];
            int posY = combinatoricsData.getData()[j];
            // заполняем соответствующий элемент матрицы
            data[posX][posY] = pattern[i][j];
            // выставляем флаг, что э
            isModified[posX][posY] = true;
        }
    // возвращаем флаг, что удалось добавить паттерн
    return true;
}

/**
 * Получить матрицу связности
 */
int **PatternBuilder::getData() {
    return this->data;
}
