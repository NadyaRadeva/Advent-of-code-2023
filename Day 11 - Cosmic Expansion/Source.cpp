#include <iostream>

char** createYourUniverse(unsigned int rows, unsigned int cols);
void readInput(char** originalUniverse, unsigned int rows, unsigned int cols);
void printOutput(char** originalUniverse, unsigned int rows, unsigned int cols);
void deleteUniverse(char** originalUniverse, unsigned int rows);

char** universeExpansion(char** originalUniverse, unsigned int rows, unsigned int cols);
int idsOfGalaxies(char** originalUniverse, unsigned int rows, unsigned int cols);
int findShortestPath(char** expandedUniverse, int** galaxyPositions, int start, int end, int totalRows, int totalCols);

char** createYourUniverse(unsigned int rows, unsigned int cols) {
    char** universe = new char* [rows];
    for (size_t i = 0; i < rows; ++i) {
        universe[i] = new char[cols];
    }
    return universe;
}

void readInput(char** originalUniverse, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cin >> originalUniverse[i][j];
        }
    }
}

void printOutput(char** originalUniverse, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << originalUniverse[i][j];
        }
        std::cout << std::endl;
    }
}

void deleteUniverse(char** originalUniverse, unsigned int rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] originalUniverse[i];
    }
    delete[] originalUniverse;
}

char** universeExpansion(char** originalUniverse, unsigned int rows, unsigned int cols) {
    char** expandedUniverse = new char* [2 * rows];
    for (unsigned int i = 0; i < 2 * rows; ++i) {
        expandedUniverse[i] = new char[2 * cols];
        for (unsigned int j = 0; j < 2 * cols; ++j) {
            expandedUniverse[i][j] = originalUniverse[i / 2][j / 2];
        }
    }
    return expandedUniverse;
}

int idsOfGalaxies(char** originalUniverse, unsigned int rows, unsigned int cols) {
    char** expandedUniverse = universeExpansion(originalUniverse, rows, cols);

    int** positionsOfGalaxies = new int* [rows * 2 * cols * 2];
    for (int i = 0; i < rows * 2 * cols * 2; ++i) {
        positionsOfGalaxies[i] = new int[3];
    }

    int idOfGalaxy = 1;

    for (size_t i = 0; i < rows * 2; ++i) {
        for (size_t j = 0; j < cols * 2; ++j) {
            if (expandedUniverse[i][j] == '#') {
                positionsOfGalaxies[idOfGalaxy][0] = i;
                positionsOfGalaxies[idOfGalaxy][1] = j;
                positionsOfGalaxies[idOfGalaxy][2] = idOfGalaxy;
                idOfGalaxy++;
            }
        }
    }

    int totalShortestPaths = 0;
    for (int i = 1; i < idOfGalaxy; ++i) {
        for (int j = i + 1; j < idOfGalaxy; ++j) {
            int distance = findShortestPath(expandedUniverse, positionsOfGalaxies, i, j, rows, cols);
            totalShortestPaths += distance;
        }
    }

    for (int i = 0; i < rows * 2 * cols * 2; ++i) {
        delete[] positionsOfGalaxies[i];
    }
    delete[] positionsOfGalaxies;

    for (unsigned int i = 0; i < 2 * rows; ++i) {
        delete[] expandedUniverse[i];
    }
    delete[] expandedUniverse;

    return totalShortestPaths;
}

int findShortestPath(char** expandedUniverse, int** galaxyPositions, int start, int end, int totalRows, int totalCols) {
    int rows = 2 * totalRows;
    int cols = 2 * totalCols;

    int** visited = new int* [2 * totalRows];
    for (size_t i = 0; i < 2 * totalRows; ++i) {
        visited[i] = new int[cols];
    }

    int i = galaxyPositions[start][0], j = galaxyPositions[start][1];
    int distance = 0, steps = 0;

    while (!(i == galaxyPositions[end][0] && j == galaxyPositions[end][1])) {
        if (visited[i][j] == 1) {
            break;
        }

        visited[i][j] = 1;

        int x, y;
        for (int k = 0; k < 4; ++k) {
            if (k == 0) { x = 0; y = 1; }
            else if (k == 1) { x = 1; y = 0; }
            else if (k == 2) { x = 0; y = -1; }
            else { x = -1; y = 0; }

            int ni = i + x;
            int nj = j + y;

            if (0 <= ni && ni < 2 * totalRows && 0 <= nj && nj < cols && expandedUniverse[ni][nj] == '.') {
                i = ni;
                j = nj;
                distance += steps;
                steps++;
                break;
            }
        }
    }

    for (size_t i = 0; i < 2 * totalRows; ++i) {
        delete[] visited[i];
    }
    delete[] visited;

    return distance;
}

int main() {
    std::cout << "Enter the number of rows of galaxies: ";
    unsigned int rows;
    std::cin >> rows;
    if (!std::cin || rows < 0) {
        throw std::runtime_error("Invalid input!");
    }

    std::cout << "Enter the number of cols of galaxies: ";
    unsigned int cols;
    std::cin >> cols;
    if (!std::cin || cols < 0) {
        throw std::runtime_error("Invalid input!");
    }

    char** originalUniverse = createYourUniverse(rows, cols);
    std::cout << "Create the image: " << std::endl;
    readInput(originalUniverse, rows, cols);
    std::cout << "Print your original image: " << std::endl;
    printOutput(originalUniverse, rows, cols);

    int totalShortestPaths = idsOfGalaxies(originalUniverse, rows, cols);
    std::cout << "Total shortest paths: " << totalShortestPaths << std::endl;

    deleteUniverse(originalUniverse, rows);

    return 0;
}
