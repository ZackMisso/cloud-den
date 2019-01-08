#include <cloud-den/density_cloud.h>
#include <pcg32.h>

namespace cloud_den
{

DensityCloud::DensityCloud(int width, int height, int depth)
    : width(width), height(height), depth(depth)
{
    density = std::vector<double>();
    int size = width * height * depth;

    for (int i = 0; i < size; ++i)
    {
        density.push_back(0.0);
    }
}

DensityCloud::DensityCloud(std::string densityFile)
{
    density = std::vector<double>();
    loadFromFile(densityFile);
}

void DensityCloud::loadFromFile(std::string filename)
{
    std::ifstream inputStream;
    inputStream.open(filename);
    std::stringstream tokenStream;
    tokenStream << inputStream.rdbuf();

    std::string str;
    tokenStream >> str;
    width = stoi(str);

    tokenStream >> str;
    height = stoi(str);

    tokenStream >> str;
    depth = stoi(str);

    int size = width * height * depth;
    int index = 0;

    while(tokenStream >> str)
    {
        density.push_back(stod(str));

        if (++index == size) break;
    }
}

void DensityCloud::writeToFile(std::string filename)
{
    std::ofstream outputStream;
    outputStream.open(filename);

    outputStream << width << std::endl;
    outputStream << height << std::endl;
    outputStream << depth << std::endl;

    for (int i = 0; i < density.size(); ++i)
    {
        outputStream << density[i] << " ";
        if (i % 20 == 0) outputStream << std::endl;
    }

    outputStream.close();
}

void DensityCloud::set(int x, int y, int z, double value)
{
    if (x < 0 || x >= width) return;
    if (y < 0 || y >= height) return;
    if (z < 0 || z >= depth) return;

    density[z * (width * height) + y * width + x] = value;
}

double DensityCloud::get(int x, int y, int z) const
{
    if (x < 0 || x >= width) return 0.0;
    if (y < 0 || y >= height) return 0.0;
    if (z < 0 || z >= depth) return 0.0;

    // std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;

    return density[z * (width * height) + y * width + x];
}

double DensityCloud::get(int x, int y, int z, const std::vector<double>& vec) const
{
    if (x < 0 || x >= width) return 0.0;
    if (y < 0 || y >= height) return 0.0;
    if (z < 0 || z >= depth) return 0.0;

    return vec[z * (width * height) + y * width + x];
}

void DensityCloud::scale(double value)
{
    for (int i = 0; i < density.size(); ++i)
    {
        density[i] *= value;
    }
}

void DensityCloud::translate(int x, int y, int z)
{
    std::vector<double> old_density = density;

    for (int i = 0; i < depth; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0 ; k < width; ++k)
            {
                set(k, j, i, get(k + x, j + y, i + z, old_density));
            }
        }
    }
}

void DensityCloud::addNoise(double mag)
{
    pcg32 rng = pcg32(0x3214, 0x563);

    for (int i = 0; i < density.size(); ++i)
    {
        density[i] += density[i] * (2.0 * rng.nextDouble() - 1.0) * mag;
    }
}

void DensityCloud::clamp(double min, double max)
{
    for (int i = 0; i < density.size(); ++i)
    {
        if (density[i] < min) density[i] = min;
        if (density[i] > max) density[i] = max;
    }
}

void DensityCloud::stretch(Axis axis, double factor)
{
    std::vector<double> old_density = density;

    switch (axis)
    {
        case X_AXIS:
        {
            for (int z = 0; z < depth; ++z)
            {
                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        set(x, y, z, get(int(double(x)/factor), y, z, old_density));
                    }
                }
            }
            break;
        }
        case Y_AXIS:
        {
            for (int z = 0; z < depth; ++z)
            {
                // std::cout << "z: " << z << std::endl;
                for (int y = 0; y < height; ++y)
                {
                    // std::cout << "y: " << y << std::endl;
                    for (int x = 0; x < width; ++x)
                    {
                        // std::cout << "x: " << x << std::endl;
                        set(x, y, z, get(x, int(double(y)/factor), z, old_density));
                    }
                }
            }
            break;
        }
        case Z_AXIS:
        {
            for (int z = 0; z < depth; ++z)
            {
                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        set(x, y, z, get(x, y, int(double(z)/factor), old_density));
                    }
                }
            }
            break;
        }
    }
}

DensityCloud* DensityCloud::combine(const Density_Combine_Record& rec,
                                    const DensityCloud* one,
                                    const DensityCloud* two)
{
    DensityCloud* newCloud = new DensityCloud(rec.new_width,
                                              rec.new_height,
                                              rec.new_depth);

    if (rec.takeAverage)
    {
        for (int i = 0; i < one->depth; ++i)
        {
            for (int j = 0; j < one->height; ++j)
            {
                for (int k = 0; k < one->width; k++)
                {
                    newCloud->set(k + rec.x_offset_one,
                                  j + rec.y_offset_one,
                                  i + rec.z_offset_one,
                                  one->get(k, j, i));
                }
            }
        }

        for (int i = 0; i < two->depth; ++i)
        {
            for (int j = 0; j < two->height; ++j)
            {
                for (int k = 0; k < two->width; k++)
                {
                    double two_val = two->get(k, j, i);

                    double cloud_val = newCloud->get(k + rec.x_offset_two,
                                                     j + rec.y_offset_two,
                                                     i + rec.z_offset_two);

                    newCloud->set(k + rec.x_offset_two,
                                  j + rec.y_offset_two,
                                  i + rec.z_offset_two,
                                  (two_val + cloud_val) / 2.0);
                }
            }
        }
    }
    else if (rec.takeMax)
    {
        for (int i = 0; i < one->depth; ++i)
        {
            for (int j = 0; j < one->height; ++j)
            {
                for (int k = 0; k < one->width; k++)
                {
                    newCloud->set(k + rec.x_offset_one,
                                  j + rec.y_offset_one,
                                  i + rec.z_offset_one,
                                  one->get(k, j, i));
                }
            }
        }

        for (int i = 0; i < two->depth; ++i)
        {
            for (int j = 0; j < two->height; ++j)
            {
                for (int k = 0; k < two->width; k++)
                {
                    double two_val = two->get(k, j, i);

                    if (newCloud->get(k + rec.x_offset_two,
                                      j + rec.y_offset_two,
                                      i + rec.z_offset_two) < two_val)
                    {
                        newCloud->set(k + rec.x_offset_two,
                                      j + rec.y_offset_two,
                                      i + rec.z_offset_two,
                                      two_val);
                    }
                }
            }
        }
    }
    else if (rec.takeMin)
    {
        for (int i = 0; i < one->depth; ++i)
        {
            for (int j = 0; j < one->height; ++j)
            {
                for (int k = 0; k < one->width; k++)
                {
                    newCloud->set(k + rec.x_offset_one,
                                  j + rec.y_offset_one,
                                  i + rec.z_offset_one,
                                  one->get(k, j, i));
                }
            }
        }

        for (int i = 0; i < two->depth; ++i)
        {
            for (int j = 0; j < two->height; ++j)
            {
                for (int k = 0; k < two->width; k++)
                {
                    double two_val = two->get(k, j, i);

                    if (newCloud->get(k + rec.x_offset_two,
                                      j + rec.y_offset_two,
                                      i + rec.z_offset_two) > two_val)
                    {
                        newCloud->set(k + rec.x_offset_two,
                                      j + rec.y_offset_two,
                                      i + rec.z_offset_two,
                                      two_val);
                    }
                }
            }
        }
    }

    return newCloud;
}

void DensityCloud::mirror(Axis axis)
{
    std::vector<double> old_density = density;

    // std::cout << "width: " << width << std::endl;
    // std::cout << "height: " << height << std::endl;
    // std::cout << "depth: " << depth << std::endl;

    switch (axis)
    {
        case X_AXIS:
        {
            for (int z = 0; z < depth; ++z)
            {
                // std::cout << z << std::endl;
                for (int y = 0; y < height; ++y)
                {
                    // std::cout << "y: " << y << std::endl;
                    for (int x = 0; x < width; ++x)
                    {
                        // std::cout << "x: " << x << std::endl;
                        set(width - x - 1, y, z, get(x, y, z, old_density));
                    }
                }
            }
            break;
        }
        case Y_AXIS:
        {
            for (int z = 0; z < depth; ++z)
            {
                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        set(x, height - y - 1, z, get(x, y, z, old_density));
                    }
                }
            }
            break;
        }
        case Z_AXIS:
        {
            for (int z = 0; z < depth; ++z)
            {
                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        set(x, y, depth - z - 1, get(x, y, z, old_density));
                    }
                }
            }
            break;
        }
    }
}

}
