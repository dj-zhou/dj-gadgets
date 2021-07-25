/**************************************************************************
   File Name      : main.c
   Author         : Dingjiang Zhou
                    Boston University, Boston, 02215
   Email          : zhoudingjiang@gmail.com
   Create Time    : Fri, Aug. 09th, 2013. 00:45:50 PM
   Last Modified  : Sat, Oct. 01st, 2016. 09:11:08 AM
   Purpose        : to clean the ~ folder in Linux computer.
**************************************************************************/
#include <dirent.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// ------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {

    double   data_double;
    uint8_t* data_ptr = ( uint8_t* )&data_double;
    if ((argc < 9) || (argc > 10)) {
        printf("usage: \n");
        printf(
            "    u8-to-double <u8> <u8> <u8> <u8> <u8> <u8> <u8> <u8> l/b\n");
        printf("    u8-to-double <u8> <u8> <u8> <u8> <u8> <u8> <u8> <u8> "
               "little/big\n");
    }
    else if (argc == 9) {
        data_ptr[0] = ( uint8_t )atoi(argv[1]);
        data_ptr[1] = ( uint8_t )atoi(argv[2]);
        data_ptr[2] = ( uint8_t )atoi(argv[3]);
        data_ptr[3] = ( uint8_t )atoi(argv[4]);
        data_ptr[4] = ( uint8_t )atoi(argv[5]);
        data_ptr[5] = ( uint8_t )atoi(argv[6]);
        data_ptr[6] = ( uint8_t )atoi(argv[7]);
        data_ptr[7] = ( uint8_t )atoi(argv[8]);
        printf(" u8: [%d, %d, %d, %d, %d, %d, %d, %d] <=> double: %f (little "
               "endian)\n",
               data_ptr[0], data_ptr[1], data_ptr[2], data_ptr[3], data_ptr[4],
               data_ptr[5], data_ptr[6], data_ptr[7], data_double);
    }
    else if (argc == 10) {
        if (argv[9][0] == 'l') {
            data_ptr[0] = ( uint8_t )atoi(argv[1]);
            data_ptr[1] = ( uint8_t )atoi(argv[2]);
            data_ptr[2] = ( uint8_t )atoi(argv[3]);
            data_ptr[3] = ( uint8_t )atoi(argv[4]);
            data_ptr[4] = ( uint8_t )atoi(argv[5]);
            data_ptr[5] = ( uint8_t )atoi(argv[6]);
            data_ptr[6] = ( uint8_t )atoi(argv[7]);
            data_ptr[7] = ( uint8_t )atoi(argv[8]);
            printf(" u8: [%d, %d, %d, %d, %d, %d, %d, %d] <=> double: %f "
                   "(little endian)\n",
                   data_ptr[0], data_ptr[1], data_ptr[2], data_ptr[3],
                   data_ptr[4], data_ptr[5], data_ptr[6], data_ptr[7],
                   data_double);
        }
        else if (argv[9][0] == 'b') {
            data_ptr[7] = ( uint8_t )atoi(argv[1]);
            data_ptr[6] = ( uint8_t )atoi(argv[2]);
            data_ptr[5] = ( uint8_t )atoi(argv[3]);
            data_ptr[4] = ( uint8_t )atoi(argv[4]);
            data_ptr[3] = ( uint8_t )atoi(argv[5]);
            data_ptr[2] = ( uint8_t )atoi(argv[6]);
            data_ptr[1] = ( uint8_t )atoi(argv[7]);
            data_ptr[0] = ( uint8_t )atoi(argv[8]);
            printf(" not tested\r\n");
            printf(" u8: [%d, %d, %d, %d, %d, %d, %d, %d] <=> double: %f (big "
                   "endian)\n",
                   data_ptr[0], data_ptr[1], data_ptr[2], data_ptr[3],
                   data_ptr[4], data_ptr[5], data_ptr[6], data_ptr[7],
                   data_double);
        }
    }

    return 0;
}

/* --------------------------- end of file ----------------------------- */
