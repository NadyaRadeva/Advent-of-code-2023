#include <iostream>
#include <cstring>

int HASHAlgorithm(const char* strs);
int* applicationOfHASHAlgorithmForStrings(const char* strs);
int findSumOfResults(const int* values, unsigned int size);

int HASHAlgorithm(const char* strs) {
    int currentValue = 0;

    for (size_t i = 0; i < strlen(strs); ++i) {
        currentValue += (int)strs[i];
        currentValue = (currentValue * 17) % 256;
    }

    return currentValue;
}

int* applicationOfHASHAlgorithmForStrings(const char* strs) {
    int len = strlen(strs);
    int* values = new int[len];

    int ind = 0, indNext = 0, valInd = 0;

    while (ind < len) {
        indNext = ind;
        while (strs[ind] != ',' && strs[indNext] != '\0' && strs[indNext] != ' ') {
            ++indNext;
        }

        values[valInd] = HASHAlgorithm(strs + ind);

        ind = indNext + 1;

        valInd++;
    }

    return values;
}

int findSumOfResults(const int* values, unsigned int size) {
    int sum = 0;

    for (size_t i = 0; i < size; ++i) {
        sum += values[i];
    }

    return sum;
}

int main() {
    unsigned int size;
    std::cout << "Enter the number of characters in your string: ";
    std::cin >> size;
    if (!std::cin || size <= 0) {
        throw std::runtime_error("Invalid input!");
        return -1;
    }

    std::cout << "Enter your string: ";
    char* strs = new char[size + 1];
    std::cin.getline(strs, size + 1);

    std::cout << "Your string is: " << strs << std::endl;

    std::cout << "The hash values of each substring are: ";
    int* values = applicationOfHASHAlgorithmForStrings(strs);
    for (size_t i = 0; i < size; ++i) {
        std::cout << values[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Their sum is: " << findSumOfResults(values, size) << std::endl;

    delete[] strs;
    delete[] values;

    return 0;
}
