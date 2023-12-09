#include <iostream>

char** createText(unsigned int lines, unsigned int lettersOnALine);
void readInput(char** text, unsigned int lines, unsigned int lettersOnALine);
void printOutput(char** text, unsigned int lines, unsigned int lettersOnALine);
void deleteText(char** text, unsigned int lines);
int turnNumberToTwoDig(int number1, int number2);
int findCalibrationValue(char** text, unsigned int lines, unsigned int lettersOnALine);

char** createText(unsigned int lines, unsigned int lettersOnALine) {
    char** text = new char* [lines];

    for (size_t i = 0; i < lines; ++i) {
        text[i] = new char[lettersOnALine];
    }

    return text;
}

void readInput(char** text, unsigned int lines, unsigned int lettersOnALine) {
    for (size_t i = 0; i < lines; ++i) {
        std::cout << "Enter text for Line[" << i + 1 << "]: ";
        for (size_t j = 0; j < lettersOnALine; ++j) {
            std::cin >> text[i][j];
        }
    }
}

void printOutput(char** text, unsigned int lines, unsigned int lettersOnALine) {
    for (size_t i = 0; i < lines; ++i) {
        std::cout << "Line[" << i + 1 << "]: ";
        for (size_t j = 0; j < lettersOnALine; ++j) {
            std::cout << text[i][j];
        }
        std::cout << std::endl;
    }
}

void deleteText(char** text, unsigned int lines) {
    for (size_t i = 0; i < lines; ++i) {
        delete[] text[i];
    }

    delete[] text;
}

int turnNumberToTwoDig(int number1, int number2) {
    int twoDigNum = (number1 - '0') * 10 + (number2 - '0');
    return twoDigNum;
}

int findCalibrationValue(char** text, unsigned int lines, unsigned int lettersOnALine) {
    int sum = 0;

    for (size_t i = 0; i < lines; ++i) {
        char firstDigit = '\0';
        char lastDigit = '\0';

        for (size_t j = 0; j < lettersOnALine; ++j) {
            if (text[i][j] >= '0' && text[i][j] <= '9') {
                if (firstDigit == '\0') {
                    firstDigit = text[i][j];
                }
                lastDigit = text[i][j];
            }
        }

        if (firstDigit != '\0' && lastDigit != '\0') {
            int twoDigNum = turnNumberToTwoDig(firstDigit, lastDigit);
            sum += twoDigNum;
        }
    }

    return sum;
}

int main() {
    unsigned int lines;
    unsigned int lettersOnALine;

    std::cout << "Enter the number of lines of your document: ";
    std::cin >> lines;
    if (!std::cin || lines <= 0) {
        throw std::runtime_error("Invalid value!");
    }

    std::cout << "Enter the maximum number of letters on every line of your document: ";
    std::cin >> lettersOnALine;
    if (!std::cin || lettersOnALine <= 0) {
        throw std::runtime_error("Invalid value!");
    }

    char** text = createText(lines, lettersOnALine);
    std::cout << "Enter your text:" << std::endl;
    readInput(text, lines, lettersOnALine);
    std::cout << "Your text:" << std::endl;
    printOutput(text, lines, lettersOnALine);

    std::cout << "The calibration value of your text is: " << findCalibrationValue(text, lines, lettersOnALine) << std::endl;

    deleteText(text, lines);

    return 0;
}
