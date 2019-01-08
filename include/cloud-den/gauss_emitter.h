// #pragma once
//
// template <typename T>
// class GaussEmitter : public DensityEmitter<T>
// {
// public:
//     GaussEmitter(T x, T y, T z, T s)
//         : cx(x), cy(y), cz(z), sigma(s) { }
//
//     void calculateDensity(T x,
//                           T y,
//                           T z,
//                           T& scat,
//                           T& abs) const
//     {
//         // TODO
//
//         scat = 0.0;
//         abs = 0.0;
//     }
//
//     void generateDensityGrid(int w,
//                              int h,
//                              int d,
//                              vector<T>& scat,
//                              vector<T>& abs) const
//     {
//         scat = std::vector<T>(w*h*d);
//         abs = std::vector<T>(w*h*d);
//
//         // TODO
//     }
//
// protected:
//     T cx;
//     T cy;
//     T cz;
//     T sigma;
// };
