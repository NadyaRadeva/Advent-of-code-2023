#include<iostream>

int** initialiseMatrix(unsigned int rows, unsigned int cols);
void readInput(int** matrix, unsigned int rows, unsigned int cols);
void printOutput(int** matrix, unsigned int rows, unsigned int cols);
void deleteMatrix(int** matrix, unsigned int rows, unsigned int cols);

int extrapolate(int** oasisReport, unsigned int rows, unsigned int cols);
int findSumOfExtrapolatedValues(int** oasisReport, unsigned int rows, unsigned int cols);

int** initialiseMatrix(unsigned int rows, unsigned int cols) {
	int** matrix = new int* [rows];
	for (size_t i = 0; i < rows; ++i) {
		matrix[i] = new int[cols];
	}
	
	return matrix;
}

void readInput(int** matrix, unsigned int rows, unsigned int cols) {
	for (size_t i = 0; i < rows; ++i) {
		std::cout << "Enter history of value " << i + 1 << ": ";
		for (size_t j = 0; j < cols; ++j) {
			std::cin >> matrix[i][j];
			if (!std::cin) {
				throw std::runtime_error("Invalid input! Rewrite your values!");
				break;
			}
		}
	}
}

void printOutput(int** matrix, unsigned int rows, unsigned int cols) {
	for (size_t i = 0; i < rows; ++i) {
		std::cout << "History of value " << i + 1 << ": ";
		for (size_t j = 0; j < cols; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void deleteMatrix(int** matrix, unsigned int rows, unsigned int cols) {
	for (size_t i = 0; i < rows; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int extrapolate(int* oasisReportRow, unsigned int rows) {
	int* currentRow = new int[rows];

	for (size_t i = 0; i < rows; ++i) {
		currentRow[i] = oasisReportRow[i];
	}

	bool hasZeroAsDiff = false;

	while (hasZeroAsDiff) {
		hasZeroAsDiff = true;
		for (int i = 0; i < rows - 1; ++i) {
			if (oasisReportRow[i] != 0) {
				hasZeroAsDiff = false;
				break;
			}
		}

		if (hasZeroAsDiff) {
			for (int i = 0; i < rows - 1; ++i) {
				currentRow[i] = oasisReportRow[i + 1] - oasisReportRow[i];
			}

			for (int i = 0; i < rows - 1; ++i) {
				oasisReportRow[i] = currentRow[i];
			}
		}
	}

	delete currentRow;

	int nextValue = oasisReportRow[rows - 2] + oasisReportRow[rows - 1];
	return nextValue;
}

int findSumOfExtrapolatedValues(int** oasisReport, unsigned int rows, unsigned int cols) {
	int sum = 0;

	for (size_t i = 0; i < rows; ++i) {
		sum += extrapolate(oasisReport[i], cols);
	}

	return sum;
}

int main() {
	unsigned int rows;
	unsigned int cols;

	std::cout << "Enter the number of your surroundings: ";
	std::cin >> rows;
	if (!std::cin || rows < 0) {
		throw std::runtime_error("Invalid input!");
		return 1;
	}

	std::cout << "Enter your values for each thing: ";
	std::cin >> cols;
	if (!std::cin || cols < 0) {
		throw std::runtime_error("Invalid input!");
		return 1;
	}

	int** oasisReport = initialiseMatrix(rows, cols);
	std::cout << "Input your information: " << std::endl;
	readInput(oasisReport, rows, cols);
	std::cout << std::endl;

	std::cout << "Your output: " << std::endl;
	printOutput(oasisReport, rows, cols);

	std::cout << "The sum of all extrapolated values is: " << findSumOfExtrapolatedValues(oasisReport, rows, cols) << std::endl;

	deleteMatrix(oasisReport, rows, cols);

	return 0;
}
