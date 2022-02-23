
#include <ctime>
#include <iostream>
#include <stdbool.h>
#include <stdio.h>

// original code is from: https://stackoverflow.com/a/26099512

// convert "2022-02-19T18:45:09.898273+0000" to epoch time as double
// usage: date-time-to-epoch 2022-02-19T18:45:09.898273+0000

// supported forms:
// 1: dd/mm/yyyy hh:mm:ss
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

static unsigned int convertTimeToEpoch(char* dateTime) {
    int char2num(char);
    int y = 0, m = 0, d, h, min, sec, day;
    unsigned int time;
    d = char2num(dateTime[0]) * 10 + char2num(dateTime[1]);
    m = char2num(dateTime[3]) * 10 + char2num(dateTime[4]);
    y = char2num(dateTime[6]) * 1000 + char2num(dateTime[7]) * 100 + char2num(dateTime[8]) * 10 + char2num(dateTime[9]);
    h = char2num(dateTime[11]) * 10 + char2num(dateTime[12]);
    min = char2num(dateTime[14]) * 10 + char2num(dateTime[15]);
    sec = char2num(dateTime[17]) * 10 + char2num(dateTime[18]);
    day = days(1970, y, 1, m, 1, d);
    time = ((day * 24 + h) * 60 + min) * 60 + sec;
    return time;
}

int main(int argc, char* argv[]) {
    (void)argc;
    unsigned int epoc = convertTimeToEpoch(argv[1]);
    printf("epoc time: %d\n", epoc);
    return 0;
}
