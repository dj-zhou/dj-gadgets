#include "cli-arguments.h"
#include "file-create.h"
#include <magic_enum.hpp>

void djfile_version(void) {
#ifdef _GIT_TAG
    printf("Git tag: %s\n", _GIT_TAG);
#endif
}

Arguments_t cli_parse_arguments(int argc, char* argv[]) {
    CLI::App app{ "dj-file: a small tool to initialize projects." };
    Arguments_t arguments;
    //  --------
    arguments.create_type = CreateType::Nothing;
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
            arguments.create_type = CreateType::CMake;
        }
        if (*flag_create_makefile) {
            arguments.create_type = CreateType::Makefile;
        }
        if (*flag_create_stm32) {
            arguments.create_type = CreateType::STM32Makefile;
        }
        if (*flag_create_meson) {
            arguments.create_type = CreateType::Meson;
            printf("todo\n");
            exit(EXIT_SUCCESS);
        }
    });
    //  --------
    std::string target_str;
    app.add_option("-t,--target", target_str, "target (for --stm32)");

    try {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) {
        return arguments;
    }
    //  --------
    arguments.stm32_target = Stm32Target::Nothing;
    if (target_str == "f030r8") {
        arguments.stm32_target = Stm32Target::f030r8;
    }
    else if (target_str == "f103rb") {
        arguments.stm32_target = Stm32Target::f103rb;
    }
    else if (target_str == "f107xc") {
        arguments.stm32_target = Stm32Target::f107xc;
    }
    else if (target_str == "f303re") {
        arguments.stm32_target = Stm32Target::f303re;
    }
    else if (target_str == "f407vg") {
        arguments.stm32_target = Stm32Target::f407vg;
    }
    else if (target_str == "f407zg") {
        arguments.stm32_target = Stm32Target::f407zg;
    }
    else if (target_str == "f427vi") {
        arguments.stm32_target = Stm32Target::f427vi;
    }
    else if (target_str == "f746zg") {
        arguments.stm32_target = Stm32Target::f746zg;
    }
    else if (target_str == "f767zi") {
        arguments.stm32_target = Stm32Target::f767zi;
    }
    else if (target_str == "h750vb") {
        arguments.stm32_target = Stm32Target::h750vb;
    }

    return arguments;
}
