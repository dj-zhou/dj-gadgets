#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace Eigen;

// example:
// rot-to-quat R(1,1) R(1,2) R(1,3) R(2,1) R(2,2) R(2,3) R(3,1) R(3,2) R(3,3)

int main(int argc, char* argv[]) {
    if (argc != 10) {
        printf("usage: %s R(1,1) R(1,2) R(1,3) R(2,1) R(2,2) R(2,3) R(3,1) "
               "R(3,2) R(3,3)\n",
               argv[0]);
        return 1;
    }
    Eigen::Matrix3d rot;
    rot << atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]),
        atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]),
        atof(argv[9]);
    printf("Input matrix:\n");
    for (int i = 0; i < 3; i++) {
        printf("[%.6f %.6f %.6f]\n", rot(i, 0), rot(i, 1), rot(i, 2));
    }
    // check if it is a rotation matrix
    return 0;
}
