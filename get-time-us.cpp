#include <stdio.h>
#include <sys/time.h>

int main(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    unsigned long long us = (unsigned long long)tv.tv_sec * 1000000 + (unsigned long long)tv.tv_usec;
    printf("%llu\n", us);
    return 0;
}
