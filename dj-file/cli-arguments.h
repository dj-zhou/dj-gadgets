#ifndef __CLI_ARGUMENTS_H_
#define __CLI_ARGUMENTS_H_

#include "config.h"

enum class CreateType {
    Nothing = 0,
    CMake,
    Makefile,
    Meson,
    STM32Makefile,
};

void djfile_version(void);
CreateType cli_arguments(int argc, char* argv[]);

#endif  // __CLI_ARGUMENTS_H_
