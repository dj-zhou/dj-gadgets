#ifndef __CLI_ARGUMENTS_H_
#define __CLI_ARGUMENTS_H_

#include "config.h"
#include <CLI/CLI.hpp>

enum class CreateType {
    Nothing = 0,
    CMake,
    Makefile,
    Meson,
    STM32Makefile,
};

enum class Stm32Target {
    Nothing = 0,
    f030r8,
    f103rb,
    f107xc,
    f303re,
    f407vg,
    f407zg,
    f427vi,
    f746zg,
    f767zi,
    h750vb,
};

void djfile_version(void);
CreateType cli_get_create_type(int argc, char* argv[]);
Stm32Target cli_get_stm32_target(int argc, char* argv[]);

#endif  // __CLI_ARGUMENTS_H_
