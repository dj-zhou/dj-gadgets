
#include "config.h"

int main( int argc, char* argv[] ) {
    int i;
    int run_shell;
    int file_name_len = 0;
    int vim_cmd_len   = 0;

    config_value_init( 1, 2 );

    /* arguments checking */
    if ( argc == 3 ) {
        djfile_err_argv();
        return -1;
    }
    if ( argc == 2 ) {
        if ( ( ( argv[1][0] >= 'a' && argv[1][0] <= 'z' )
               || ( argv[1][0] >= 'A' && argv[1][0] <= 'Z' )
               || argv[1][0] == '-' )
             == FALSE ) {
            djfile_err_argv();
            return -1;
        }
    }
    /* -----------------------------------------*/
    /* create the right files */
    if ( argc == 1 ) /* vim main.cpp */
    {
        create_main_cpp();
        create_Makefile();
        create_clang_format();
    }
    else if ( argc == 2 ) /* with a '-' */
    {
        if ( argv[1][0] == '-' ) {
            switch ( argv[1][1] ) {
            case 'v':
            case 'V':
                djfile_version();
                break;
            case 'u':
            case 'U':
            case 'h':
            case 'H':
                djfile_usage();
                break;
            default:
                break;
            }
        }
        /* example: "djfile hello.cpp", or "djfile hello.h" */
        else {
            /* obtain the length of the vim command */
            file_name_len = strlen( argv[1] );
            vim_cmd_len   = 4 + file_name_len + 1;
            char vimCmd[vim_cmd_len];
            /* construct the vim command */
            strcpy( vimCmd, "vim " );
            for ( i = 4; i < vim_cmd_len; i++ )
                vimCmd[i] = argv[1][i - 4]; /* combined as "vim hello.c" or "vim
                                               hello.h" */
            /* if file exists, then modify the "last Modified" item and then
             * continue.*/
            if ( strcmp( "main.cpp", argv[1] ) == 0 )
                create_main_cpp();
            else {
                if ( argv[1][file_name_len - 1] == 'c' )
                    create_cpp_file( argv[1] );
                else if ( argv[1][file_name_len - 1] == 'h' )
                    create_header_file( argv[1] );
            }
            /* vim */
            run_shell = system( vimCmd );
        }
    }
    return 0;
}

/* -------------------- end of file --------------------- */
