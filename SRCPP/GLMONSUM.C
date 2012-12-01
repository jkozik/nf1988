#include <stdio.h>
#include <string.h>
#include <ctype.h>
#ifndef turboc
#include <direct.h>
#include <sys/types.h>
#include <search.h>
#endif
#include <stdlib.h>
#include <time.h>

#include <sys/stat.h>

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

/* Define Global Variables */

/* Current Report Level Data */
char curmon[SZDATE];
char curacct[SZACCT+1];
char cura12[SZACCT];
char cura11[SZACCT];

/* Total accumulators */
long totacct[MAXMONCNT];
long tota12[MAXMONCNT];
long tota11[MAXMONCNT];
long grand[MAXMONCNT];
long networth[MAXMONCNT];
long incsum[MAXMONCNT];

/* Indices */
int monidx;
int curmonidx;
int maxmon;

/* Report Level Changed Flags */
jebool head_prt;
jebool mon_chgd;
jebool acct_chgd;
jebool a12_chgd;
jebool a11_chgd;
jebool rept_mode;

/* page and line counters */
int linecnt;
int linesperpg;
int pagecnt;

char line[SZLINE];
struct jefileinp *jefld_ptr;


/* Function templates */
void GLinit();
jebool GLctrlbrk(struct jefileinp *);
void GLsubtotals(struct jefileinp *);
void GLdtl(struct jefileinp *);
void GLpsumline(char *, long *,char *);
void GLaccum(long *, long *);
void GLnewheads();
void GLheadchk();
void GLfinals();

void
main() 
{

/* Setup GL environment */
(void)GLenvsetup();


(void)GLinit();
rept_mode=SUMMARY;

/* Detail Record Processing */
while ( (jefld_ptr=GLjegetnxt(line)) != NULL) {

	(void)GLheadchk();

	if (GLctrlbrk(jefld_ptr) == JETRUE) {
		(void)GLsubtotals(jefld_ptr);
	}

	(void)GLdtl(jefld_ptr);
}

(void) GLfinals();

(void)GLinit();
rept_mode=DETAILED;

/* Detail Record Processing */
while ( (jefld_ptr=GLjegetnxt(line)) != NULL) {

	(void)GLheadchk();

	if (GLctrlbrk(jefld_ptr) == JETRUE) {
		(void)GLsubtotals(jefld_ptr);

		(void)GLheadchk();

		(void)GLnewheads();
	}

	(void)GLdtl(jefld_ptr);
}

(void) GLfinals();

/* Restore working directory */
chdir(cwdstr);

} /* end of main */

void
GLheadchk()
{
	struct tm *newtime;
	long ltime;

	/* if the linecnt is greater than 56, */
	if (linecnt < linesperpg - 10) 
		return;

	/* go to top of form */
	for (; linecnt < linesperpg; linecnt++ ) putchar('\n');
	linecnt = 0;
	pagecnt++;

	/* print heading */
	time(&ltime);
	newtime = localtime(&ltime);
	printf("\n%.24s     * * 19%s Account Summary * *  Page %d\n\n",asctime(newtime),year,pagecnt);
	linecnt = linecnt + 3;
}
	
jebool
GLctrlbrk(jefld)
struct jefileinp *jefld;
{
	/* Check for change in report level, generate subtotals */

	mon_chgd = JEFALSE;
	acct_chgd = JEFALSE;
	a12_chgd = JEFALSE;
	a11_chgd = JEFALSE;

	/* Check for change in 1st acct digit */
	if ( strcmp(jefld->a11,cura11) ) {
		mon_chgd = JETRUE;
		acct_chgd = JETRUE;
		a12_chgd = JETRUE;
		a11_chgd = JETRUE;

	/* Check for change in 2nd acct digit */
	} else if ( strcmp(jefld->a12,cura12) ) {
		mon_chgd = JETRUE;
		acct_chgd = JETRUE;
		a12_chgd = JETRUE;

	/* Check for change in acct */
	} else if ( strcmp(jefld->acct,curacct) ) {
		mon_chgd = JETRUE;
		acct_chgd = JETRUE;

	/* Check for change in month */
	} else if ( strcmp(jefld->mon,curmon) ) {
		mon_chgd = JETRUE;
	}

	/* if any control level changed, mon_chgd=JETRUE */
	return(mon_chgd);
}
void
GLsubtotals(jefld)
struct jefileinp *jefld;
{

	/* Process change in month */
	if (mon_chgd == JETRUE) {
		curmonidx = (jefld->mon[0]-'0')*10 + jefld->mon[1]-'0';
		if (curmonidx < 0 || curmonidx > MAXMONCNT-1) {
			fprintf(stderr,"GLmonsum: Month is found out of range(0-12)\nGLmonsum:%s\n",line);
			JEinthand(1);
		}
		/* Keep track of the largest month read (1-12) */
		if ( curmonidx > maxmon) 
			maxmon = curmonidx;

		strcpy(curmon,jefld->mon);
	}

	/* Process change in account number */
	if (acct_chgd == JETRUE) {
		if (head_prt == JETRUE) {
			(void) GLpsumline(curacct,totacct,CHlookup(curacct));
		}
		/* accumlate totals */
		(void) GLaccum(totacct,tota12);
		strcpy(curacct,jefld->acct);
	}

	/* Process change in first two digits in account number */
	if (a12_chgd == JETRUE) {
		if (head_prt == JETRUE) {
		   (void) GLpsumline(cura12,tota12,CHlookup(cura12));
		}
		/* accumulate totals */
		(void) GLaccum(tota12,tota11);
		strcpy(cura12,jefld->a12);
	}

	/* Process change in first digit in account number */
	if (a11_chgd == JETRUE) {
		if (head_prt == JETRUE) {
		   (void) GLpsumline(cura11,tota11,CHlookup(cura11));
		}
		/* accumulate totals */
		for(monidx=0; monidx<MAXMONCNT; monidx++){
			if (*cura11 < EXPACCT && *cura11 != CAPACCT){
			   networth[monidx] = networth[monidx] + tota11[monidx];
			} else if (*cura11 >= EXPACCT) {
			   incsum[monidx] = incsum[monidx] + tota11[monidx];
			}
		} /* end for */
		
		(void) GLaccum(tota11,grand);
		strcpy(cura11,jefld->a11);
	}

	head_prt = JETRUE;
}

void
GLnewheads()
{
	/* Print out heading for change in first digit in acct (a11) */
	if (a11_chgd == JETRUE) {
		a11_chgd = JEFALSE;
		printf("\n\n%.1s   %-30.30s\n",cura11,CHlookup(cura11));
		linecnt = linecnt + 3;
	}

	/* Print out heading for change in first two digits in acct (a12) */
	if (a12_chgd == JETRUE) {
		a12_chgd = JEFALSE;
		printf("\n%.2s  %-30.30s\n",cura12,CHlookup(cura12));
		linecnt = linecnt + 2;
	}

	/* Print out heading for change in account */
	if (acct_chgd == JETRUE) {
		acct_chgd = JEFALSE;
	}
} /* return GLnewheads */


void
GLinit()
{
int i;

/* clear out accumulaters */
for (i=0; i<MAXMONCNT; i++) {
	totacct[i] = 0;
	tota12[i] = 0;
	tota11[i] = 0;
	grand[i] = 0;
	networth[i] = 0;
	incsum[i] = 0;
}

monidx = 0;
curmonidx = 0;
maxmon = 0;

linecnt=67;
linesperpg=66;
pagecnt=0;

head_prt = JEFALSE;
mon_chgd = JETRUE;
acct_chgd = JETRUE;
a12_chgd = JETRUE;
a11_chgd = JETRUE;

rept_mode=DETAILED;

strcpy(curmon,"");
strcpy(curacct,"");
strcpy(cura12,"");
strcpy(cura11,"");

/* Read in chart of accounts file into array, charttab.
** This array will be queried to validate account numbers.
*/
CHload();

GLjeopen();
}

void
GLdtl(jefld)
struct jefileinp *jefld;
{

	/* find and total detail amount */
	totacct[curmonidx] = totacct[curmonidx] + jefld->amt;

	/* if the account is an expense account keep a special accumulator */
	if (line[GLACCT] >= EXPACCT) {
		totacct[EXPACCUM]  = totacct[EXPACCUM]  + jefld->amt;
	} 

}

void
GLfinals()
{
	char finline[SZLINE];

	/* force subtotals for all report levels */
	strncpy(finline,line,SZDATE);
	strcat(finline,",999,0000");
	strcpy(line,finline);

	/*
	** Force the final total line to print,
	** By causing a control break on account number.
	*/
	jefld_ptr = GLjeparse(line);
	GLctrlbrk(jefld_ptr);
	(void)GLsubtotals(jefld_ptr);

	/* print grand total */
	GLpsumline(" ", grand, "GRAND TOTAL");
	printf("\n");
	linecnt++;

	/* print income summary */
	GLpsumline("89", incsum, "INCOME SUMMARY");

	/* print networth total */
	GLpsumline("49", networth, "NET WORTH");

	/* go to top of form */
	for (; linecnt < linesperpg; linecnt++ ) putchar('\n');
	linecnt = 0;
	pagecnt++;

}

void
GLpsumline(acctstr,totarray,descptr)
char acctstr[SZACCT];
long totarray[MAXMONCNT];
char *descptr;
{
	long amt,ramt;

	/* print total line -
	** 1. print account number
	** 2. print description
	** 3. print rounded integer amount for each month
	** 4. if expense account, print accumulated total and monthly average
	**    columns.
	** 5. if balance sheet account, print each column summed with the
	**    previous columns.
	*/

	if (rept_mode == SUMMARY && strlen(acctstr) == SZACCT)
		return;

	printf("%-3.3s %-25.25s",acctstr,descptr);

	/* print the total columns */
	amt = 0;
	for (monidx=0; monidx<=maxmon; monidx++) {
		if (*acctstr < EXPACCT) {
			amt = amt + totarray[monidx];
		} else {
			amt = totarray[monidx];
		}

		/* round to the nearest integer */
		if (abs((int)(amt%100)) > 49) 
			ramt = amt + 100;
		else
			ramt = amt;

		printf(" %7ld",ramt/100);

	} /* end for */

	/* if expense account */
	if (*acctstr >= EXPACCT) {
		amt = totarray[EXPACCUM];
		if (abs((int)(amt%100)) > 49) amt = amt + 100;
		printf(" %7ld %7ld",amt/100,amt/(maxmon*100));
	}
	printf("\n");
	linecnt++;
}

void
GLaccum(dtlar,totar)
long dtlar[MAXMONCNT],totar[MAXMONCNT];
{
	/* 
	** Accumulate totals:
	** 1.  Add dtlar[i] to totar[i]
	** 2.  Zero dtlar[i]
	** 3.  If expense account add dtlar[EXPACCUM] to totar[EXPACCUM]
	*/
	
	for (monidx=0; monidx<=maxmon; monidx++) {
		totar[monidx] = totar[monidx] + dtlar[monidx];
		dtlar[monidx] = 0;
	}
	if (*curacct >= EXPACCT) {
		totar[EXPACCUM] = totar[EXPACCUM] + dtlar[EXPACCUM];
		dtlar[EXPACCUM] = 0;
	}
}
