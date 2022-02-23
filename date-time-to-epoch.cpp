
#include <ctime>
#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// original code is from: https://stackoverflow.com/a/26099512

// convert "2022-02-19T18:45:09.898273+0000" to epoch time as double
// usage: date-time-to-epoch 2022-02-19T18:45:09.898273+0000

// supported forms:
// 1: dd/mm/yyyy-hh:mm:ss (no space!)
// 2: 2022-02-19T18:45:09.898273+0000

int char2num(char c) {
    int i;
    i = (int)c - 48;
    return i;
}

bool isleapyear(int year) {
    bool i;
    if (year % 400 == 0)
        i = true;
    else if (year % 100 == 0)
        i = false;
    else if (year % 4 == 0)
        i = true;
    else
        i = false;
    return i;
}

int month(int a, int yy) {
    int x = 0, c;
    int mon[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (c = 0; c < a - 1; c++) {
        if (c == 1) {
            if (isleapyear(yy))
                x += 29;
            else
                x += 28;
        }
        else
            x += mon[c];
    }
    return (x);
}

int days(int y1, int y2, int m1, int m2, int d1, int d2) {
    int count = 0, i;
    for (i = y1; i < y2; i++) {
        if (isleapyear(i))
            count += 366;
        else
            count += 365;
    }
    count -= month(m1, y1);
    count -= d1;
    count += month(m2, y2);
    count += d2;
    if (count < 0)
        count = count * -1;
    return count;
}

enum class DateTimeType {
    yyyymmddThhmmss = 1,  // 2022-02-19T18:45:09.898273+0000
    ddmmyyyyhhmmss = 2,   // 19/02/2022-18:45:09.898273
};

static double convertTimeToEpoch(char* str) {
    int y = 0, m = 0, d, h, min, sec, day, us;
    // determine type
    DateTimeType type;
    if ((str[2] == '/') && (str[5] == '/') && (str[10] == '-') && (str[13] == ':')) {
        type = DateTimeType::ddmmyyyyhhmmss;
    }
    else if ((str[4] == '-') && (str[7] == '-') && (str[10] == 'T') && (str[13] == ':')) {
        type = DateTimeType::yyyymmddThhmmss;
    }
    // find each component from string
    switch (type) {
    case DateTimeType::ddmmyyyyhhmmss:
        d = char2num(str[0]) * 10 + char2num(str[1]);
        m = char2num(str[3]) * 10 + char2num(str[4]);
        y = char2num(str[6]) * 1000 + char2num(str[7]) * 100 + char2num(str[8]) * 10 + char2num(str[9]);
        h = char2num(str[11]) * 10 + char2num(str[12]);
        min = char2num(str[14]) * 10 + char2num(str[15]);
        sec = char2num(str[17]) * 10 + char2num(str[18]);
        us = 0;
        if ((str[19] == '.') && (strlen(str) >= 26)) {
            for (int i = 0; i < 6; i++) {
                us = us * 10 + char2num(str[20 + i]);
            }
        }
        break;
    case DateTimeType::yyyymmddThhmmss:
        y = char2num(str[0]) * 1000 + char2num(str[1]) * 100 + char2num(str[2]) * 10 + char2num(str[3]);
        m = char2num(str[5]) * 10 + char2num(str[6]);
        d = char2num(str[8]) * 10 + char2num(str[9]);
        h = char2num(str[11]) * 10 + char2num(str[12]);
        min = char2num(str[14]) * 10 + char2num(str[15]);
        sec = char2num(str[17]) * 10 + char2num(str[18]);
        us = 0;
        if ((str[19] == '.') && (strlen(str) >= 26)) {
            for (int i = 0; i < 6; i++) {
                us = us * 10 + char2num(str[20 + i]);
            }
        }
        break;
    default:
        break;
    }

    day = days(1970, y, 1, m, 1, d);
    unsigned int time_s = ((day * 24 + h) * 60 + min) * 60 + sec;
    return time_s + us / 1000000.;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Convert human readable time to epoch time\n\nusage examples:\n");
        printf("    %s 2022-02-19T18:45:09.898273+0000\n", argv[0]);
        printf("    %s 2022-02-19T18:45:09.898273\n", argv[0]);
        printf("    %s 19/02/2022-18:45:09\n", argv[0]);
        printf("    %s 19/02/2022-18:45:09\n", argv[0]);
        return 1;
    }
    printf("epoc time: %f\n", convertTimeToEpoch(argv[1]));
    return 0;
}
