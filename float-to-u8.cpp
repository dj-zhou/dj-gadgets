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
    uint8_t* data_ptr = (uint8_t*)(&data_float);
    uint8_t data_u8[4];
    if (argc == 1) {
        printf("usage: \n");
        printf("$ %s [float number]\n", argv[0]);
        printf("$ %s [float number] [l or b]\n", argv[0]);
        printf("$ %s [float number] [little or big]\n", argv[0]);
        return 0;
    }
    if (argc == 2) {
        data_float = (float)atof(argv[1]);
        for (int i = 0; i < 4; i++) {
            data_u8[i] = *data_ptr;
            data_ptr++;
        }
        printf("float: %f <=> u8: [%d, %d, %d, %d] (little endian)\n", data_float, data_u8[0], data_u8[1], data_u8[2],
               data_u8[3]);
        printf("float: %f <=> u8: 0x[%02X, %02X, %02X, %02X] (little endian)\n", data_float, data_u8[0], data_u8[1],
               data_u8[2], data_u8[3]);
    }
    else if (argc == 3) {
        data_float = (float)atof(argv[1]);
        for (int i = 0; i < 4; i++) {
            data_u8[i] = *data_ptr;
            data_ptr++;
        }
        data_float = (float)atof(argv[1]);
        if (argv[2][0] == 'l') {
            printf("float: %f <=> u8: [%d, %d, %d, %d] (little endian)\n", data_float, data_u8[0], data_u8[1],
                   data_u8[2], data_u8[3]);
            printf("float: %f <=> u8: 0x[%02X, %02X, %02X, %02X] (little endian)\n", data_float, data_u8[0], data_u8[1],
                   data_u8[2], data_u8[3]);
        }
        else if (argv[2][0] == 'b') {
            printf("float: %f <=> u8: [%d, %d, %d, %d] (big endian)\n", data_float, data_u8[3], data_u8[2], data_u8[1],
                   data_u8[0]);
            printf("float: %f <=> u8: 0x[%02X, %02X, %02X, %02X] (big endian)\n", data_float, data_u8[3], data_u8[2],
                   data_u8[1], data_u8[0]);
        }
    }
    return 0;
}
