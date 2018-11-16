#pragma once

template <typename T>
class DensityEmitter
{
public:
    void calculateDensity(T x,
                          T y,
                          T z,
                          T& scat,
                          T& abs) const = 0;

    void generateDensityGrid(int w,
                             int h,
                             int d,
                             vector<T>& scat,
                             vector<T>& abs) const = 0;
};
