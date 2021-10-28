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
    char utc_str[100];
    std::strftime(utc_str, sizeof(utc_str), "%a %b %d %Y %T", std::gmtime(&tt));
    std::string std_utc_str(utc_str);
    std::cout << "UTC: " << std_utc_str;

    // output ms and us
    double ms = (t - ( uint32_t )t) * 1000;
    printf(" %3.3f ms\n", ms);
    return 0;
}

/* --------------------------- end of file ----------------------------- */
