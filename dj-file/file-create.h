/***********************************************************
    >   File Name     : time-fetch.h
    >   Author        : Dingjiang Zhou
                        Tieling 110, Shanghai, China.
    >   Create Time   : Tue 12 Feb 2013 10:37:31 PM CST
    >   Last Modified :
    >   Purpose       :
***********************************************************/

#ifndef __FILECREATE_H__
#define __FILECREATE_H__

#include "config.h"

/* macro definitions */
#define LINE_MAX_LEN 1000

/* functions declaration */
void create_main_cpp(void);
void create_cpp_file(char*);
void create_header_file(char*);
void create_Makefile(void);
void create_CMakeLists_txt(void);
void create_editor_config(void);
void create_clang_format(void);

#endif
