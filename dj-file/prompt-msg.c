/***********************************************************
   File Name     : promptMsg.c
   Author        : Dingjiang Zhou 
                   Boston University, Boston, 02215.
   Create Time   : Thu, Feb. 21st, 2013. 08:34:24 PM
   Last Modified : Thu, Feb. 21st, 2013. 05:27:44 PM
   Purpose       : 
***********************************************************/
#include "prompt-msg.h"


void djfileUsage(void)
{
	printf("Usage:\n");
	printf("1. djfile          : to create <main.c> and <Makefile>. (done)\n");
	printf("2. djfile -m       : to generate a multi-file c source code with:\n");
	printf("                     <main.c>, <config.h>, <funcs.c>, <funcs.h> and <Makefile>.\n");
	printf("3. djfile -u       : to check how to use djfile in detail.\n"); /* not added */
	printf("4. djfile -v       : check the djfile tool version. (done)\n"); 
	printf("5. djfile <file.c> : to create or modify <file.c>, and also generate <file.h>.\n");
}

void errArgv(void)
{
	printf("Error in Arguments.\n");
	djfileUsage();
}

void djfileVersion(void)
{
	printf("djfile tool by Dingjiang Zhou.\nversion: %d.%d.\n",versionNum1,versionNum2);
}

/* -------------------- end of file --------------------- */



