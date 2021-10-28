#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s <double>\n", argv[0]);
        return 1;
    }
    double rad = atof(argv[1]);
    printf("%.6f rad = %.2f deg\n", rad, rad * 180.0 / M_PI);
    return 0;
}
