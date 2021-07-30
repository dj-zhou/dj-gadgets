
#include "config.h"
#include <CLI/CLI.hpp>
#include <unistd.h>

enum Methods {
    Use_Makefile   = 1,
    Use_CMakeLists = 2,
};

enum Methods method;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        djfile_err_argv();
        return 1;
    }
    int opt;
    while ((opt = getopt(argc, argv, "cmh")) != -1) {
        switch (opt) {
        case 'c':
            method = Use_CMakeLists;
            break;
        case 'm':
            method = Use_Makefile;
            break;
        case 'h':
            djfile_usage();
            return 0;
        default:
            return 2;
        }
    }

    create_main_cpp();
    switch (method) {
    case Use_Makefile:
        create_Makefile();
        break;
    case Use_CMakeLists:
        create_CMakeLists_txt();
        break;
    default:
        break;
    }
    create_clang_format();
    create_editor_config();
    create_gitignore();
    return 0;
}
