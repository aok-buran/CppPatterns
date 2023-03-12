#include "fastPatternResolver.h"

/**
 * Проверить совпадение самого правого столбца
 * и самой нижней строки подматрицы дата-графа,
 * полученной по соответствующей комбинации
 * (проверяются только новые элементы,
 * они находятся в самом нижнем ряду и в самой правой колонке)
 *
 * @param source      дата-граф
 * @param pattern     паттерн
 * @param combination комбинация
 * @param cnt         кол-во элементов в комбинации
 * @param hardCheck   флаг, нужна ли жёсткая проверка
 * @return флаг, совпадают ли матрицы по углу
 */
bool checkMatrixEdge(
        int **source, int **pattern, const int *combination, int cnt, bool hardCheck
) {
    // перебираем элементы самого нижнего ряда матрицы
    // и самой правой колонки
    for (int i = 0; i < cnt; i++) {
        // если жёсткая проверка
        if (hardCheck) {
            // если элемент из паттерна в правом столбце не совпадает с соответствующим
            // элементом из дата-графа
            if (pattern[i][cnt - 1] != source[combination[i]][combination[cnt - 1]])
                // возвращаем флаг, что матрицы не равны по уголку
                return false;
            // если элемент из паттерна в нижней строке не совпадает с соответствующим
            // элементом из дата-графа
            if (pattern[cnt - 1][i] != source[combination[cnt - 1]][combination[i]])
                // возвращаем флаг, что матрицы не равны по уголку
                return false;
        } else { // если нежёсткая проверка
            // если элемент из паттерна в правом столбце ненулевой и не совпадает с соответствующим
            // элементом из дата-графа
            if (pattern[i][cnt - 1] != 0 && pattern[i][cnt - 1] != source[combination[i]][combination[cnt - 1]])
                // возвращаем флаг, что матрицы не равны по уголку
                return false;
            // если элемент из паттерна в нижней строке ненулевой и не совпадает с соответствующим
            // элементом из дата-графа
            if (pattern[cnt - 1][i] != 0 && pattern[cnt - 1][i] != source[combination[cnt - 1]][combination[i]])
                // возвращаем флаг, что матрицы не равны по уголку
                return false;
        }
    }

    // если не встречено неравных элементов, то возвращаем флаг, что матрицы равны по уголку
    return true;
}


/**
 * Шаг поиска паттерна
 *
 * @param consumer      обработчик найденной комбинации
 * @param used          массив флагов, использовалась ли уже i-я точка
 * @param source        дата-граф
 * @param sourceSize    размер стороны дата-графа
 * @param pattern       искомый паттерн
 * @param patternSize   размер стороны искомого паттерна
 * @param sourcePowers  степени вершин источника
 * @param patternPowers степени вершин паттерна
 * @param cnt           кол-во обработанных элементов
 * @param combination   массив комбинации
 * @param hardCheck     флаг, нужна ли жёсткая проверка
 * @param consumer      лямбда выражение (int *c)->{}
 */
template<typename F>
void fastFindPatternStep(
        bool *used, int **source, int sourceSize, int **pattern,
        int patternSize,
        int *sourcePowers, int *patternPowers, int cnt, int *combination,
        bool hardCheck, const F &consumer
) {
    // если уже выбрана хотя бы одна точка для комбинации и при этом
    // матрица, составленная из дата-графа по этой комбинации
    // не совпадает с соответствующей подматрицей паттерна
    // (нам нужно проверить только новые элементы,
    // они находятся в самом нижнем ряду и в самой правой колонке)
    if (cnt > 0 && !checkMatrixEdge(source, pattern, combination, cnt, hardCheck))
        return;

    // если получено нужное кол-во элементов комбинации
    if (cnt == patternSize)
        // обрабатываем её
        consumer(combination);
    else
        // в противном случае перебираем все вершины графа
        for (int i = 0; i < sourceSize; i++) {
            // если i-я точка уже использована или её степень меньше степени
            // следующей точки в паттерне
            if (used[i] || (hardCheck && sourcePowers[i] < patternPowers[cnt]))
                continue;

            // говорим, что i-я точка использована
            used[i] = true;
            // добавляем индекс точки в комбинацию
            combination[cnt] = i;

            // вызываем следующий шаг рекурсии
            fastFindPatternStep(
                    used, source, sourceSize, pattern, patternSize, sourcePowers,
                    patternPowers, cnt + 1, combination, hardCheck, consumer
            );

            // возвращаем значение флага
            used[i] = false;
        }
}


/**
 * Быстрый поиск изоморфных подграфов
 *
 * @param source        дата-граф
 * @param sourceSize    размер стороны дата-графа
 * @param pattern       искомый паттерн
 * @param patternSize   размер стороны паттерна
 * @param hardCheck     флаг, нужна ли жёсткая проверка; если `hardCheck` равен `false`, то нулевому элементу паттерна
 *                      может соответствовать произвольное значение в переставленной подматрице, а если
 *                      `true`, то все элементы паттерна и переставленной подматрицы должны
 *                      совпадать с точностью до перестановки.
 * @return список таких комбинаций точек из источника, чтобы при составлении
 * соответствующих переставленных подматриц, подграфы, построенные по ним,
 * были изоморфны заданному паттерну
 */
std::vector<CombinatoricsData>
fastGetAllPatterns(int **source, int sourceSize, int **pattern, int patternSize, bool hardCheck) {
    // множество найденных паттернов
    std::vector<CombinatoricsData> res;
    // флаги, использована ли уже та или иная точка
    bool *used = new bool[sourceSize];
    for (int i = 0; i < sourceSize; i++)
        used[i] = false;
    // текущая комбинация
    int *combination = new int[patternSize];
    // степени вершин в дата-графе
    int *sourcePowers = getPowers(source, sourceSize);
    // степени вершин в паттерне
    int *patternPowers = getPowers(pattern, patternSize);

    // запускаем рекурсию
    fastFindPatternStep(
            used, source, sourceSize, pattern, patternSize,
            sourcePowers, patternPowers, 0, combination, hardCheck, [&res, &patternSize](int *c) {
                res.emplace_back(CombinatoricsData(c, patternSize));
            }
    );

    // возвращаем множество найденных паттернов
    return res;
}

