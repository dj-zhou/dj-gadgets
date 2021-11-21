#include <ctime>
#include <iostream>
#include <stdio.h>

using namespace std;

// double-to-time 1637506242.019466
// UTC: Sun Nov 21 2021 14:50:42
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s <double>\n", argv[0]);
        return 1;
    }
    double t = atof(argv[1]);
    int us = ( int )((t - ( int )t) * 1000000);
    int ms = us / 1000;
    us = us - 1000 * ms;
    const time_t tt = ( time_t )t;
    char utc_str[100];

    // gmtime: convert "tt" to utc time
    std::strftime(utc_str, sizeof(utc_str), "%a %b %d %T UTC %Y",
                  std::gmtime(&tt));
    sprintf(utc_str + 28, " %03d:%03d", ms, us);
    std::string std_utc_str(utc_str);
    std::cout << std_utc_str << std::endl;

    return 0;
}
