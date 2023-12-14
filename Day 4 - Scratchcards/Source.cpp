#include <iostream>

int** initialiseMatrix(unsigned int rows, unsigned int cols);
void readInput(int** matrix, unsigned int rows, unsigned int cols);
void deleteMatrix(int** matrix, unsigned int rows, unsigned int cols);
void createYourScratchcards(int** winningNumbers, unsigned int numOfWinningNumbers, int** yourNumbers, unsigned int numOfYourNumbers, unsigned int numOfScratchcards);

int** initialiseMatrix(unsigned int rows, unsigned int cols) {
    int** matrix = new int * [rows];

    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    return matrix;
}

void readInput(int** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

void deleteMatrix(int** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void createYourScratchcards(int** winningNumbers, unsigned int numOfWinningNumbers, int** yourNumbers, unsigned int numOfYourNumbers, unsigned int numOfScratchcards) {
    for (size_t i = 0; i < numOfScratchcards; ++i) {
        std::cout << "Card " << i + 1 << ": ";

        for (size_t j = 0; j < numOfWinningNumbers; ++j) {
            std::cout << winningNumbers[i][j] << " ";
        }
        std::cout << "| ";
        for (size_t l = 0; l < numOfYourNumbers; ++l) {
            std::cout << yourNumbers[i][l] << " ";
        }
        std::cout << std::endl;
    }
}

int findYourPoints(int** winningNumbers, unsigned int numOfWinningNumbers, int** yourNumbers, unsigned int numOfYourNumbers, unsigned int numOfScratchcards) {
    int sumOfPoints = 0;

    for (size_t i = 0; i < numOfScratchcards; ++i) {
        int pointsPerCard = 0;

        for (size_t j = 0; j < numOfWinningNumbers; ++j) {
            int multiplier = 1;
            for (size_t l = 0; l < numOfYourNumbers; ++l) {
                if (winningNumbers[j][l] == yourNumbers[j][l]) {
                    pointsPerCard += multiplier;
                    multiplier *= 2;
                }
            }
        }

        sumOfPoints += pointsPerCard;
    }


    return sumOfPoints;
}

int main() {
    std::cout << "Enter the amount of your scratchcards: ";
    unsigned int numOfScratchcards;
    std::cin >> numOfScratchcards;
    if (!std::cin || numOfScratchcards < 0) {
        throw std::runtime_error("Invalid input!");
    }

    unsigned int numOfWinningNumbers;
    std::cout << "Enter the amount of the winning numbers on your scratcards: ";
    std::cin >> numOfWinningNumbers;
    if (!std::cin || numOfWinningNumbers < 0) {
        throw std::runtime_error("Invalid input!");
    }
    int** winningNumbers = initialiseMatrix(numOfScratchcards, numOfWinningNumbers);
    std::cout << "Enter the winning numbers: " << std::endl;
    readInput(winningNumbers, numOfScratchcards, numOfWinningNumbers);

    unsigned int numOfYourNumbers;
    std::cout << "Enter the amount of your numbers on your scratcards: ";
    std::cin >> numOfYourNumbers;
    if (!std::cin || numOfYourNumbers < 0) {
        throw std::runtime_error("Invalid input!");
    }
    int** yourNumbers = initialiseMatrix(numOfScratchcards, numOfYourNumbers);
    std::cout << "Enter your numbers: " << std::endl;
    readInput(yourNumbers, numOfScratchcards, numOfYourNumbers);

    createYourScratchcards(winningNumbers, numOfWinningNumbers, yourNumbers, numOfYourNumbers, numOfScratchcards);

    std::cout << "The total points of your scratcards are: " << findYourPoints(winningNumbers, numOfWinningNumbers, yourNumbers, numOfYourNumbers, numOfScratchcards) << std::endl;

    deleteMatrix(winningNumbers, numOfScratchcards, numOfWinningNumbers);
    deleteMatrix(yourNumbers, numOfScratchcards, numOfYourNumbers);

    return 0;
}
