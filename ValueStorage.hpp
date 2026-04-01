#include <vector>
#include <iostream>

#pragma once

// Forward declaration
class Grid;

class ValueStorage {
public:
    ValueStorage(int width, int height);
    ~ValueStorage();

    // make getValue const so it can be called on const ValueStorage instances
    double getValue(int x, int y, int z) const;
    void setValue(int x, int y, int z, double value);

    double getInfluenceValue(double pixelX, double pixelY, double pixelZ, std::vector<double> whichCell, int detailD);
    void FillCellInfluenceValues(int cellX, int cellY, int cellZ, const Grid& grid, int detail);
    void FillAllCellsInfluenceValues(const Grid& grid, int detail);

    // this can be const as it does not modify state
    std::vector<double> getDistanceVectors(double u, double v, double w) const;

    friend std::ostream& operator<<(std::ostream& os, const ValueStorage& storage);

private:
    int width;
    int height;
    std::vector<std::vector<std::vector<double>>> values;
};