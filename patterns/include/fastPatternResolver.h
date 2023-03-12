#pragma once


#include "misc/CombinatoricsData.h"
#include "patternResolver.h"
#include <vector>

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
fastGetAllPatterns(int **source, int sourceSize, int **pattern, int patternSize, bool hardCheck);