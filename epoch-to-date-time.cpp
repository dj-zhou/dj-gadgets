
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

// convert "1645296309.898273" to human readable date & time:
// usage: date-time-to-epoch 1645296309.898273
// result: 2022-02-19 18:45:09.898273

const std::vector<std::pair<int, int>> Month({
    { 1, 31 },
    { 2, 28 },
    { 3, 31 },
    { 4, 30 },
    { 5, 31 },
    { 6, 30 },
    { 7, 31 },
    { 8, 31 },
    { 9, 30 },
    { 10, 31 },
    { 11, 30 },
    { 12, 31 },
});

bool is_leap_year(int year) {
    if ((year % 4) != 0)
        return false;
    if (((year % 400) != 0) && ((year % 100) == 0))
        return false;
    return true;
}

// The "epoch day" in Linux world is 01/01/1970
int get_year(int& days) {
    days += 1;
    int year = 1970;
    while (days > 365) {
        days -= 365;
        if (is_leap_year(year)) {
            days -= 1;
        }
        year++;
    }
    return year;
}

int get_month(int& days, int year) {
    for (auto e : Month) {
        int days_in_a_month = e.second;
        if ((e.first == 2) && (is_leap_year(year)))
            days_in_a_month++;
        if (days <= days_in_a_month)
            return e.first;
        days -= days_in_a_month;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Convert epoch time to human readable date & time\nusage examples:\n");
        printf("    %s 1645296309.898273\n", argv[0]);
        printf("    %s 1645296309\n", argv[0]);
        return 0;
    }

    if (strspn(argv[1], "0123456789.\n") != strlen(argv[1])) {
        fprintf(stderr, "found non-numeric value, exit.\n");
        return -1;
    }

    double epoch_time = atof(argv[1]);
    printf(" Epoch time: %f\n", epoch_time);
    int seconds = (int)epoch_time;
    int days = seconds / 60 / 60 / 24;
    int seconds_left = seconds - days * 60 * 60 * 24;
    int year = get_year(days);
    int month = get_month(days, year);
    int hour = seconds_left / 60 / 60;
    seconds_left -= hour * 60 * 60;
    int minute = seconds_left / 60;
    seconds_left -= minute * 60;
    double us = epoch_time - seconds;
    // 2022-02-19 18:45:09.898273
    printf("date & time: %04d-%02d-%02d %02d:%02d:%02d.%06d\n", year, month, days, hour, minute, seconds_left,
           (int)(us * 1000000));
    return 0;
}
