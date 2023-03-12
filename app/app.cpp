#include <vector>
#include "misc/CombinatoricsData.h"
#include "fastPatternResolver.h"

int main() {
    // паттерн
    int patternMatrix[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    int **pattern = new int *[3];
    for (int i = 0; i < 3; i++) {
        pattern[i] = new int[3];
        for (int j = 0; j < 3; j++)
            pattern[i][j] = patternMatrix[i][j];
    }

    // матрица связности дата-графа
    int sourceMatrix[7][7]{
            {1, 3, 2, 2, 3, 4, 6},
            {7, 9, 1, 8, 0, 3, 3},
            {4, 0, 5, 4, 6, 6, 0},
            {4, 6, 4, 5, 5, 1, 1},
            {7, 2, 8, 3, 9, 7, 8},
            {5, 1, 0, 6, 3, 1, 2},
            {3, 6, 1, 0, 6, 4, 5}
    };
    int **source = new int *[7];
    for (int i = 0; i < 7; i++) {
        source[i] = new int[7];
        for (int j = 0; j < 7; j++)
            source[i][j] = sourceMatrix[i][j];
    }


    // получаем список найденных комбинаций
    std::vector<CombinatoricsData> fastPatterns = fastGetAllPatterns(source, 7, pattern, 3, true);
    // для каждой комбинации выводим её элементы
    for (CombinatoricsData cd: fastPatterns) {
        for (int i = 0; i < 3; i++)
            std::cout << cd.getData()[i] << " ";
        std::cout << std::endl;
    }

    return 0;
}