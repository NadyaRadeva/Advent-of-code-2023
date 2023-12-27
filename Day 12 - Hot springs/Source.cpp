#include<iostream>

char** initialiseMatrix(unsigned int rows, unsigned int cols);
void readInput(char** matrix, unsigned int rows, unsigned int cols);
void printOutput(char** matrix, unsigned int rows, unsigned int cols);
void deleteMatrix(char** matrix, unsigned int rows, unsigned int cols);

int findAllArrangements(int* damagedGroups, int numGroups);
int findGroups(char** matrix, unsigned int rows, unsigned int cols);

char** initialiseMatrix(unsigned int rows, unsigned int cols) {
    char** matrix = new char* [rows];

    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new char[cols];
    }

    return matrix;
}

void readInput(char** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
            if (!std::cin || (matrix[i][j] != '?' && matrix[i][j] != '.' && matrix[i][j] != '#')) {
                throw std::runtime_error("Invalid input!");
            }
        }
    }
}

void printOutput(char** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void deleteMatrix(char** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int findAllArrangements(int* damagedGroups, int numGroups) {
    int totalArrangements = 1;

    for (int i = 0; i < numGroups; ++i) {
        int powerValue = 1;
        for (int j = 0; j < damagedGroups[i] - 1; ++j) {
            powerValue *= 2;
        }
        totalArrangements *= powerValue;
    }

    return totalArrangements;
}

int findGroups(char** matrix, unsigned int rows, unsigned int cols) {
    int* damagedGroups = new int[rows];
    int numGroups = 0;
    int groupSize = 0;

    for (unsigned int i = 0; i < rows; ++i) {
        char* row = matrix[i];

        for (unsigned int j = 0; j < cols; ++j) {
            char ch = row[j];

            if (ch == '#') {
                if (groupSize > 0) {
                    damagedGroups[numGroups++] = groupSize;
                    groupSize = 0;
                }
            }
            else if (ch == '?') {
                groupSize++;
            }
        }

        if (groupSize > 0) {
            damagedGroups[numGroups++] = groupSize;
            groupSize = 0;
        }
    }

    int result = findAllArrangements(damagedGroups, numGroups);

    delete[] damagedGroups;

    return result;
}

int main() {
    unsigned int rows;
    unsigned int cols;

    std::cout << "Enter the rows and columns of your table of springs: ";
    std::cin >> rows >> cols;
    if (!std::cin || rows <= 0 || cols <= 0) {
        throw std::runtime_error("Invalid input!");
        return 1;
    }

    char** matrix = initialiseMatrix(rows, cols);
    std::cout << "Enter input: " << std::endl;
    readInput(matrix, rows, cols);
    std::cout << "Your output: " << std::endl;
    printOutput(matrix, rows, cols);

    int result = findGroups(matrix, rows, cols);
    std::cout << "Result: " << result << std::endl;

    deleteMatrix(matrix, rows, cols);

    return 0;
}
