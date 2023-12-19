#include <iostream>

int main() {
    unsigned int numOfDisciplines;
    std::cout << "Enter the number of disciplines in the race: ";
    std::cin >> numOfDisciplines;
    if (!std::cin || numOfDisciplines < 1) {
        throw std::runtime_error("Invalid input!");
    }

    int* recordDistances = new int[numOfDisciplines];
    int* times = new int[numOfDisciplines];

    std::cout << "Enter durations of each race: " << std::endl;
    for (size_t i = 0; i < numOfDisciplines; ++i) {
        std::cout << "Race " << i + 1 << ": ";
        std::cin >> times[i];
    }

    std::cout << std::endl;

    std::cout << "Enter the record distances for each race: " << std::endl;
    for (size_t i = 0; i < numOfDisciplines; ++i) {
        std::cout << "Race " << i + 1 << ": ";
        std::cin >> recordDistances[i];
    }

    int startingSpeed = 1;
    unsigned int multiplyWaysToWin = 1;

    for (size_t i = 0; i < numOfDisciplines; ++i) {
        int waysToWinThisRace = 0;

        for (size_t j = 0; j <= times[i]; ++j) {
            unsigned int remainingTime = times[i] - j;
            unsigned int distanceTravelled = (startingSpeed + j) * remainingTime;

            if (distanceTravelled > recordDistances[i]) {
                waysToWinThisRace++;
            }
        }

        multiplyWaysToWin *= waysToWinThisRace;
    }

    std::cout << "Total number of ways to beat the record across all races: " << multiplyWaysToWin << std::endl;

    delete[] times;
    delete[] recordDistances;

    return 0;
}

