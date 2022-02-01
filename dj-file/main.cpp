#include "cli-arguments.h"
#include "file-create.h"
#include <CLI/CLI.hpp>
#include <magic_enum.hpp>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("run \"%s -h\" to see how to use this tool.\n", argv[0]);
        return 1;
    }
    Arguments_t arguments = cli_parse_arguments(argc, argv);
    if ((long unsigned int)arguments.create_type
        >= (long unsigned int)magic_enum::enum_count<CreateType>()) {
        printf("argument error, exit.\n");
        return 2;
    }
    if (arguments.create_type == CreateType::STM32Makefile) {
    }

    // Stm32Target target = cli_get_stm32_target(argc, argv);
    // ( void )target;
    // printf("target = %d\n", ( int )target);

    switch (arguments.create_type) {
    case CreateType::Nothing:
        exit(EXIT_SUCCESS);
        return 0;
    case CreateType::CMake:
        create_main_cpp();
        create_CMakeLists_txt();
        break;
    case CreateType::Makefile:
        create_main_cpp();
        create_Makefile();
        break;
    case CreateType::Meson:
        create_main_cpp();
        // create_meson_build(); todo
        printf("not implemented yet\n");
        break;
    case CreateType::STM32Makefile:
        create_stm32_main_cpp(arguments.stm32_target);
        create_stm32_config_h(arguments.stm32_target);
        create_stm32_crystal_h(arguments.stm32_target);
        create_stm32_Makefile(arguments.stm32_target);
        break;
    default:
        break;
    }
    create_clang_format();
    create_editor_config();
    create_gitignore();
    return 0;
}
