#include <cmath>

#include "Grid.hpp"
#include "ValueStorage.hpp"
#include "Computations.cpp"

ValueStorage::ValueStorage(int width, int height) : width(width), height(height) {
    values.resize(height);
    for (int i = 0; i < height; ++i) {
        values[i].resize(width);
        for (int j = 0; j < width; ++j) {
            values[i][j].resize(width);
        }
    }
}
ValueStorage::~ValueStorage() {}

double ValueStorage::getValue(int x, int y, int z) const {
    return values[z][y][x]; // assuming we want all dotproduct values
}

void ValueStorage::setValue(int x, int y, int z, double value) {
    values[z][y][x] = value; // assuming we want to set all dotproduct values
}

double ValueStorage::getInfluenceValue(double pixelX, double pixelY, double pixelZ, std::vector<double> whichCell, int detailD) {
    double u = pixelX / detailD;
    double v = pixelY / detailD;
    double w = pixelZ / detailD;
    return Calculations::getDotProduct(whichCell, getDistanceVectors(u, v, w));
}

void ValueStorage::FillCellInfluenceValues(int cellX, int cellY, int cellZ, const Grid& grid, int detail) {

    // iterate over each pixel in the cell based on detail
    // detail is the number of pixels along one edge of a grid cell
    for (int k = 0; k < detail; ++k) {
        for (int l = 0; l < detail; ++l) {
            for (int m = 0; m < detail; ++m) {
                // calculate relative pixel positions within the cell
                double relativePixelX = static_cast<double>(k);
                double relativePixelY = static_cast<double>(l);
                double relativePixelZ = static_cast<double>(m);

                // interpret detail as a double for division
                double detailD = static_cast<double>(detail);

                // check bounds
                if (cellX + 1 >= grid.getNumVectors() || cellY + 1 >= grid.getNumVectors() || cellZ + 1 >= grid.getNumVectors()) {
                    continue; // skip if out of bounds
                } else {

                    double fade_u = Calculations::fade(relativePixelX / detailD);
                    double fade_v = Calculations::fade(relativePixelY / detailD);
                    double fade_w = Calculations::fade(relativePixelZ / detailD);

                    // get influence values from the four corner vectors
                    double value1 = getInfluenceValue(relativePixelX, relativePixelY, relativePixelZ, grid.getCell(cellX, cellY, cellZ), detailD);
                    double value2 = getInfluenceValue(relativePixelX - detail, relativePixelY, relativePixelZ, grid.getCell(cellX + 1, cellY, cellZ), detailD);
                    double value3 = getInfluenceValue(relativePixelX, relativePixelY - detail, relativePixelZ, grid.getCell(cellX, cellY + 1, cellZ), detailD);
                    double value4 = getInfluenceValue(relativePixelX - detail, relativePixelY - detail, relativePixelZ, grid.getCell(cellX + 1, cellY + 1, cellZ), detailD);

                    double value5 = getInfluenceValue(relativePixelX, relativePixelY, relativePixelZ, grid.getCell(cellX, cellY, cellZ + 1), detailD);
                    double value6 = getInfluenceValue(relativePixelX - detail, relativePixelY, relativePixelZ, grid.getCell(cellX + 1, cellY, cellZ + 1), detailD);
                    double value7 = getInfluenceValue(relativePixelX, relativePixelY - detail, relativePixelZ, grid.getCell(cellX, cellY + 1, cellZ + 1), detailD);
                    double value8 = getInfluenceValue(relativePixelX - detail, relativePixelY - detail, relativePixelZ, grid.getCell(cellX + 1, cellY + 1, cellZ + 1), detailD);

                    double interp1 = Calculations::lerp(value1, value2, fade_u);
                    double interp2 = Calculations::lerp(value3, value4, fade_u);
                    double interp3 = Calculations::lerp(value5, value6, fade_u);
                    double interp4 = Calculations::lerp(value7, value8, fade_u);

                    double interpA = Calculations::lerp(interp1, interp2, fade_v);
                    double interpB = Calculations::lerp(interp3, interp4, fade_v);

                    double noise = Calculations::lerp(interpA, interpB, fade_w);

                    // calculate absolute pixel positions in the ValueStorage
                    int PixelX = cellX * detail + k;
                    int PixelY = cellY * detail + l;
                    int PixelZ = cellZ * detail + m;

                    setValue(PixelX, PixelY, PixelZ, noise);
                }
            }
        }
    }
}

// detail is the number of pixels along one edge of a grid cell
void ValueStorage::FillAllCellsInfluenceValues(const Grid& grid, int detail) {
    // rewritten

    // iterate over each cell in the grid
    for (int i = 0; i < grid.getNumVectors(); ++i) {
        for (int j = 0; j < grid.getNumVectors(); ++j) {
            for (int k = 0; k < detail; ++k) {
                int cellX = i;
                int cellY = j;
                int cellZ = k;

                FillCellInfluenceValues(cellX, cellY, cellZ, grid, detail);
            }
        }
    }
}

std::vector<double> ValueStorage::getDistanceVectors(double u, double v, double w) const {
    std::vector<double> points;
    points.push_back(u);
    points.push_back(v);
    points.push_back(w);
    return points;
}

std::ostream& operator<<(std::ostream& os, const ValueStorage& storage) {
    for (size_t z = 0; z < storage.values.size(); ++z) {
        for (size_t y = 0; y < storage.values[z].size(); ++y) {
            for (size_t x = 0; x < storage.values[z][y].size(); ++x) {
                os << storage.values[z][y][x] << " ";
            }
            os << std::endl;
        }
        os << std::endl;
    }
    return os;
}