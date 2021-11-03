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
    char utc_str[100];

    // gmtime: convert "tt" to utc time
    std::strftime(utc_str, sizeof(utc_str), "%a %b %d %Y %T", std::gmtime(&tt));
    std::string std_utc_str(utc_str);
    std::cout << "UTC: " << std_utc_str << std::endl;

    return 0;
}
