#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
//
// enum Direction
// {
//     POS_X,
//     POS_Y,
//     POS_Z,
//     NEG_X,
//     NEG_Y,
//     NEG_Z
// };
//

namespace cloud_den
{

struct Vec3
{
    Vec3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vec3(double x, double y, double z)
        : x(x), y(y), z(z)
    {
    }

    double x;
    double y;
    double z;
};

enum Axis
{
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

}
