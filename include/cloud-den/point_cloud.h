#pragma once

#include <cloud-den/common.h>
#include <vector>

namespace cloud_den
{

class PointCloud
{
public:
    PointCloud();

    void writeToFile(std::string filename) const;
    void loadFromFile(std::string filename);

    void addPoint(const Vec3& point);

protected:
    std::vector<Vec3> cloud;
};

}
