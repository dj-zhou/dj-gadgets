#pragma once

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

typedef struct {
    CreateType create_type;
    Stm32Target stm32_target;
} Arguments_t;

void djfile_version(void);
Arguments_t cli_parse_arguments(int argc, char* argv[]);
