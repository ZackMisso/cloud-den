#pragma once

template <typename T>
class GaussEmitter : public DensityEmitter<T>
{
public:
    GaussEmitter(T x, T y, T z, T s)
        : cx(x), cy(y), cz(z), sigma(s) { }

    T calculateDensity(T x, T y, T z) const
    {
        // TODO
        return 0.0;
    }

    std::vector<T> generateDensityGrid(int w, int h, int d) const
    {
        std::vector<T> density = std::vector<T>(w*h*d);

        // TODO

        return density;
    }

protected:
    T cx;
    T cy;
    T cz;
    T sigma;
};
