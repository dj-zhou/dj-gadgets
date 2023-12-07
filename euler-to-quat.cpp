#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace Eigen;

// example: euler-to-quat -90.000592 -0.196423 -0.848052  -d

int main(int argc, char* argv[]) {
    if ((argc < 4) || (argc > 5)) {
        printf("usage:\n    %s yaw(psi) pitch(theta) roll(phi) [-r or -d]\n", argv[0]);
        printf("    -r: use radian (default)\n");
        printf("    -d: use degree\n");
        return 1;
    }
    double yaw = atof(argv[1]);
    double pitch = atof(argv[2]);
    double roll = atof(argv[3]);

    bool use_radian = true;
    if (argc == 5) {
        if (strcmp(argv[4], "-d") == 0) {
            use_radian = false;
        }
    }
    if (use_radian) {
        printf("ZYX Euler (Tait-Bryan) angles [yaw, pitch, roll]: [%.6f "
               "%.6f %.6f] (rad)\n",
               yaw, pitch, roll);
    }
    else {
        printf("ZYX Euler (Tait-Bryan) angles [yaw, pitch, roll]: [%.6f "
               "%.6f %.6f] (deg)\n",
               yaw, pitch, roll);
        // convert from degree to radian
        yaw = yaw / 180.0 * M_PI;
        pitch = pitch / 180.0 * M_PI;
        roll = roll / 180.0 * M_PI;
    }

    // calculate rotation matrix, do not delete
    // Eigen::Matrix3d R_yaw;
    // R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d(0, 0, 1));
    // Eigen::Matrix3d R_pitch;
    // R_pitch = Eigen::AngleAxisd(pitch, Eigen::Vector3d(0, 1, 0));
    // Eigen::Matrix3d R_roll;
    // R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d(1, 0, 0));
    // Eigen::Matrix3d R = R_yaw * R_pitch * R_roll;

    // std::cout << "R_yaw:\n" << R_yaw << std::endl;
    // std::cout << "R_pitch:\n" << R_pitch << std::endl;
    // std::cout << "R_roll:\n" << R_roll << std::endl;
    // std::cout << "R = R_yaw * R_pitch * R_roll:\n" << R << std::endl;

    // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    // (Source code)
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    double w = cr * cp * cy + sr * sp * sy;
    double x = sr * cp * cy - cr * sp * sy;
    double y = cr * sp * cy + sr * cp * sy;
    double z = cr * cp * sy - sr * sp * cy;
    printf("Quaternion: [w, x, y, z] = [%.6f %.6f %.6f %.6f]\n", w, x, y, z);
    return 0;
}
