/**************************************************************************
   File Name      : main.c
   Author         : Dingjiang Zhou
                    Boston University, Boston, 02215
   Email          : zhoudingjiang@gmail.com
   Create Time    : Fri, Aug. 09th, 2013. 00:45:50 PM
   Last Modified  : Sat, Oct. 01st, 2016. 09:11:08 AM
   Purpose        : to clean the ~ folder in Linux computer.
**************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
 

// ------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
 
	float data_float;
	uint8_t * data_ptr = (uint8_t*) &data_float;
	if( (argc < 5) || (argc >6) ) {
		printf("usage: \n");
		printf("    u8-to-float <u8> <u8> <u8> <u8> l/b\n");
		printf("    u8-to-float <u8> <u8> <u8> <u8> little/big\n");
	}
	else if (argc == 5) {
		data_ptr[0] = atof(argv[1]);
		data_ptr[1] = atof(argv[2]);
		data_ptr[2] = atof(argv[3]);
		data_ptr[3] = atof(argv[4]);
		printf(" u8: [%d, %d, %d, %d] <=> float: %f (little endian)\n",
			data_ptr[0],data_ptr[1],data_ptr[2],data_ptr[3],data_float);
	} 
	else if (argc == 6) {
		if (argv[5][0] == 'l') {
			data_ptr[0] = atof(argv[1]);
			data_ptr[1] = atof(argv[2]);
			data_ptr[2] = atof(argv[3]);
			data_ptr[3] = atof(argv[4]);
			printf(" u8: [%d, %d, %d, %d] <=> float: %f (little endian)\n",
				data_ptr[0],data_ptr[1],data_ptr[2],data_ptr[3],data_float);
		}
		else if (argv[5][0] == 'b') {
			data_ptr[3] = atof(argv[1]);
			data_ptr[2] = atof(argv[2]);
			data_ptr[1] = atof(argv[3]);
			data_ptr[0] = atof(argv[4]);
			printf(" u8: [%d, %d, %d, %d] <=> float: %f (big endian)\n",
				data_ptr[0],data_ptr[1],data_ptr[2],data_ptr[3],data_float);
		}
	}

	return 0;
}


/* --------------------------- end of file ----------------------------- */



