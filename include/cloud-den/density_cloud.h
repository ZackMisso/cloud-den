#pragma once

#include <cloud-den/common.h>
#include <cloud-den/point_cloud.h>
#include <vector>

namespace cloud_den
{

struct Density_Combine_Record
{
    Density_Combine_Record()
    {
        new_width = 0;
        new_height = 0;
        new_depth = 0;

        x_offset_one = 0;
        y_offset_one = 0;
        z_offset_one = 0;

        x_offset_two = 0;
        y_offset_two = 0;
        z_offset_two = 0;

        takeAverage = false;
        takeMax = false;
        takeMin = false;
    }

    int new_width;
    int new_height;
    int new_depth;

    int x_offset_one;
    int y_offset_one;
    int z_offset_one;

    int x_offset_two;
    int y_offset_two;
    int z_offset_two;

    bool takeAverage;
    bool takeMax;
    bool takeMin;
};

class DensityCloud
{
public:
    DensityCloud(int width, int height, int depth);
    DensityCloud(std::string densityFile);

    void loadFromFile(std::string filename);
    void writeToFile(std::string filename);

    static DensityCloud* combine(const Density_Combine_Record& rec,
                                 const DensityCloud* one,
                                 const DensityCloud* two);

    void mirror(Axis axis);

    void set(int x, int y, int z, double value);
    double get(int x, int y, int z) const;
    double get(int x, int y, int z, const std::vector<double>& vec) const;
    void scale(double value);
    void stretch(Axis axis, double factor);
    void translate(int x, int y, int z);
    void addNoise(double mag);
    void clamp(double min, double max);

    DensityCloud* doubleCloud() const;
    DensityCloud* partial(int x_off,
                          int y_off,
                          int z_off,
                          int x_size,
                          int y_size,
                          int z_size) const;

    PointCloud* tightPointCloud() const;
    PointCloud* pointRepresentation() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getDepth() const { return depth; }

protected:
    std::vector<double> density;
    int width;
    int height;
    int depth;
};

}
