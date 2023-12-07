#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace Eigen;

// example:
// rot-to-quat R(1,1) R(1,2) R(1,3) R(2,1) R(2,2) R(2,3) R(3,1) R(3,2) R(3,3)
// rot-to-quat
// -0.000010 0.999891 0.014801 -0.999994 -0.000061 0.003428 0.003428 -0.014801
// 0.999885
int main(int argc, char* argv[]) {
    if (argc != 10) {
        printf("usage: %s R(1,1) R(1,2) R(1,3) R(2,1) R(2,2) R(2,3) R(3,1) "
               "R(3,2) R(3,3)\n",
               argv[0]);
        return 1;
    }
    Eigen::Matrix3d R;
    R << atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]),
        atof(argv[8]), atof(argv[9]);
    // check if it is a rotation matrix
    Eigen::Matrix3d I;
    I.setIdentity();
    Eigen::Matrix3d checkR = R * R.transpose() - I;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (std::abs(checkR(i, j)) > 0.0001) {
                printf("not a rotation matrix, exit!\n");
                return 1;
            }
        }
    }
    printf("Input matrix:\n");
    for (int i = 0; i < 3; i++) {
        printf("[%.6f %.6f %.6f]\n", R(i, 0), R(i, 1), R(i, 2));
    }
    // https://math.stackexchange.com/questions/893984/conversion-of-rotation-matrix-to-quaternion
    // seems not right? because it uses [x,y,z,w], but we used [w,x,y,z]
    double m00 = R(0, 0);
    double m01 = R(0, 1);
    double m02 = R(0, 2);
    double m10 = R(1, 0);
    double m11 = R(1, 1);
    double m12 = R(1, 2);
    double m20 = R(2, 0);
    double m21 = R(2, 1);
    double m22 = R(2, 2);
    double t = 0;
    // Eigen::Quaterniond q;  // [x,y,z,w]
    Eigen::Vector4d q;  // [x,y,z,w]
    if (m22 < 0) {
        if (m00 > m11) {
            t = 1 + m00 - m11 - m22;
            q = Vector4d(t, m01 + m10, m20 + m02, m12 - m21);
        }
        else {
            t = 1 - m00 + m11 - m22;
            q = Vector4d(m01 + m10, t, m12 + m21, m20 - m02);
        }
    }
    else {
        if (m00 < -m11) {
            t = 1 - m00 - m11 + m22;
            q = Vector4d(m20 + m02, m12 + m21, t, m01 - m10);
        }
        else {
            t = 1 + m00 + m11 + m22;
            q = Vector4d(m12 - m21, m20 - m02, m01 - m10, t);
        }
    }
    double x = q(0) * 0.5 / std::sqrt(t);
    double y = q(1) * 0.5 / std::sqrt(t);
    double z = q(2) * 0.5 / std::sqrt(t);
    double w = q(3) * 0.5 / std::sqrt(t);

    printf("quaternion [w, x, y, z] = [%.6f %.6f %.6f %.6f]\n", w, x, y, z);
    return 0;
}
