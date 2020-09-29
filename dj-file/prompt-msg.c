/***********************************************************
   File Name     : promptMsg.c
   Author        : Dingjiang Zhou
                   Boston University, Boston, 02215.
   Create Time   : Thu, Feb. 21st, 2013. 08:34:24 PM
   Last Modified : Thu, Feb. 21st, 2013. 05:27:44 PM
   Purpose       :
***********************************************************/
#include "prompt-msg.h"

void djfile_usage( void ) {
    printf( "Usage:\n" );
    printf(
        "1. djfile          : to create \"src/main.cpp\" and \"Makefile\".\n" );
    printf( "2. djfile -h       : to check how to use djfile in detail.\n" );
    printf( "3. djfile -v       : check the djfile tool version.\n" );
    printf( "4. djfile \"file.c\" : to create or modify  \"file.c\".\n" );
}

void djfile_err_argv( void ) {
    printf( "Error in Arguments.\n" );
    djfile_usage();
}

void djfile_version( void ) {
    printf( "djfile tool by Dingjiang Zhou.\nversion: %d.%d.\n", ver_no_1,
            ver_no_2 );
}
