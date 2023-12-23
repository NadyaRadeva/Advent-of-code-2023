#include <iostream>

char** initialiseMatrix(unsigned int rows, unsigned int cols);
void readInput(char** matrix, unsigned int rows, unsigned int cols);
void printOutput(char** matrix, unsigned int rows, unsigned int cols);
void deleteMatrix(char** matrix, unsigned int rows, unsigned int cols);

unsigned int findStepsToEnd(char** nodes, unsigned int numNodes, char* instr, unsigned int instrLen);

char** initialiseMatrix(unsigned int rows, unsigned int cols) {
    char** matrix = new char* [rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new char[cols];
    }

    return matrix;
}

void readInput(char** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        std::cout << "Node[" << i + 1 << "]: ";
        for (size_t j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
            if (!std::cin) {
                throw std::runtime_error("Invalid input!");
                break;
            }
        }
    }
}

void printOutput(char** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        std::cout << "Node[" << i + 1 << "]: ";
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

unsigned int findStepsToEnd(char** nodes, unsigned int numNodes, char* instr, unsigned int instrLen) {
    unsigned int currentIndex = 0;
    unsigned int steps = 0;

    for (size_t i = 0; i < instrLen; i += 2) {
        while (nodes[currentIndex][0] != 'Z' && nodes[currentIndex][1] != 'Z' && nodes[currentIndex][2] != 'Z') {
            if (instr[i] == 'L') {
                currentIndex = (currentIndex + numNodes - 1) % numNodes;
            }
            else {
                currentIndex = (currentIndex + 1) % numNodes;
            }
            steps++;
        }
    }

    return steps;
}

int main() {
    std::cout << "Enter the length of your instructions: ";
    unsigned int instrLen;
    std::cin >> instrLen;
    if (!std::cin || instrLen <= 0) {
        throw std::runtime_error("Invalid input!");
        return 1;
    }

    std::cout << "Enter your instructions: ";
    char* instructions = new char[instrLen];
    for (size_t i = 0; i < instrLen; ++i) {
        std::cin >> instructions[i];
        if (!std::cin || (instructions[i] != 'L' && instructions[i] != 'R')) {
            throw std::runtime_error("Invalid input!");
            return 1;
        }
    }

    std::cout << "Enter the number of your nodes: ";
    unsigned int numOfNodes;
    std::cin >> numOfNodes;
    if (!std::cin || numOfNodes <= 0) {
        throw std::runtime_error("Invalid input!");
        return 1;
    }

    char** nodes = initialiseMatrix(numOfNodes, 8);
    std::cout << "Enter your nodes: " << std::endl;
    readInput(nodes, numOfNodes, 6);
    std::cout << "Your network: " << std::endl;
    std::cout << "Instructions: ";
    for (size_t i = 0; i < instrLen; ++i) {
        std::cout << instructions[i];
    }
    std::cout << std::endl;
    std::cout << "Nodes: " << std::endl;
    printOutput(nodes, numOfNodes, 6);

    std::cout << "The number of steps you need to make to reach the end is: " << findStepsToEnd(nodes, numOfNodes, instructions, instrLen) << std::endl;

    deleteMatrix(nodes, numOfNodes, 6);
    delete[] instructions;

    return 0;
}
