#ifndef turboc
#include <malloc.h>
#else
#include <alloc.h>
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


/* Define global variables */
struct GTrec {
	char acct[SZACCT+1];
	struct GTrec *a11;
	struct GTrec *a12;
	struct {
		long cur;
		long ytd;
	} mamt[MONTHS];
	struct {
		long cur;
		long ytd;
	} qamt[4];
};
struct GTrec *GTtab;
struct GTrec *GTptr,*networth,*incsum;
int GTrec_cnt;


/* function templates */
int GTinit();
int GTload(char *yearstr);
int GTsave(char *yearstr);
void GTtally(int month, char *acct, long amt);
void GTsgl(char *sglfile);
int GTtabchk(struct GTrec *GTtab);


int
GTload(yearstr)
char *yearstr;
{
	/*
	** Load totals file for the year, yearstr.
	** Allocate an array, GTtab, to load in the file.
	*/

	struct GTrec *GTtab,*GTptr;
	FILE *GTfp;
	char GTtotfn[SZPATH];
	char line[SZLINE];

	/*
	** Initialize GTtab data stucture
	*/
	GTinit();

	/*
	** Try to open totals file, $F/totals/$YEAR
	*/
	strcpy(GTtotfn,"\\")
	strcat(GTtotfn,froot);
	strcat(GTtotfn,"\\totals\\");
	strcat(GTtotfn,year);

	if ( stat(GTtotfn,4) != 0) {
		/* totals file not found */
		for (i=0; i<MONTHS; i++) {
			GTsgl(months[i]);
		}
		return;
	} 

	/* totals file found, read it in */
		
	if ( (GTfp=fopen(GTtotfn,"r")) == NULL) {
		fprintf(stderr,"GLtotals: Cannot open %s\n",GTtotfn);
		fprintf(stderr,"GLtotals: cannot continue...\n");
		JEinthand();
	}

	/*
	** We opened totals file.  Read in records of following layout-
	**  101,"...desc...",amt00,ytd00,amt01,ytd01,...,ytd12
	** Check for sorted order of account numbers.
	** Missing or NULL amounts are assumed 0.
	** Amounts are positional; trailing commas can be omitted.
	** Do not bother storing the description.
	*/
	while (fgets(line,sizeof(line),GTfp) != (char *)NULL) {
	}
	if (fclose(GTfp) == EOF) {
		/* this should never happen */
		fprintf(stderr,"GLtotals: Cannot close %s\n", GTtotfn);
		JEinthand();
	}
}
void
GTinit()
{
	/*
	** Allocate an array in memory with the same record
	** count as 'chart', chrec_cnt.
	*/
	GTtab = (struct GTrec *) malloc(chrec_cnt*sizeof(struct GTrec)+5);
	if (GTtab == NULL) {
		/*  not enough memory !!?! */
		fprintf(stderr,"GLtotal: cannot allocate %d bytes for GTtab[]\n",chrec_cnt*sizeof(struct GTrec) + 5);
		fprintf(stderr,"GLtotal: cannot continue, exiting...\n");
		JEinthand();
	}

	/*
	** Initialize GTtab array
	*/
	for (GTptr=GTtab; GTptr < &GTtab[chrec_cnt]; GTptr++) {
		GTptr->acct = '\0';
		GTptr->a11 = (struct GTrec *)NULL;
		GTptr->a12 = (struct GTrec *)NULL;
		for (i=0; i<MONTHS; i++) {
			GTptr->mamt[i].cur = 0;
			GTptr->mamt[i].ytd = 0;
		}
		for (i=0; i<4; i++) {
			GTptr->qamt[i].cur = 0;
			GTptr->qamt[i].ytd = 0;
		}
	}
	GTrec_cnt = 0;
}
