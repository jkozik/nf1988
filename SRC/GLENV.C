#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#ifndef turboc
#include <direct.h>
#include <sys/types.h>
#endif
#include <stdlib.h>
#include <sys/stat.h>
#include <io.h>
#include <errno.h>

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

/* Define global string */
char cwdstr[SZPATH+1];
char *year;
char *froot;
char *months[MONTHS]= 
		{ 
		"00","01","02","03","04","05","06",
		"07","08","09","10","11","12"
		};



void
GLenvsetup() 
{
	struct stat sbuf1;
	struct stat sbuf2;
	char path[SZPATH+1];
	char sglf[SZPATH+1];
	int i,srcm,srcp;

/* Save current working directory
*/
if(getcwd(cwdstr,SZPATH) == NULL)
	cwdstr[0] = '\0';  /* assumed current directory if error */

/* Goto JEinthand on a ^C */
#ifdef turboc
ctrlbrk(JEinthand);
#else
signal(SIGINT,JEinthand);
#endif

/*
**   $F\$YEAR\00.sgl must exist.
*/


froot=getenv("F");
if (froot == NULL) froot="";
year = getenv("YEAR");
if (year == NULL) year="";
fprintf(stderr,"Using environment variables: F='%s', YEAR='%s'\n",froot,year);
strcpy(path,"\\");
strcat(path,froot);
strcat(path,"\\");
strcat(path,year);
if (chdir(path) == -1) {
	fprintf(stderr,"GLenvsetup: The directory %s does not exists\n",path);
	JEinthand(1);
}


if (stat("00.sgl",&sbuf1) != 0 ) {
	fprintf(stderr,"GLenvsetup: WARNING: The file '00.sgl' does not exist\n");
	fprintf(stderr,"GLenvsetup: pregl may need to be run\n");
}
if (stat("chart",&sbuf1) !=0 ) {
	fprintf(stderr,"GLenvsetup: The file 'chart' does not exist\n");
	JEinthand(1);
}

for (i=0; i<MONTHS; i++) {
	/*
	** Skip if '00' does not exist
	*/
	if (access(months[i],0)) {
		continue;
	}
	/*
	** Get modification times for 00 and 00.sgl
	*/
	srcm = stat(months[i],&sbuf1);
	strcpy(sglf,months[i]);
	strcat(sglf,".sgl");
	srcp = stat(sglf,&sbuf2);

	/*
	** Print warning if 00 is newer than 00.sgl
	** or if 00 exists and 00.sgl does not.
	*/
	if (srcp || srcm == 0 && sbuf1.st_mtime > sbuf2.st_mtime ) {
		fprintf(stderr,"GLenv: WARNING: file-%s is newer than %s.sgl\n",months[i],months[i]);
	}
}
}
void
JEinthand(int sig)
{
#if defined(PC_CURSES)
	endwin();
#endif
	sig++;
	fprintf(stderr,"Terminating Processing\n");
	/* Restore working directory */
	chdir(cwdstr);
	exit(1);
   return;
}
