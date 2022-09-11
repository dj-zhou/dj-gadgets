#include <stdio.h>
#include <sys/time.h>

int main(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    long int us = (long int)tv.tv_sec * 1000000 + (long int)tv.tv_usec;
    printf("%ld\n", us);
    return 0;
}