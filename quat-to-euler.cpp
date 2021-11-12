#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace Eigen;

// example: quat-to-euler 0.707074 -0.006445 0.004021 -0.707099

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("usage: %s w(q0) x(q1) y(q2) z(q3)\n", argv[0]);
        return 1;
    }
    double w = atof(argv[1]);
    const double x = atof(argv[2]);
    const double y = atof(argv[3]);
    const double z = atof(argv[4]);

    // check if it is a unit quaternion
    if ((std::fabs(w * w + x * x + y * y + z * z) - 1) > 0.001) {
        printf("not a unit quaternion [%.6f %.6f %.6f %.6f]\n", w, x, y, z);
        return 2;
    }
    printf("quaternion [w, x, y, z]: [%.6f %.6f %.6f %.6f]\n", w, x, y, z);
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
        printf("not a unit vector:[%.6f, %.6f, %.6f]\n", v1, v2, v3);
        return 3;
    }
    // find rotation matrix
    Eigen::Matrix3d rot;
    // [v1, v2, v3] must be a unit vector
    rot = Eigen::AngleAxisd(theta, Eigen::Vector3d(v1, v2, v3));

    // convert to ZYZ euler
    auto euler = rot.eulerAngles(2, 1, 0);

    double roll = euler[2] / M_PI * 180.0;
    double pitch = euler[1] / M_PI * 180.0;
    double yaw = euler[0] / M_PI * 180.0;
    printf(
        "(method 1) ZYX euler: [yaw, pitch, roll] = [%.6f %.6f %.6f] (deg)\n",
        yaw, pitch, roll);

    // method 2:
    // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    roll = atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y)) / M_PI * 180.0;
    pitch = asin(2 * (w * y - x * z)) / M_PI * 180.0;
    yaw = atan2(2 * (x * y + w * z), 1 - 2 * (y * y + z * z)) / M_PI * 180.0;
    printf(
        "(method 2) ZYX euler: [yaw, pitch, roll] = [%.6f %.6f %.6f]  (deg)\n",
        yaw, pitch, roll);
    return 0;
}
