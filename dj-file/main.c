/***********************************************************
   File Name     : main.c
   Author        : Dingjiang Zhou 
                   Tieling 110, Shanghai, China.
   Create Time   : Tue, Feb. 12th, 2013. 10:54:24 AM
   Last Modified  : Fri, Oct. 23rd, 2015. 09:39:09 AM
   Purpose       : This is a tiny project created by 
                 Dingjiang Zhou.
		    				 To create *.c and *.h files automatically.
							   run the program as:
								   djfile;
									 djfile hello.c;
									 djfile hello.h;
***********************************************************/
#include "config.h"


int main(int argc, char *argv[])
{
	int i;
	int runShell;
	int fileNameLen = 0;
	int vimCmdLen = 0;

/*	printf("Welcome to use the djfile tool!   --Dingjiang Zhou\n\n"); */
	configValueInit(1,1);
			
	/* arguments checking */
	if(argc == 3)
	{
		errArgv();
		return -1;
	}
	if(argc == 2)
	{
		if(((argv[1][0]>='a' && argv[1][0]<='z') 
					|| (argv[1][0]>='A' && argv[1][0]<='Z') 
					|| argv[1][0]=='-')==FALSE)
		{
			errArgv();
			return -1;
		}
	}
  /* -----------------------------------------*/
	/* create the right files */
	if(argc == 1) 									/* vim main.c */
	{
		char vimCmd[] = "vim main.c"; /* need to be main.c */
		createMainC(); 								/* generate main.c and also the Makefile, need to check if the Makefile exists */
		runShell = system(vimCmd);    /* enter into vim mode */
	}
	else if(argc == 2) 							/* with a '-' */
	{
		if(argv[1][0] == '-')
		{
			switch(argv[1][1])
			{
				case 'v':
				case 'V':
					djfileVersion();
					break;
				case 'm':
				case 'M':
					printf("Create multi-file source code...\n");
					break;
				case 'u':
				case 'U':
					djfileUsage();
					break;
				default:
					break;
			}
		}
		else /* example: "djfile hello.c", or "djfile hello.h" */
		{
			/* obtain the length of the vim command */
			fileNameLen = strlen(argv[1]);
			vimCmdLen = 4 + fileNameLen + 1;
			char vimCmd[vimCmdLen];
			/* construct the vim command */
			strcpy(vimCmd,"vim ");
			for(i=4;i<vimCmdLen;i++)
				vimCmd[i]=argv[1][i-4]; /* combined as "vim hello.c" or "vim hello.h" */
			/* if file exists, then modify the "last Modified" iterm and then continue.*/
			if(strcmp("main.c",argv[1]) == 0)
				createMainC();
			else{
				if(argv[1][fileNameLen-1] == 'c')
					createCfile(argv[1]);
				else if(argv[1][fileNameLen-1] =='h')
					createHfile(argv[1]);
			}
			/* vim */
			runShell = system(vimCmd);
		}
	}
  return 0;
}


/* -------------------- end of file --------------------- */



