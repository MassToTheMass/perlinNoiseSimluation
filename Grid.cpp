#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include "Grid.hpp"

Grid::Grid(int vectors) : vectors(vectors) {
    std::srand(static_cast<unsigned int>(std::time(0))); // seed random number generator
    Grid::generateGrid();
}
Grid::~Grid() {}

void Grid::generateGrid() {
    cells.resize(vectors);
    for (int i = 0; i < vectors; ++i) {
        cells[i].resize(vectors);
        for (int j = 0; j < vectors; ++j) {
            cells[i][j].resize(vectors);
            for (int k = 0; k < vectors; ++k) {

                double old_x = std::rand();
                double old_y = std::rand();
                double old_z = std::rand();

                // normalize
                double x = old_x / sqrt(old_x * old_x + old_y * old_y + old_z * old_z);
                double y = old_y / sqrt(old_x * old_x + old_y * old_y + old_z * old_z);
                double z = old_z / sqrt(old_x * old_x + old_y * old_y + old_z * old_z);

                // randomize direction
                int random_sign = (std::rand() % 2 == 0) ? 1 : -1;
                x *= random_sign;
                random_sign = (std::rand() % 2 == 0) ? 1 : -1;
                y *= random_sign;
                random_sign = (std::rand() % 2 == 0) ? 1 : -1;
                z *= random_sign;

                cells[i][j][k] = std::vector<double>{x, y, z};
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Grid& grid) {
    for (const auto& row : grid.cells) {
        for (const auto& cell : row) {
            for (const auto& depth : cell) {
                for (const auto& val : depth) {
                    os << val << " ";
                }
            }
            os << " | ";
        }
        os << std::endl;
    }
    return os;
}