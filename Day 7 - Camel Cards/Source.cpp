#include <iostream>

char** initialiseMatrix(unsigned int rows, unsigned int cols);
void readInput(char** matrix, unsigned int rows, unsigned int cols);
void printOutput(char** matrix, unsigned int rows, unsigned int cols);
void deleteMatrix(char** matrix, unsigned int rows);

bool isHandFiveOfAKind(char* hand);
bool isHandFourOfAKind(char* hand);
bool isHandFullHouse(char* hand);
bool isHandThreeOfAKind(char* hand);
bool isHandTwoPair(char* hand);
bool isHandOnePair(char* hand);
bool isHandHighCard(char* hand);

int* rankHands(char** matrix, unsigned int rows, unsigned int cols);

char** initialiseMatrix(unsigned int rows, unsigned int cols) {
    char** matrix = new char* [rows];

    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new char[cols];
    }

    return matrix;
}

void readInput(char** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        std::cout << "Hand " << i + 1 << ": ";
        for (size_t j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
            if (!std::cin) {
                throw std::runtime_error("Invalid input!");
            }
        }
    }
}

void printOutput(char** matrix, unsigned int rows, unsigned int cols) {
    for (size_t i = 0; i < rows; ++i) {
        std::cout << "Hand " << i + 1 << ": ";
        for (size_t j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void deleteMatrix(char** matrix, unsigned int rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

bool isHandFiveOfAKind(char* hand) {
    for (size_t i = 1; i < 5; ++i) {
        if (hand[i] != hand[i - 1]) {
            return false;
        }
    }
    return true;
}

bool isHandFourOfAKind(char* hand) {
    for (size_t i = 1; i < 4; ++i) {
        if (hand[i] != hand[i - 1]) {
            return false;
        }
    }
    return hand[1] == hand[3] || hand[2] == hand[4];
}

bool isHandFullHouse(char* hand) {
    for (size_t i = 1; i < 4; ++i) {
        if (hand[i] != hand[i - 1]) {
            return false;
        }
    }
    return (hand[0] == hand[2] && hand[3] == hand[4]) || (hand[0] == hand[1] && hand[2] == hand[4]);
}

bool isHandThreeOfAKind(char* hand) {
    for (size_t i = 1; i < 3; ++i) {
        if (hand[i] != hand[i - 1]) {
            return false;
        }
    }
    return hand[2] != hand[3] && hand[3] != hand[4];
}

bool isHandTwoPair(char* hand) {
    return (hand[0] == hand[1] && hand[2] == hand[3]) || (hand[0] == hand[1] && hand[3] == hand[4]) || (hand[1] == hand[2] && hand[3] == hand[4]);
}

bool isHandOnePair(char* hand) {
    for (size_t i = 1; i < 4; ++i) {
        if (hand[i] == hand[i - 1]) {
            return true;
        }
    }
    return false;
}

bool isHandHighCard(char* hand) {
    for (size_t i = 1; i < 5; ++i) {
        if (hand[i] == hand[i - 1]) {
            return false;
        }
    }
    return true;
}

int getCardValue(char card) {
    if (card == 'A') return 14;
    if (card == 'K') return 13;
    if (card == 'Q') return 12;
    if (card == 'J') return 11;
    if (card == 'T') return 10;
    return card - '0';
}

int compareHands(char* hand1, char* hand2) {
    for (size_t i = 0; i < 5; ++i) {
        int value1 = getCardValue(hand1[i]);
        int value2 = getCardValue(hand2[i]);
        if (value1 != value2) {
            return value2 - value1;
        }
    }
    return 0;
}

int* rankHands(char** matrix, unsigned int rows, unsigned int cols) {
    int* arrayOfRanks = new int[rows];

    for (size_t i = 0; i < rows; ++i) {
        char* currentHand = matrix[i];

        if (isHandFiveOfAKind(currentHand)) {
            arrayOfRanks[i] = 1;
        }
        else if (isHandFourOfAKind(currentHand)) {
            arrayOfRanks[i] = 2;
        }
        else if (isHandFullHouse(currentHand)) {
            arrayOfRanks[i] = 3;
        }
        else if (isHandThreeOfAKind(currentHand)) {
            arrayOfRanks[i] = 4;
        }
        else if (isHandTwoPair(currentHand)) {
            arrayOfRanks[i] = 5;
        }
        else if (isHandOnePair(currentHand)) {
            arrayOfRanks[i] = 6;
        }
        else if (isHandHighCard(currentHand)) {
            arrayOfRanks[i] = 7;
        }
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = i + 1; j < rows; ++j) {
            if (arrayOfRanks[j] < arrayOfRanks[i] || (arrayOfRanks[j] == arrayOfRanks[i] && compareHands(matrix[j], matrix[i]) < 0)) {
                int tempRank = arrayOfRanks[i];
                arrayOfRanks[i] = arrayOfRanks[j];
                arrayOfRanks[j] = tempRank;

                char* tempHand = matrix[i];
                matrix[i] = matrix[j];
                matrix[j] = tempHand;
            }
        }
    }

    return arrayOfRanks;
}

int main() {
    unsigned int rows;
    unsigned int cols = 5;

    std::cout << "Enter the number of your hands: ";
    std::cin >> rows;
    if (!std::cin || rows < 0) {
        throw std::runtime_error("Invalid input!");
    }

    char** hands = initialiseMatrix(rows, cols);
    std::cout << "Enter your hands: " << std::endl;
    readInput(hands, rows, cols);

    int* ranks = rankHands(hands, rows, cols);

    std::cout << "Ranks of hands:" << std::endl;
    for (size_t i = 0; i < rows; ++i) {
        std::cout << "Hand " << i + 1 << ": " << ranks[i] << std::endl;
    }

    int totalWinnings = 0;
    for (size_t i = 0; i < rows; ++i) {
        totalWinnings += ranks[i] * (i + 1);
    }

    std::cout << "Total winnings: " << totalWinnings << std::endl;

    deleteMatrix(hands, rows);
    delete[] ranks;

    return 0;
}
