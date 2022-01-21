#include "config.h"

#include "cli-arguments.h"
#include "file-create.h"
#include <magic_enum.hpp>

void djfile_version(void) {
#ifdef _GIT_TAG
    printf("Git tag: %s\n", _GIT_TAG);
#endif
}

CreateType cli_get_create_type(int argc, char* argv[]) {
    CreateType type = CreateType::Nothing;
    CLI::App app{ "djfile: a small tool to initialize projects." };
    //  --------
    auto immediate_flags = app.add_option_group("Immediate");
    auto flag_version = immediate_flags->add_flag(
        "-v,--version", "Display the version of this tool");
    auto flag_create_cmake =
        immediate_flags->add_flag("--cmake", "create a CMake project");
    auto flag_create_makefile =
        immediate_flags->add_flag("--makefile", "create a Makefile project");
    auto flag_create_meson =
        immediate_flags->add_flag("--meson", "create a Meson project");
    auto flag_create_stm32 =
        immediate_flags->add_flag("--stm32", "create a STM32 Makefile project");
    immediate_flags->parse_complete_callback([&] {
        if (*flag_version) {
            djfile_version();
            exit(EXIT_SUCCESS);
        }
        if (*flag_create_cmake) {
            type = CreateType::CMake;
        }
        if (*flag_create_makefile) {
            type = CreateType::Makefile;
        }
        if (*flag_create_stm32) {
            type = CreateType::STM32Makefile;
        }
        if (*flag_create_meson) {
            type = CreateType::Meson;
            printf("todo\n");
            exit(EXIT_SUCCESS);
        }
    });
    try {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) {
        return (CreateType)(app.exit(e));
    }
    return type;
}

Stm32Target cli_get_stm32_target(int argc, char* argv[]) {
    ( void )argc;
    ( void )argv;
    Stm32Target target = Stm32Target::Nothing;
    return target;
}
