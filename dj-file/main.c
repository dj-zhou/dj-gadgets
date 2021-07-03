
#include "config.h"
#include <unistd.h>

enum Methods {
    Use_Makefile   = 1,
    Use_CMakeLists = 2,
};

enum Methods method;

int main(int argc, char* argv[]) {

    config_value_init(1, 4);

    if (argc < 2) {
        djfile_err_argv();
        return 1;
    }
    int opt;
    while ((opt = getopt(argc, argv, "cmvh")) != -1) {
        switch (opt) {
        case 'c':
            method = Use_CMakeLists;
            break;
        case 'm':
            method = Use_Makefile;
            break;
        case 'v':
            djfile_version();
            return 0;
        case 'h':
            djfile_usage();
            return 0;
        default:
            return 2;
        }
    }

    create_main_cpp();
    if (method == Use_Makefile) {
        create_Makefile();
    }
    else if (method == Use_CMakeLists) {
        create_CMakeLists_txt();
    }
    create_clang_format();
    return 0;
}
