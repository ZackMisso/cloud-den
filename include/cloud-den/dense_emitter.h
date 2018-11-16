#pragma once

template <typename T>
class DensityEmitter
{
public:
    T calculateDensity(T x, T y, T z) const = 0;
    std::vector<T> generateDensityGrid(int w, int h, int d) const = 0;
};
