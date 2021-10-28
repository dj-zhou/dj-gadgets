#include <dirent.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if ((argc <= 1) || (argc > 2)) {
        printf(" ascii-code: too few argument, usage (examples): \n");
        printf(" $   ascii-code  c\n");
        printf(" $   ascii-code \"c\"\n");
        printf(" $   ascii-code \"5\"\n");
        printf(" $   ascii-code \"&\"\n");
        return -1;
    }
    // the argument is taken as a char
    char c = *argv[1];
    printf("%c | Dec: %d | Hex: %x\n", c, c, c);
    return 0;
}
