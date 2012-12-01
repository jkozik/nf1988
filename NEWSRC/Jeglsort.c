#include "curses.h"
#ifndef turboc
#include <malloc.h>
#else
#include <malloc.h>
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#ifndef turboc
#include <search.h>
#include <sys/types.h>
#include <direct.h>
#endif
#include <stdlib.h>
#include <sys/stat.h>

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

#include "JSdefs.h"
#include "JSstruct.h"
#include "JSextern.h"

/* Define global variables */
char *recptr[MAXJEINPREC];

/* function templates */
int JEglscmp(char **, char **);
typedef int (*sortFn)(const void*, const void*);

/*
** Sort ifname by account and date.
** Output to ofname.
** Return success or fail (NULL).
*/
char *
JEglsort(ifname,ofname)
char *ifname,*ofname;
{
	FILE *ifp,*ofp;
	int i;
	struct stat sbuf;
	char line[SZLINE];
	char *inprecords;
	char *currecptr;
	char prtstr[80];
	int rec_cnt;
	int isize,totsize;

	totsize=0;
	isize=0;
	rec_cnt=0;

	/* Get the size, inbytes, of the input record */
	if ( stat(ifname,&sbuf) < 0 ){
		JMprtbody("\nJEglsort: stat cannot open input file");
		return(NULL);
	}

	/* Allocate enough memory to read whole file into memory */
   inprecords = (char *)malloc((size_t)sbuf.st_size);
	if (inprecords == NULL) {
		sprintf(prtstr,"\nJEglsort:malloc failed to allocate %d bytes\n",sbuf.st_size);
		JMprtbody(prtstr);
		return(NULL);
	}
	currecptr=inprecords;


	/* Copy input file into memory */
	if ((ifp=fopen(ifname,"r")) == NULL) {
		JMprtbody("\nJEglsort: cannot open input file");
		free(inprecords);
		return(NULL);
	}

	while ( fgets(line,SZLINE,ifp) != NULL) {
		isize=strlen(line);
		if(line[isize-1] == '\n') {
			line[isize-1] = '\0';
			isize--;
		}
		totsize=totsize+isize;
		if (totsize > sbuf.st_size){
			JMprtbody("\nJEglsort: Ran out of memory for input file\n");
			sprintf(prtstr,"\nJEglsort: Allocated %d bytes, read %d bytes\n",sbuf.st_size,totsize);
			JMprtbody(prtstr);
			free(inprecords);
			return(NULL);
		}
		if (rec_cnt+1 >= MAXJEINPREC ) {
			sprintf(prtstr,"\nJEglsort: More than %d input records read\n",MAXJEINPREC);
			JMprtbody(prtstr);
			free(inprecords);
			return(NULL);
		}

		recptr[rec_cnt++] = currecptr;
		strcpy(currecptr,line);
		currecptr = currecptr + isize + 1;
	} /* while */

	/* Input file read-in. Close it. */
   if (fclose(ifp) != (int)NULL){
		JMprtbody("\nJEglsort: cannot close input file");
	}

	/* Sort input 
	**  data stored in as records in recptr[]
	*/
   qsort((void *)recptr, (size_t)rec_cnt, sizeof(char *), (sortFn)JEglscmp);

	/* Read recptr, output to ofname
	*/
	if((ofp=fopen(ofname,"w")) == NULL) {
		JMprtbody("\nJEglsort: cannot open output file");
		free(inprecords);
		return(NULL);
	}

	for (i=0; i<rec_cnt; i++) {
		fputs(recptr[i],ofp);
		fputs("\n",ofp);
	}

	/* CLose output file */
   if (fclose(ofp) != (int)NULL)
		JMprtbody("\nJEglsort: cannot close output file");

	free(inprecords);
	return(ifname);
};

int
JEglscmp(a1,a2)
char **a1,**a2;
{
	int cmp_acct;
	int date_cmp;

	cmp_acct=strncmp(*a1+5,*a2+5,SZACCT);

	if (cmp_acct != 0)
		return(cmp_acct);

	date_cmp = strncmp(*a1,*a2,SZDATE);
	if ( date_cmp != 0)
		return(date_cmp);

	/* All fields equal, retain relative position */
	if (*a1 < *a2)
		return(-1);
	else if (*a1 > *a2)
		return(1);
	else
		return(0);
}
