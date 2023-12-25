//this programme was not written by me

#include<iostream>

char** initialiseMatrix(unsigned int rows, unsigned int cols);
void readInput(char** matrix, unsigned int rows, unsigned int cols);
void printOutput(char** matrix, unsigned int rows, unsigned int cols);
void deleteMatrix(char** matrix, unsigned int rows, unsigned int cols);



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
			if (!std::cin || matrix[i][j] != '|' || matrix[i][j] != '-' || matrix[i][j] != 'J' || matrix[i][j] != 'L' || matrix[i][j] != '7' || matrix[i][j] != 'F' || matrix[i][j] != '.' || matrix[i][j] != 'S') {
				throw std::runtime_error("Invalid input!");
				break;
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

void dfs(char** sketch, int** distances, unsigned int rows, unsigned int cols, int x, int y, int distance) {
    bool (*is_valid)(int, int) = [&](int i, int j) {
        return i >= 0 && i < rows && j >= 0 && j < cols;
        };

    if (is_valid(x, y) && sketch[x][y] != '.' && distances[x][y] == -1) {
        distances[x][y] = distance;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx * dy == 0 && !(dx == 0 && dy == 0)) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (is_valid(nx, ny)) {
                        dfs(sketch, distances, rows, cols, nx, ny, distance + 1);
                    }
                }
            }
        }
    }
}

void findLoopDistances(char** sketch, unsigned int rows, unsigned int cols, int** distances) {
    int start_x = -1, start_y = -1;

    bool (*is_valid)(int, int) = [&](int i, int j) {
        return i >= 0 && i < rows && j >= 0 && j < cols;
        };

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            if (sketch[i][j] == 'S') {
                start_x = i;
                start_y = j;
                break;
            }
        }
        if (start_x != -1) break;
    }

    if (start_x == -1) {
        std::cerr << "Error: Starting point 'S' not found in the matrix." << std::endl;
        exit(1);
    }

    dfs(sketch, distances, rows, cols, start_x, start_y, 0);
}

int findFarthestPointDistance(int** distances, unsigned int rows, unsigned int cols) {
    int farthest_distance = 0;

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            if (distances[i][j] > farthest_distance) {
                farthest_distance = distances[i][j];
            }
        }
    }

    return farthest_distance;
}
