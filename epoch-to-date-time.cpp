
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string.h>

// original code is from: https://stackoverflow.com/a/26099512

// convert "1645296309.898273" to human readable date & time:
// usage: date-time-to-epoch 1645296309.898273
// result: 2022-02-19T18:45:09.898273

// bool is_leap_year(int year) {
//     if (year % 400 == 0)
//         return true;
//     else if (year % 100 == 0)
//         return false;
//     else if (year % 4 == 0)
//         return true;
//     else
//         return false;
// }

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Convert epoch time to human readable date & time\nusage examples:\n");
        printf("    %s 1645296309.898273\n", argv[0]);
        printf("    %s 1645296309\n", argv[0]);
        return 1;
    }

    if (strspn(argv[1], "0123456789.\n") != strlen(argv[1])) {
        fprintf(stderr, "found non-numeric value, exit.\n");
        return -1;
    }
    double epoch_time = atof(argv[1]);
    printf("Epoch time: %f\n", epoch_time);
    return 0;
}
