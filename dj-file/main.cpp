#include "cli-arguments.h"
#include "config.h"
#include <CLI/CLI.hpp>
#include <magic_enum.hpp>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("run \"%s -h\" to see how to use this tool.\n", argv[0]);
        return 1;
    }
    CreateType type = cli_get_create_type(argc, argv);
    if (( long unsigned int )type
        >= ( long unsigned int )magic_enum::enum_count<CreateType>()) {
        printf("argument error, exit.\n");
        return 2;
    }
    if (type == CreateType::STM32Makefile) {
    }

    switch (type) {
    case CreateType::Nothing:
        exit(EXIT_SUCCESS);
        return 0;
    case CreateType::CMake:
        create_CMakeLists_txt();
        break;
    case CreateType::Makefile:
        create_Makefile();
        break;
    case CreateType::Meson:
        printf("not implemented yet\n");
        break;
    case CreateType::STM32Makefile:
        create_Stm32_Makefile(argv[2]);
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
