/***********************************************************
    >   File Name     : time-fetch.c
    >   Author        : Dingjiang Zhou 
                        Tieling 110, Shanghai, China.
    >   Create Time   : Tue 12 Feb 2013 10:36:24 PM CST
    >   Last Modified : 
    >   Purpose       :
***********************************************************/
#include "file-create.h"


void createMainC(void)
{
	int i;
	char time2Print[]="WWW, MMM. DDth, YYYY. HH:MM:SS AM";
	FILE *F;
	/* need to judge if the file already exist */
	curTimeDate(time2Print);
	if((F = fopen("main.c","r")) == NULL)/* does not exist */
	{
		printf("No <main.c> exists, create one.\n");
	  F = fopen("main.c","a");
		fprintf(F,"/*****************************************************************************************\n");
		fprintf(F,"File Name     : main.c\n");
		fprintf(F,"Author        : Dingjiang Zhou\n");
		fprintf(F,"Email         : zhoudingjiang@gmail.com\n");
		fprintf(F,"Create Time   : %s\n",time2Print);
		fprintf(F,"Last Modified : \n");
		fprintf(F,"Purpose       : \n");
		fprintf(F,"------------------------------------------------------------------------------------------\n");
        fprintf(F,"INPUTS\n\nOUTPUTS\n\n");
		fprintf(F,"*****************************************************************************************/\n");
		fprintf(F,"#include <stdio.h>\n");
		fprintf(F,"#include <stdlib.h>\n");
		fprintf(F,"#include <unistd.h>\n");
		fprintf(F,"#include <stdint.h>\n\n");
		fprintf(F,"int main(int argc, char *argv[])\n");
		fprintf(F,"{\n");
		/* fprintf(F,"\tprintf(\"Hello, Dingjiang!\\n\");\n"); */
		fprintf(F,"\treturn 0;\n");
		fprintf(F,"}\n\n\n");
		fprintf(F,"/* ---------------------------------- end of file ------------------------------------- */\n");
		fprintf(F,"\n\n\n\n\n\n\n\n\n\n\n\n");
		/* the above cannot be generated twice */
		fclose(F);

		/* create the Makefile */
		FILE *F2;
		if((F2 = fopen("Makefile","r")) == NULL)	/* does not exist */
		{
			fileCreateMake();
		}
	}
	else /* files exists, only modify main.c */
	{
		int runShell = 0;
		FILE *F2;
		char lineBuf[lINEmAXnUM];	
		char LastModified[14];
		printf("<main.c> exists, modify the \"Last Modified\" item:\n");
		F2 = fopen("main.ctemp","w"); /* read from F then write to F2 */
		/* read out "Last Modified", then modify the time behind */
		while(fgets(lineBuf,lINEmAXnUM,F)!=NULL)
		{
			/* modify */
			/* locate "Last Modified " */
			for(i=0;i<13;i++) LastModified[i]=lineBuf[i+3];LastModified[13]='\0';
			if(strcmp(LastModified,"Last Modified")==0)
				fprintf(F2,"   Last Modified  : %s\n",time2Print);
			else
				fprintf(F2,"%s",lineBuf);
		}
		fclose(F);
		fclose(F2);
		runShell = system("mv main.ctemp main.c");

		/* create the Makefile */
		/* if exist the Makefile, don't have to generate again */
		if((F2 = fopen("Makefile","r")) != NULL) 	/* file exists */
		{
			printf("<Makefile> exists, exit.\n");
			fclose(F2);
			exit;
		}
		else
		{
			fileCreateMake();
		}
	}
}

void fileCreateMake(void)
{
	printf("No \"Makefile\" exists, create one.\n");
	FILE *F = fopen("Makefile","w");
	fprintf(F,"# Makefile genrated by djfile automatically.\n");
	fprintf(F,"FILENAME=main\n");
	fprintf(F,"CC=g++\n");
	fprintf(F,"LIBS+=\n");
	fprintf(F,"all:\n");
	fprintf(F,"\t$(CC) -c -O4 $(FILENAME).c\n");
	fprintf(F,"\t$(CC) -o $(FILENAME) $(FILENAME).o $(LIBS)\n");
	fprintf(F,"clean:\n");
	fprintf(F,"\trm -f *.o *~ $(FILENAME)\n");
	fprintf(F,"destroy:\n");
	fprintf(F,"\trm -f *.o *~ $(FILENAME) $(FILENAME).c Makefile");
	fclose(F);
}

/* --------------------------------- */
void createCfile(char * fileName)
{
	int i;
	char time2Print[]="WWW, MMM. DDth, YYYY. HH:MM:SS AM";
	int lenName;
	lenName = strlen(fileName);
	char *headerName = (char*)malloc((lenName+1)*sizeof(char));
	for(i=0;i<lenName-1;i++)
		headerName[i] = fileName[i];
	headerName[lenName-1] = 'h';
	headerName[lenName]   = '\0';
	FILE *F;
	curTimeDate(time2Print);
	if((F = fopen(fileName,"r")) == NULL)/* does not exist */
	{
		printf("No <%s> exists, create one.\n",fileName);
	    F = fopen(fileName,"a");
		fprintf(F,"/*****************************************************************************************\n");
		fprintf(F,"File Name     : %s\n",fileName);
		fprintf(F,"Author        : Dingjiang Zhou\n");
		fprintf(F,"Email         : zhoudingjiang@gmail.com\n");
		fprintf(F,"Create Time   : %s\n",time2Print);
		fprintf(F,"Last Modified : \n");
		fprintf(F,"Purpose       : \n");
		fprintf(F,"------------------------------------------------------------------------------------------\n");
        fprintf(F,"INPUTS\n\nOUTPUTS\n\n");
		fprintf(F,"*****************************************************************************************/\n");
		fprintf(F,"#include \"%s\"\n\n",headerName);
		fprintf(F,"int fncs(void)\n");
		fprintf(F,"{\n");
		/* fprintf(F,"\tprintf(\"Hello, Dingjiang!\\n\");\n"); */
		fprintf(F,"\treturn 0;\n");
		fprintf(F,"}\n\n\n");
		fprintf(F,"/* ---------------------------------- end of file ------------------------------------- */\n");
		fprintf(F,"\n\n\n\n\n\n\n\n\n\n\n\n");
		/* the above cannot be generated twice */
		fclose(F);
	}
	else /* files exists */
	{
		int runShell = 0;
		
		int i;
		FILE *F2;
		char lineBuf[lINEmAXnUM];	
		char LastModified[14];
		
		char tempFileName[lenName+5];
		strcpy(tempFileName, fileName);
		tempFileName[lenName]='t';
		tempFileName[lenName+1]='e';
		tempFileName[lenName+2]='m';
		tempFileName[lenName+3]='p';
		tempFileName[lenName+4]='\0';
		printf("<%s> exists, modify the \"Last Modified\" item:\n",fileName);
		F2 = fopen(tempFileName,"w"); /* read from F then write to F2 */
		/* read out "Last Modified", then modify the time behind */
		while(fgets(lineBuf,lINEmAXnUM,F)!=NULL)
		{
			/* modify */
			/* locate "Last Modified " */
			for(i=0;i<13;i++) LastModified[i]=lineBuf[i+3];LastModified[13]='\0';
			if(strcmp(LastModified,"Last Modified")==0)
			{
				fprintf(F2, "   Last Modified  : %s\n",time2Print);
			}
			else
				fprintf(F2,"%s",lineBuf);
		}
		fclose(F);
		fclose(F2);
		
		/* to form the mv command */
		int sysCmdLen;
		sysCmdLen = 9 + 2*lenName;
 		char sysCmdVim[sysCmdLen];

		strcpy(sysCmdVim,"mv ");
		
		for(i=3;i<3+lenName;i++)
		{
			sysCmdVim[i]=fileName[i-3];
		}
		
		sysCmdVim[lenName+3]='t';
		sysCmdVim[lenName+4]='e';
		sysCmdVim[lenName+5]='m';
		sysCmdVim[lenName+6]='p';
		sysCmdVim[lenName+7]=' ';

		for(i=lenName+8;i<2*lenName+8;i++)
			sysCmdVim[i]=fileName[i-lenName-8];
		sysCmdVim[sysCmdLen]='\0';
		
		/* run the cmd: mv hello.ctemp hello.c */
		runShell = system(sysCmdVim);
	}
}

/* --------------------------------- */
void createHfile(char * fileName)
{
	int i;
	char time2Print[]="WWW, MMM. DDth, YYYY. HH:MM:SS AM";
	int lenName;
	lenName = strlen(fileName);
	/* convert the low case name to captical name */
	char *headerNameCap = (char*)malloc((lenName+1)*sizeof(char));
	for(i=0;i<lenName;i++){
		if(fileName[i] >= 'a' && fileName[i] <= 'z')
			headerNameCap[i] = fileName[i] - 32;
		else if(fileName[i] >= 'A' && fileName[i] <= 'Z')
			headerNameCap[i] = fileName[i];
		else if(fileName[i] == '.')
			headerNameCap[i] = '_';
	}
	headerNameCap[lenName+1] = '\0'; /* the end of a string */
	/* creat the file */
	FILE *F;
	curTimeDate(time2Print);
	if((F = fopen(fileName,"r")) == NULL)/* does not exist */
	{
		printf("No <%s> exists, create one.\n",fileName);
	  F = fopen(fileName,"a");
		fprintf(F,"/*****************************************************************************************\n");
		fprintf(F,"File Name     : %s\n",fileName);
		fprintf(F,"Author        : Dingjiang Zhou\n");
		fprintf(F,"Email         : zhoudingjiang@gmail.com\n");
		fprintf(F,"Create Time   : %s\n",time2Print);
		fprintf(F,"Last Modified : \n");
		fprintf(F,"Purpose       : \n");
		fprintf(F,"------------------------------------------------------------------------------------------\n");
        fprintf(F,"INPUTS\n\nOUTPUTS\n\n");
		fprintf(F,"*****************************************************************************************/\n");
		fprintf(F,"#ifndef __%s__\n",headerNameCap);
		fprintf(F,"#define __%s__\n\n",headerNameCap);
		fprintf(F,"#include <stdio.h>\n");
		fprintf(F,"#include <stdlib.h>\n");
		fprintf(F,"#include <unistd.h>\n");
		fprintf(F,"#include <stdint.h>\n\n");
		fprintf(F,"/* typedef struct{\n\n}; */\n\n\n");
		fprintf(F,"/* variables declaration */\n\n\n");
		fprintf(F,"/* functions declaration */\n\n\n");
		fprintf(F,"#endif\n\n\n");
		fprintf(F,"/* ---------------------------------- end of file ------------------------------------- */\n");
		fprintf(F,"\n\n\n\n\n\n\n\n\n\n\n\n");
		/* the above cannot be generated twice */
		fclose(F);
	}
	else /* files exists */
	{
		int runShell = 0;
		
		int i;
		FILE *F2;
		char lineBuf[lINEmAXnUM];	
		char LastModified[14];
		
		char tempFileName[lenName+5];
		strcpy(tempFileName, fileName);
		tempFileName[lenName]   = 't';
		tempFileName[lenName+1] = 'e';
		tempFileName[lenName+2] = 'm';
		tempFileName[lenName+3] = 'p';
		tempFileName[lenName+4] = '\0';
		printf("<%s> exists, modify the \"Last Modified\" item:\n",fileName);
		F2 = fopen(tempFileName,"w"); /* read from F then write to F2 */
		/* read out "Last Modified", then modify the time behind */
		while(fgets(lineBuf,lINEmAXnUM,F)!=NULL)
		{
			/* modify */
			/* locate "Last Modified " */
			for(i=0;i<13;i++) LastModified[i]=lineBuf[i+3];LastModified[13]='\0';
			if(strcmp(LastModified,"Last Modified")==0)
			{
				fprintf(F2, "   Last Modified  : %s\n",time2Print);
			}
			else
				fprintf(F2,"%s",lineBuf);
		}
		fclose(F);
		fclose(F2);
		
		/* to form the mv command */
		int sysCmdLen;
		sysCmdLen = 9 + 2*lenName;
 		char sysCmdVim[sysCmdLen];

		strcpy(sysCmdVim,"mv ");
		
		for(i=3;i<3+lenName;i++)
		{
			sysCmdVim[i]=fileName[i-3];
		}
		
		sysCmdVim[lenName+3]='t';
		sysCmdVim[lenName+4]='e';
		sysCmdVim[lenName+5]='m';
		sysCmdVim[lenName+6]='p';
		sysCmdVim[lenName+7]=' ';

		for(i=lenName+8;i<2*lenName+8;i++)
			sysCmdVim[i]=fileName[i-lenName-8];
		sysCmdVim[sysCmdLen]='\0';
		
		/* run the cmd: mv hello.ctemp hello.c */
		runShell = system(sysCmdVim);
	}
}
/* -------------------- end of file --------------------- */
