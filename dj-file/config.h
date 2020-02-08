/***********************************************************
    >   File Name     : config.h
    >   Author        : Dingjiang Zhou 
                        Tieling 110, Shanghai, China.
    >   Create Time   : Tue 12 Feb 2013 10:40:20 PM CST
    >   Last Modified : 
    >   Purpose       :
***********************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------- macro defines, used in all files ---------- */
#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE 
    #define FALSE 0
#endif
/* -- global variables declarations, used in all files -- */
int versionNum1;
int versionNum2;


#include "file-create.h"
#include "time-fetch.h"
#include "prompt-msg.h"
#include "funcs.h"

#endif
