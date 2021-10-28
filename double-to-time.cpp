#include <ctime>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s <double>\n", argv[0]);
        return 1;
    }
    double t = atof(argv[1]);
    const time_t tt = ( time_t )t;

    std::cout << std::ctime(&tt);
    return 0;
}