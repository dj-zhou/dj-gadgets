#pragma once

#include "cli-arguments.h"

#define LINE_MAX_LEN 1000

void create_main_cpp(void);
void create_Makefile(void);
void create_stm32_main_cpp(Stm32Target);
void create_stm32_Makefile(Stm32Target);
void create_CMakeLists_txt(void);
void create_editor_config(void);
void create_clang_format(void);
void create_gitignore(void);
