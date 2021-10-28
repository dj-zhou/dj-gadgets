#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s <double>\n", argv[0]);
        return 1;
    }
    double deg = atof(argv[1]);
    printf("%.6f deg = %.2f rad\n", deg, deg * M_PI / 180.0);
    return 0;
}
