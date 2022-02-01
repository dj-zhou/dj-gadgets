#include "time-fetch.h"
#include <time.h>

void current_time_date(char* time2Print) {
    char wday[][3] = {
        { 'S', 'u', 'n' }, { 'M', 'o', 'n' }, { 'T', 'u', 'e' },
        { 'W', 'e', 'd' }, { 'T', 'h', 'u' }, { 'F', 'r', 'i' },
        { 'S', 'a', 't' },
    };
    char wmon[][3] = {
        { 'J', 'a', 'n' }, { 'F', 'e', 'b' }, { 'M', 'a', 'r' },
        { 'A', 'p', 'r' }, { 'M', 'a', 'y' }, { 'J', 'u', 'n' },
        { 'J', 'u', 'l' }, { 'A', 'u', 'g' }, { 'S', 'e', 'p' },
        { 'O', 'c', 't' }, { 'N', 'o', 'v' }, { 'D', 'e', 'c' }
    };
    time_t timep;
    struct tm* p;
    // char time2Print[]="WWW, MMM. DDth, YYYY. HH:MM:SS AM";
    int year, mon, day, wkday, hour, min, sec;

    /* obtain the time */
    time(&timep);
    p = localtime(&timep);

    /* store the time */
    year = 1900 + p->tm_year;
    mon = p->tm_mon;
    day = p->tm_mday;
    wkday = p->tm_wday;
    hour = p->tm_hour;
    min = p->tm_min;
    sec = p->tm_sec;

    /* weekday or weekend */
    time2Print[0] = wday[wkday][0];
    time2Print[1] = wday[wkday][1];
    time2Print[2] = wday[wkday][2];

    /* month */
    time2Print[5] = wmon[mon][0];
    time2Print[6] = wmon[mon][1];
    time2Print[7] = wmon[mon][2];

    /* day */
    time2Print[10] = (char)((int)(day / 10.0) + 48);
    time2Print[11] = (char)(day % 10 + 48);
    if (((int)(day / 10.0)) == 0 || ((int)(day / 10.0)) == 2
        || ((int)(day / 10.0)) == 3) {
        switch (day % 10) {
        case 1:
            time2Print[12] = 's';
            time2Print[13] = 't';
            break;
        case 2:
            time2Print[12] = 'n';
            time2Print[13] = 'd';
            break;
        case 3:
            time2Print[12] = 'r';
            time2Print[13] = 'd';
            break;
        default:
            time2Print[12] = 't';
            time2Print[13] = 'h';
            break;
        }
    }

    /* year */
    time2Print[16] = (char)((int)(year / 1000.0) + 48);
    time2Print[17] = (char)((int)(year % 1000 / 100.0) + 48);
    time2Print[18] = (char)((int)(year % 100 / 10.0) + 48);
    time2Print[19] = (char)(year % 10 + 48);

    /* hour */
    time2Print[22] = (char)((int)(hour % 12 / 10.0) + 48);
    time2Print[23] = (char)(hour % 12 % 10 + 48);

    /* minute */
    time2Print[25] = (char)((int)(min / 10.0) + 48);
    time2Print[26] = (char)(min % 10 + 48);

    /* second */
    time2Print[28] = (char)((int)(sec / 10.0) + 48);
    time2Print[29] = (char)(sec % 10 + 48);

    /* AM or PM */
    if (hour >= 12)
        time2Print[31] = 'P';
}
