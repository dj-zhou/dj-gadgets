#ifndef __FILE_CREATE_H__
#define __FILE_CREATE_H__

#include "config.h"

#define LINE_MAX_LEN 1000

void create_main_cpp(void);
void create_Makefile(void);
void create_Stm32_Makefile(const char*);
void create_CMakeLists_txt(void);
void create_editor_config(void);
void create_clang_format(void);
void create_gitignore(void);

#endif  // __FILE_CREATE_H__
