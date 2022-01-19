#include <dirent.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    float data_float;
    uint8_t* data_ptr = (uint8_t*)&data_float;
    if ((argc < 5) || (argc > 6)) {
        printf("usage: \n");
        printf("    u8-to-float <u8> <u8> <u8> <u8> l/b\n");
        printf("    u8-to-float <u8> <u8> <u8> <u8> little/big\n");
    }
    else if (argc == 5) {
        data_ptr[0] = (uint8_t)atoi(argv[1]);
        data_ptr[1] = (uint8_t)atoi(argv[2]);
        data_ptr[2] = (uint8_t)atoi(argv[3]);
        data_ptr[3] = (uint8_t)atoi(argv[4]);
        printf(" u8: [%d, %d, %d, %d] <=> float: %f (little endian)\n",
               data_ptr[0], data_ptr[1], data_ptr[2], data_ptr[3], data_float);
    }
    else if (argc == 6) {
        if (argv[5][0] == 'l') {
            data_ptr[0] = (uint8_t)atoi(argv[1]);
            data_ptr[1] = (uint8_t)atoi(argv[2]);
            data_ptr[2] = (uint8_t)atoi(argv[3]);
            data_ptr[3] = (uint8_t)atoi(argv[4]);
            printf(" u8: [%d, %d, %d, %d] <=> float: %f (little endian)\n",
                   data_ptr[0], data_ptr[1], data_ptr[2], data_ptr[3],
                   data_float);
        }
        else if (argv[5][0] == 'b') {
            data_ptr[3] = (uint8_t)atoi(argv[1]);
            data_ptr[2] = (uint8_t)atoi(argv[2]);
            data_ptr[1] = (uint8_t)atoi(argv[3]);
            data_ptr[0] = (uint8_t)atoi(argv[4]);
            printf(" u8: [%d, %d, %d, %d] <=> float: %f (big endian)\n",
                   data_ptr[0], data_ptr[1], data_ptr[2], data_ptr[3],
                   data_float);
        }
    }
    // todo: check if the arguments are in the right range, or contains illegal
    // characters

    return 0;
}
