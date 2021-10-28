#include <ctime>
#include <dirent.h>
#include <iostream>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s <double>\n", argv[0]);
        return 1;
    }
    double t = atof(argv[1]);
    const time_t tt = ( time_t )t;

    std::cout << std::ctime(&tt) << std::endl;
    return 0;
}

/* --------------------------- end of file ----------------------------- */
