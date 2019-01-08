#include <cloud-den/cloud.h>
#include <cloud-den/gauss_emitter.h>
#include <cloud-den/density_cloud.h>

using namespace cloud_den;
// {

int main(int argc, char* argv[])
{
    // DensityCloud* one = new DensityCloud("/Users/corneria/Documents/Research/testscenes/smoke_scene/geometry/media_plume.txt");
    // one->mirror(Axis::Z_AXIS);
    // one->stretch(Axis::Y_AXIS, 1.0);
    // one->writeToFile("/Users/corneria/Documents/Research/testscenes/smoke_scene/geometry/tmpMedia.txt");
    // delete one;

    DensityCloud* right = new DensityCloud("/Users/corneria/Documents/Research/testscenes/smoke_scene/geometry/media_plume.txt");
    DensityCloud* left = new DensityCloud("/Users/corneria/Documents/Research/testscenes/smoke_scene/geometry/media_plume.txt");
    left->mirror(Axis::X_AXIS);

    Density_Combine_Record record = Density_Combine_Record();;
    record.takeMax = true;
    right->translate(-40, 0.0, 0.0);
    // std::cout << "WHAT" << std::endl;
    right->stretch(Axis::Y_AXIS, 0.8);
    // record.x_offset_two = 0;
    // record.x_offset_one = -120;
    record.new_width = right->getWidth();
    record.new_height = right->getHeight();
    record.new_depth = right->getDepth();

    DensityCloud* new_cloud = DensityCloud::combine(record, right, left);
    new_cloud->stretch(Axis::Y_AXIS, 1.35);
    new_cloud->stretch(Axis::X_AXIS, 1.35);
    new_cloud->stretch(Axis::Z_AXIS, 1.35);
    // new_cloud->translate(0, 0, -60);
    // new_cloud->stretch(Axis::Z_AXIS, 2.0);
    // new_cloud->translate(0, 0, 60);
    // new_cloud->addNoise(1.0);
    new_cloud->clamp(0.0, 1.0);
    new_cloud->writeToFile("/Users/corneria/Documents/Research/testscenes/smoke_scene/geometry/tmpMedia.txt");

    // delete one;
    delete right;
    delete left;
    delete new_cloud;

    // std::cout << "TODO" << std::endl;
    // TODO
    return 0;
}

// }
