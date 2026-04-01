#include <iostream>
#include <vector>
#pragma once

class Grid {
    public:
        Grid(int vectors);
        ~Grid();

        int getNumVectors() const {return vectors;}

        // creates 2d gird of PerlinVectors
        std::vector<std::vector<std::vector<std::vector<double>>>> cells;

        std::vector<double> getCell(int x, int y, int z) const {
            return cells[x][y][z];
        }

        friend std::ostream& operator<<(std::ostream& os, const Grid& grid);

    private:
        int vectors;
        void generateGrid();
};