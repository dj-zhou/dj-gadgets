/***********************************************************
   File Name     : promptMsg.c
   Author        : Dingjiang Zhou
                   Boston University, Boston, 02215.
   Create Time   : Thu, Feb. 21st, 2013. 08:34:24 PM
   Last Modified : Thu, Feb. 21st, 2013. 05:27:44 PM
   Purpose       :
***********************************************************/
#include "prompt-msg.h"

void djfile_usage(void) {
    printf("Usage:djfile [-h] [-v] [-c] [-m]\n");
    printf("  -h: to check how to use djfile in detail.\n");
    printf("  -v: check the djfile tool version.\n");
    printf("  -c: to create a CMake template project.\n");
    printf("  -m: to create a Makefile template project.\n");
}

void djfile_err_argv(void) {
    printf("djfile: arguments error.\n");
    djfile_usage();
}
