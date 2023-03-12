#include "patternResolver.h"


/**
 * Проверка переставленной подматрицы на равенство целевой матрице;
 * Этот метод проверяет, что каждому ненулевому элементу образца
 * должен соответствовать ненулевой элемент в переставленной матрице.
 * В случае жёсткой проверки каждому нулевому элементу целевой матрицы должен
 * соответствовать нулевой элемент переставленной матрицы
 *
 * @param p          перестановка
 * @param source     матрица-источник
 * @param target     матрица-цель
 * @param sourceSum  степени вершин у графа-источника
 * @param targetSum  степени вершин у графа-цели
 * @param sz         размер стороны матриц
 * @param hardCheck  флаг, нужна ли жёсткая проверка
 * @return - флаг, является ли одна матрица перестановкой другой
 */
bool arePermutatedEquals(
        const int *p, int **source, int **target, const int *sourceSum, const int *targetSum,
        int sz, bool hardCheck
) {
    // проверяем, что у графов совпадают степени вершин
    for (int i = 0; i < sz; i++)
        // или её степень меньше степени в паттерне
        if (hardCheck && sourceSum[p[i]] < targetSum[i])
            return false;

    // перебираем все вершины
    for (int i = 0; i < sz; i++)
        // снова перебираем все вершины
        for (int j = 0; j < sz; j++) {
            // если проверка жёсткая и элемент из переставленной не совпадает с соответствующим
            // элементом из целевой матрицы
            if (hardCheck && target[i][j] != source[p[i]][p[j]])
                // возвращаем флаг, что матрицы не равны
                return false;
            // если проверка нежёсткая, элемент целевой матрицы не равен 0
            // и при этом элемент из переставленной не совпадает с соответствующим
            // элементом из целевой матрицы
            if (!hardCheck && target[i][j] != 0 && target[i][j] != source[p[i]][p[j]])
                // возвращаем флаг, что матрицы не равны
                return false;
        }
    // если не встречено неравных элементов, то возвращаем флаг, что матрицы равны
    return true;
}


/**
 * Получить массив степеней вершин
 *
 * @param connectivityMatrix матрица связности
 * @param sz                 размер стороны матрицы
 * @return массив степеней вершин
 */
int *getPowers(int **connectivityMatrix, int sz) {
    // создаём массив степеней вершин
    int *powers = new int[sz];

    // перебираем все точки паттерна
    for (int i = 0; i < sz; i++)
        powers[i] = 0;

    // перебираем все точки паттерна
    for (int i = 0; i < sz; i++)
        // внутри снова перебираем все точки
        for (int j = 0; j < sz; j++) {  // заполняем множество
            // если есть ребро от i-ой точки к j-ой
            if (connectivityMatrix[i][j] != 0)
                // увеличиваем степень i-ой вершины
                powers[i]++;
            // если есть ребро от j-ой точки к i-ой
            if (connectivityMatrix[j][i] != 0)
                // увеличиваем степень i-ой вершины
                powers[i]++;
        }
    // возвращаем массив степеней
    return powers;
}


/**
 * Поиск всех перестановок исходной матрицы таких, что переставленная матрица совпадает
 * с целевой. Перестановка - это просто последовательность индексов всех вершин,
 * составляя по которым новую матрицу, мы получим целевую
 *
 * @param source    матрица-источник
 * @param target    целевая матрица
 * @param sz        размер стороны матриц
 * @param hardCheck флаг, нужна ли жёсткая проверка; если `hardCheck` равен `false`, то нулевому элементу целевой
 *                  матрицы может соответствовать произвольное значение в переставленной матрице, а если
 *                  `true`, то все элементы целевой и переставленной матриц должны полностью
 *                  совпадать
 * @return список всех перестановок исходной матрицы таких, что переставленная матрица совпадает
 * с целевой
 */
std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction>
getAllIsomorphicPermutations(int **source, int **target, int sz, bool hardCheck) {
    // степени вершин
    int *sourceSum = getPowers(source, sz);
    int *targetSum = getPowers(target, sz);


    // множество перестановок
    std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction> ps;
    // запускаем генерацию перестановок
    generatePermutations(
            sz,
            [&ps, &sz, &source, &target, &hardCheck, &targetSum, &sourceSum](int *p) {
                // если подграф изоморфен паттерну по рассматриваемой перестановке
                if (arePermutatedEquals(p, source, target, sourceSum, targetSum, sz, hardCheck))
                    // добавляем эту перестановку в множество изоморфных перестановок
                    ps.insert(CombinatoricsData(p, sz));
            });
    return ps;
}

/**
 * Поиск изоморфных подграфов полным перебором
 *
 * @param source       матрица-источник
 * @param sourceSize   размер стороны дата-графа
 * @param pattern      искомый паттерн
 * @param patternSize  размер стороны паттерна
 * @param hardCheck    флаг, нужна ли жёсткая проверка; если `hardCheck` равен `false`, то нулевому элементу паттерна
 *                     может соответствовать произвольное значение в переставленной подматрице, а если
 *                     `true`, то все элементы паттерна и переставленной подматрицы должны
 *                     совпадать с точностью до перестановки.
 * @return список таких комбинаций точек из источника, чтобы при составлении
 * соответствующих переставленных подматриц, подграфы, построенные по ним,
 * были изоморфны заданному паттерну
 */
std::vector<CombinatoricsData>
getAllPatterns(int **source, int sourceSize, int **pattern, int patternSize, bool hardCheck) {
    // множество найденных паттернов
    std::vector<CombinatoricsData> res;

    // перебираем все возрастающие комбинации
    combine(sourceSize, patternSize, [&source, &patternSize, &res, &pattern, &hardCheck](const int *c) {
        // для каждой из них получаем матрицу из дата-графа по этой комбинации
        int **subMatrix = getSubMatrix(source, c, patternSize);

        // находим все перестановки, которые связывают паттерн
        // и составленную подматрицу
        std::unordered_set<CombinatoricsData, CombinatoricsData::HashFunction> ps =
                getAllIsomorphicPermutations(subMatrix, pattern, patternSize, hardCheck);

        // для каждой найденной перестановки
        for (CombinatoricsData p: ps) {
            // в множество добавляем переставленную комбинацию
            // в соответствии с той, которая найдена при поиске изоморфных
            // матриц
            res.emplace_back(
                    makePermute(c, patternSize, getReversePermutation(p.getData(), p.getSize())),
                    p.getSize()
            );
        }
    });

    // возвращаем множество найденных паттернов
    return res;
}



