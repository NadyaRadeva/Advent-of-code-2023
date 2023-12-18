#include<iostream>

int** createMatrix(unsigned int rows, unsigned int cols);
void readInput(int** matrix, unsigned int rows, unsigned int cols);
void printOutput(int** matrix, unsigned int rows, unsigned int cols);
void deleteMatrix(int** matrix, unsigned int rows, unsigned int cols);

int findLocation(int** map, unsigned int rows, int source);

int** createMatrix(unsigned int rows, unsigned int cols) {
	int** matrix = new int* [rows];

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

void printOutput(int** matrix, unsigned int rows, unsigned int cols) {
	for (size_t i = 0; i < rows; ++i) {
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

int findLocation(int** map, unsigned int rows, int source) {
	for (size_t i = 0; i < rows; ++i) {
		if (source >= map[i][1] && source < map[i][1] + map[i][2]) {
			return map[i][0] + (source - map[i][1]);
		}
	}
	return source;
}


int main() {
	std::cout << "Enter the number of your seeds: ";
	unsigned int seedsNum;
	std::cin >> seedsNum;
	if (!std::cin || seedsNum < 0) {
		throw std::runtime_error("Invalid input!");
	}

	std::cout << "Now, enter the seeds to be planted: ";
	int* seeds = new int[seedsNum];
	for (size_t i = 0; i < seedsNum; ++i) {
		std::cin >> seeds[i];
	}

	std::cout << std::endl;

	std::cout << "Enter the parameters of your seed-to-soil map: ";
	unsigned int stsmRows;
	unsigned int stsmCols;
	std::cin >> stsmRows >> stsmCols;
	if (!std::cin || stsmRows < 0 || stsmCols < 0) {
		throw std::runtime_error("Invalid input!");
	}

	int** seedToSoilMap = createMatrix(stsmRows, stsmCols);
	std::cout << "Enter the values in your seed-to-soil map: " << std::endl;
	readInput(seedToSoilMap, stsmRows, stsmCols);
	
	std::cout << std::endl;

	std::cout << "Enter the parameters of your soil-to-fertilizer map: ";
	unsigned int stfmRows;
	unsigned int stfmCols;
	std::cin >> stfmRows >> stfmCols;
	if (!std::cin || stfmRows < 0 || stfmCols < 0) {
		throw std::runtime_error("Invalid input!");
	}

	int** soilToFertilizerMap = createMatrix(stfmRows, stfmCols);
	std::cout << "Enter the values in your soil-to-fertilizer map: " << std::endl;
	readInput(soilToFertilizerMap, stfmRows, stfmCols);

	std::cout << "Enter the parameters of your fertilizer-to-water map: ";
	unsigned int ftwmRows;
	unsigned int ftwmCols;
	std::cin >> ftwmRows >> ftwmCols;
	if (!std::cin || ftwmRows < 0 || ftwmCols < 0) {
		throw std::runtime_error("Invalid input!");
	}

	int** fertilizerToWaterMap = createMatrix(ftwmRows, ftwmCols);
	std::cout << "Enter the values in your fertilizer-to-water map: " << std::endl;
	readInput(fertilizerToWaterMap, ftwmRows, ftwmCols);

	std::cout << std::endl;

	std::cout << "Enter the parameters of your water-to-light map: ";
	unsigned int wtlmRows;
	unsigned int wtlmCols;
	std::cin >> wtlmRows >> wtlmCols;
	if (!std::cin || wtlmRows < 0 || wtlmCols < 0) {
		throw std::runtime_error("Invalid input!");
	}

	int** waterToLightMap = createMatrix(wtlmRows, wtlmCols);
	std::cout << "Enter the values in your water-to-light map: " << std::endl;
	readInput(waterToLightMap, wtlmRows, wtlmCols);

	std::cout << std::endl;

	std::cout << "Enter the parameters of your light-to-temperature map: ";
	unsigned int lttmRows;
	unsigned int lttmCols;
	std::cin >> lttmRows >> lttmCols;
	if (!std::cin || lttmRows < 0 || lttmCols < 0) {
		throw std::runtime_error("Invalid input!");
	}

	int** lightToTemperatureMap = createMatrix(lttmRows, lttmCols);
	std::cout << "Enter the values in your light-to-temperature map: " << std::endl;
	readInput(lightToTemperatureMap, lttmRows, lttmCols);

	std::cout << std::endl;

	std::cout << "Enter the parameters of your temperature-to-humidity map: ";
	unsigned int tthmRows;
	unsigned int tthmCols;
	std::cin >> tthmRows >> tthmCols;
	if (!std::cin || tthmRows < 0 || tthmCols < 0) {
		throw std::runtime_error("Invalid input!");
	}

	int** temperatureToHumidityMap = createMatrix(tthmRows, tthmCols);
	std::cout << "Enter the values in your temperature-to-humidity map: " << std::endl;
	readInput(temperatureToHumidityMap, tthmRows, tthmCols);

	std::cout << std::endl;

	std::cout << "Enter the parameters of your humidity-to-location map: ";
	unsigned int htlmRows;
	unsigned int htlmCols;
	std::cin >> htlmRows >> htlmCols;
	if (!std::cin || htlmRows < 0 || htlmCols < 0) {
		throw std::runtime_error("Invalid input!");
	}

	int** humidityToLocationMap = createMatrix(htlmRows, htlmCols);
	std::cout << "Enter the values in your humidity-to-location map: " << std::endl;
	readInput(humidityToLocationMap, htlmRows, htlmCols);

	std::cout << std::endl;


	std::cout << "Your almanac: " << std::endl;
	std::cout << "Seeds: ";
	for (size_t i = 0; i < seedsNum; ++i) {
		std::cout << seeds[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Seed-to-soil map: " << std::endl;
	printOutput(seedToSoilMap, stsmRows, stsmRows);

	std::cout << "Soil-to-fertilizer map:" << std::endl;
	printOutput(soilToFertilizerMap, stfmRows, stfmCols);

	std::cout << "Fertilizer-to-water map:" << std::endl;
	printOutput(fertilizerToWaterMap, ftwmRows, ftwmCols);

	std::cout << "Water-to-light map: " << std::endl;
	printOutput(waterToLightMap, wtlmRows, wtlmCols);

	std::cout << "Light-to-temperature map:" << std::endl;
	printOutput(lightToTemperatureMap, lttmRows, lttmCols);

	std::cout << "Temperature-to-humidity map:" << std::endl;
	printOutput(temperatureToHumidityMap, tthmRows, tthmCols);

	std::cout << "Humidity-to-location map:" << std::endl;
	printOutput(humidityToLocationMap, htlmRows, htlmCols);

	int location = humidityToLocationMap[0][1];

	for (size_t i = 0; i < seedsNum; ++i) {
		int seed = seeds[i];

		int soil = findLocation(seedToSoilMap, stsmRows, seed);
		int fertilizer = findLocation(soilToFertilizerMap, stfmRows, soil);
		int water = findLocation(fertilizerToWaterMap, ftwmRows, fertilizer);
		int light = findLocation(waterToLightMap, wtlmRows, water);
		int temperature = findLocation(lightToTemperatureMap, lttmRows, light);
		int humidity = findLocation(temperatureToHumidityMap, tthmRows, temperature);
		location = findLocation(humidityToLocationMap, htlmRows, humidity);

		std::cout << "Locationof seed " << seed << ": " << location << std::endl;
	}

	std::cout << "The min location is: " << location << std::endl;


	delete[] seeds;
	deleteMatrix(seedToSoilMap, stsmRows, stsmCols);
	deleteMatrix(soilToFertilizerMap, stfmRows, stfmCols);
	deleteMatrix(fertilizerToWaterMap, ftwmRows, ftwmCols);
	deleteMatrix(waterToLightMap, wtlmRows, wtlmCols);
	deleteMatrix(lightToTemperatureMap, lttmRows, lttmCols);
	deleteMatrix(temperatureToHumidityMap, tthmRows, tthmCols);
	deleteMatrix(humidityToLocationMap, htlmRows, htlmCols);

	return 0;
}
