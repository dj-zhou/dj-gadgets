#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("usage: %s <double> <double> <double> <double>\n", argv[0]);
        return 1;
    }
    double w = atof(argv[1]);
    const double x = atof(argv[2]);
    const double y = atof(argv[3]);
    const double z = atof(argv[4]);

    // check if it is a unit quaternion
    if ((std::fabs(w * w + x * x + y * y + z * z) - 1) > 0.001) {
        printf("not a unit quaternion\n");
        return 2;
    }
    printf("quaternion: [%.4f, %.4f, %.4f, %.4f]\n", w, x, y, z);
    // find axis and angle
    if (w > 1) {
        w = 1;
    }
    double theta = 2 * acos(w);
    double v1 = x / sin(theta / 2.0);
    double v2 = y / sin(theta / 2.0);
    double v3 = z / sin(theta / 2.0);
    // check if it is a unit vector
    if ((std::fabs(v1 * v1 + v2 * v2 + v3 * v3) - 1) > 0.001) {
        printf("not a unit vector\n");
        return 2;
    }
    // find rotation matrix
    Eigen::Matrix3d rot;
    rot = Eigen::AngleAxisd(theta, Eigen::Vector3d(x, y, z));

    // convert to ZYZ euler
    auto euler = rot.eulerAngles(2, 1, 0);

    double yaw = euler[0] / M_PI * 180.0;
    double roll = euler[2] / M_PI * 180.0;
    double pitch = euler[1] / M_PI * 180.0;
    printf("ZYX euler: yaw = %.3f, pitch = %.3f, roll = %.3f (deg)\n", yaw, pitch,
           roll);
    return 0;
}
