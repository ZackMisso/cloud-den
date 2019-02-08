#include <cloud-den/point_cloud.h>

namespace cloud_den
{

PointCloud::PointCloud()
{
    cloud = std::vector<Vec3>();
}

void PointCloud::writeToFile(std::string filename) const
{
    std::ofstream outputStream;
    outputStream.open(filename);

    for (int i = 0; i < cloud.size(); ++i)
    {
        outputStream << "v " << cloud[i].x << " " << cloud[i].y << " " << cloud[i].z << std::endl;
    }

    outputStream.close();
}

void PointCloud::loadFromFile(std::string filename)
{
    // TODO: later
}

void PointCloud::addPoint(const Vec3& point)
{
    cloud.push_back(point);
}

}
