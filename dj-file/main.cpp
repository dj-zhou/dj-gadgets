#include "cli-arguments.h"
#include "config.h"
#include <CLI/CLI.hpp>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("run \"%s -h\" to see how to use this tool.\n", argv[0]);
        return 1;
    }
    CreateType type = cli_arguments(argc, argv);
    switch (type) {
    case CreateType::Nothing:
        exit(EXIT_SUCCESS);
        return 0;
    case CreateType::Makefile:
        create_Makefile();
        break;
    case CreateType::CMake:
        create_CMakeLists_txt();
        break;
    case CreateType::Meson:
        printf("not implemented yet\n");
        break;
    default:
        break;
    }
    create_main_cpp();
    create_clang_format();
    create_editor_config();
    create_gitignore();
    return 0;
}
