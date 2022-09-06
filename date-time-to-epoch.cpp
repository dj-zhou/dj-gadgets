
#include <ctime>
#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// original code is from: https://stackoverflow.com/a/26099512

// convert "2022-02-19T18:45:09.898273+0000" to epoch time as double
// usage: date-time-to-epoch 2022-02-19T18:45:09.898273+0000

// supported forms:
// 1: 2022-02-19T18:45:09.898273+0000
// 2: 2022-02-25 15:59:29.886 (must accept space!)
// 3: dd/mm/yyyy-hh:mm:ss (no space!)
// 4: dd/mm/yyyy hh:mm:ss (must accept space!)

int ch_to_num(char c) {
    if (((int)c >= 48) && ((int)c <= 57)) {
        return (int)c - 48;
    }
    else {
        printf("wrong character, abort!\n");
        abort();
    }
}

bool is_leap_year(int year) {
    bool is_leap_year;
    if (year % 400 == 0)
        is_leap_year = true;
    else if (year % 100 == 0)
        is_leap_year = false;
    else if (year % 4 == 0)
        is_leap_year = true;
    else
        is_leap_year = false;
    return is_leap_year;
}

int month(int a, int yy) {
    int x = 0, c;
    int mon[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (c = 0; c < a - 1; c++) {
        if (c == 1) {
            if (is_leap_year(yy))
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
    int count = 0;
    for (int i = y1; i < y2; i++) {
        if (is_leap_year(i))
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
    NotAType = 0,
    yyyymmddThhmmss = 1,  // 2022-02-19T18:45:09.898273+0000
                          // 2022-02-19 18:45:09.898273+0000
    ddmmyyyyhhmmss = 2,   // 19/02/2022-18:45:09.898273
};

static int convert_time_to_epoch(char* str, double* ret) {
    int y = 0, m = 0, d, h, min, sec, day, us;
    // determine type
    DateTimeType type = DateTimeType::NotAType;
    if ((str[2] == '/') && (str[5] == '/') && (str[10] == '-') && (str[13] == ':')) {
        type = DateTimeType::ddmmyyyyhhmmss;
    }
    else if ((str[4] == '-') && (str[7] == '-') && ((str[10] == 'T') || (str[10] == ' ')) && (str[13] == ':')) {
        type = DateTimeType::yyyymmddThhmmss;
    }
    // find each component from string
    switch (type) {
    case DateTimeType::ddmmyyyyhhmmss:
        d = ch_to_num(str[0]) * 10 + ch_to_num(str[1]);
        m = ch_to_num(str[3]) * 10 + ch_to_num(str[4]);
        y = ch_to_num(str[6]) * 1000 + ch_to_num(str[7]) * 100 + ch_to_num(str[8]) * 10 + ch_to_num(str[9]);
        h = ch_to_num(str[11]) * 10 + ch_to_num(str[12]);
        min = ch_to_num(str[14]) * 10 + ch_to_num(str[15]);
        sec = ch_to_num(str[17]) * 10 + ch_to_num(str[18]);
        us = 0;
        if ((str[19] == '.') && (strlen(str) >= 26)) {
            for (int i = 0; i < 6; i++) {
                us = us * 10 + ch_to_num(str[20 + i]);
            }
        }
        break;
    case DateTimeType::yyyymmddThhmmss:
        // 2022-02-19T18:45:09.898273+0000
        // "2022-02-19 18:45:09.898273+0000"
        // 2022-02-19 18:45:09.898273+0000
        // the "+0000" part is not processed
        y = ch_to_num(str[0]) * 1000 + ch_to_num(str[1]) * 100 + ch_to_num(str[2]) * 10 + ch_to_num(str[3]);
        m = ch_to_num(str[5]) * 10 + ch_to_num(str[6]);
        d = ch_to_num(str[8]) * 10 + ch_to_num(str[9]);
        h = ch_to_num(str[11]) * 10 + ch_to_num(str[12]);
        min = ch_to_num(str[14]) * 10 + ch_to_num(str[15]);
        sec = ch_to_num(str[17]) * 10 + ch_to_num(str[18]);
        us = 0;
        if ((str[19] == '.') && (strlen(str) >= 26)) {
            for (int i = 0; i < 6; i++) {
                us = us * 10 + ch_to_num(str[20 + i]);
            }
        }
        break;
    default:
        return -1;
    }

    day = days(1970, y, 1, m, 1, d);
    unsigned int time_s = ((day * 24 + h) * 60 + min) * 60 + sec;
    *ret = time_s + us / 1000000.;
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Convert human readable time to epoch time\n\nusage examples:\n");
        printf("    %s 2022-02-19T18:45:09.898273+0000\n", argv[0]);
        printf("    %s \"2022-02-19 18:45:09.898273+0000\"\n", argv[0]);
        printf("    %s 2022-02-19 18:45:09.898273+0000\n", argv[0]);
        printf("    %s 2022-02-19T18:45:09.898273\n", argv[0]);
        printf("    %s 19/02/2022-18:45:09\n", argv[0]);
        printf("    %s 19/02/2022 18:45:09\n", argv[0]);  // this does not work!
        return 1;
    }
    double epoch_time;
    char* date_time_str;
    if (argc == 2) {
        date_time_str = argv[1];
    }
    else if (argc == 3) {
        printf("strlen(argv[1]  = %ld\n", strlen(argv[1]));
        printf("strlen(argv[2]  = %ld\n", strlen(argv[2]));
        date_time_str = (char*)malloc(strlen(argv[1] + strlen(argv[2]) + 2));
        char* ptr = date_time_str;
        for (size_t i = 0; i < strlen(argv[1]); i++)
            *ptr++ = argv[1][i];
        *ptr++ = ' ';
        for (size_t i = 0; i < strlen(argv[2]); i++)
            *ptr++ = argv[2][i];
        *ptr = '0';
    }
    if (convert_time_to_epoch(date_time_str, &epoch_time) == -1) {
        printf("not a recognized date/time string, exit.\n");
        return -1;
    }
    printf("Epoch time: %f\n", epoch_time);

    // OK, this is not a good practise
    if (argc == 3) {
        free(date_time_str);
    }
    return 0;
}
