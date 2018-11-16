#pragma once

template <typename T>
class PercolationEmitter : public DensityEmitter<T>
{
public:
    PercolationEmitter(T p, T t, int runs)
        : p(p), t(t), runs(runs)
    {
        // TODO
    }

    void calculateDensity(T x,
                          T y,
                          T z,
                          T& scat,
                          T& abs) const
    {
        // TODO

        scat = 0.0;
        abs = 0.0;
    }

    void generateDensityGrid(int w,
                             int h,
                             int d,
                             vector<T>& scat,
                             vector<T>& abs) const
    {
        scat = std::vector<T>(w*h*d);
        abs = std::vector<T>(w*h*d);

        // TODO
    }

protected:
    T p;
    T t;
    int runs;
}
