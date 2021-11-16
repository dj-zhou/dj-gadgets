#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace Eigen;

// example: quat-to-rot 0.707074 -0.006445 0.004021 -0.707099

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("usage: %s w(q0) x(q1) y(q2) z(q3)\n", argv[0]);
        return 1;
    }
    const double w = atof(argv[1]);
    const double x = atof(argv[2]);
    const double y = atof(argv[3]);
    const double z = atof(argv[4]);
    if ((std::fabs(w * w + x * x + y * y + z * z) - 1) > 0.001) {
        printf("not a unit quaternion [%.6f %.6f %.6f %.6f]\n", w, x, y, z);
        return 2;
    }
    printf("quaternion [w, x, y, z] = [%.6f %.6f %.6f %.6f]\n", w, x, y, z);

    double ww = w * w;
    double xx = x * x;
    double yy = y * y;
    double zz = z * z;
    double wx = w * x;
    double wy = w * y;
    double wz = w * z;
    double xy = x * y;
    double xz = x * z;
    double yz = y * z;
    Eigen::Matrix3d rot;
    // clang-format off
    rot << ww + xx - yy - zz, 2 * (xy - wz)    , 2 * (wy + xz),    \
           2 * (xy + wz)    , ww - xx + yy - zz, 2 * (yz - wx),    \
           2 * (xz - wy)    , 2 * (wx + yz)    , ww - xx - yy + zz;
    // clang-format on

    printf("Rotation matrix:\n");
    for (int i = 0; i < 3; i++) {
        printf("[%.6f %.6f %.6f]\n", rot(i, 0), rot(i, 1), rot(i, 2));
    }

    return 0;
}
