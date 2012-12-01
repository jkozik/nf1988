#include <stdio.h>
#include <string.h>
#include <ctype.h>
#ifndef turboc
#include <search.h>
#include <direct.h>
#include <sys/types.h>
#endif
#include <stdlib.h>
#include <time.h>

#include <sys/stat.h>

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"


/* Current Report Level Data */
char curmon[SZDATE];
char curacct[SZACCT+1];
char cura12[SZACCT];
char cura11[SZACCT];

/* Total accumulators */
long totmon;
long totacct;
long tota12;
long tota11;
long grand;

/* Report Level Changed Flags */
jebool head_prt;
jebool mon_chgd;
jebool acct_chgd;
jebool a12_chgd;
jebool a11_chgd;

/* page and line counters */
int monlincnt;
int linecnt;
int linesperpg;
int pagecnt;

struct jefileinp *jefld_ptr;
char line[SZLINE];

/* Function Templates */
jebool GLctrlbrk(struct jefileinp *);
void GLinit();
void GLsubtotals(struct jefileinp *);
void GLprtdtl(struct jefileinp *);
void GLnewheads(),GLheadchk(),GLfinals();

void
main()
{

/* Setup GL environment */
(void)GLenvsetup();

(void)GLinit();

/* Detail Record Processing */
while ( (jefld_ptr=GLjegetnxt(line)) != NULL) {

	(void)GLheadchk();

	if (GLctrlbrk(jefld_ptr) == JETRUE) {
		(void)GLsubtotals(jefld_ptr);

		(void)GLheadchk();

		(void)GLnewheads();
	}
	
	(void)GLprtdtl(jefld_ptr);
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
	printf("\n%.24s     * * 19%s Account Detail * *  Page %d\n\n",asctime(newtime),year,pagecnt);
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

	/* If any level changes, mon_chgd = JETRUE */
	return(mon_chgd);

}

void
GLsubtotals(jefld)
struct jefileinp *jefld;
{
	/* Process change in month */
	if (mon_chgd == JETRUE) {
		if (head_prt == JETRUE && monlincnt>0) {
		   printf("    TOT %s  %7ld.%02d*\n",curmon,totmon/100,abs((int)(totmon%100)));
		   linecnt++;
		}
		monlincnt = 0;
		if (*curacct >= EXPACCT || acct_chgd == JETRUE) {
			totacct = totacct + totmon;
			totmon = 0;
		}
		strcpy(curmon,jefld->mon);
	}

	/* Process change in account number */
	if (acct_chgd == JETRUE) {
		if (head_prt == JETRUE) {
		   printf("%.3s TOTAL %-30.30s %7ld.%02d**\n",curacct,CHlookup(curacct),totacct/100,abs((int)(totacct%100)));
		   linecnt++;
		}
		tota12 = tota12 + totacct;
		totacct = 0;
		strcpy(curacct,jefld->acct);
	}

	/* Process change in first two digits in account number */
	if (a12_chgd == JETRUE) {
		if (head_prt == JETRUE) {
		   printf("%.2s  TOTAL %-30.30s %7ld.%02d***\n",cura12,CHlookup(cura12),tota12/100,abs((int)(tota12%100)));
		   linecnt++;
		}
		tota11 = tota11 + tota12;
		tota12 = 0;
		strcpy(cura12,jefld->a12);
	}

	/* Process change in first digit in account number */
	if (a11_chgd == JETRUE) {
		if (head_prt == JETRUE) {
		   printf("%.1s   TOTAL %-30.30s %7ld.%02d****\n",cura11,CHlookup(cura11),tota11/100,abs((int)(tota11%100)));
		   linecnt++;
		}
		grand = grand + tota11;
		tota11 = 0;
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
		printf("%.3s %-30.30s\n",curacct,CHlookup(curacct));
		linecnt++;
	}
} /* return GLnewheads */


void
GLinit()
{
/* Read in chart of accounts file into array, charttab.
** This array will be queried to validate account numbers.
*/
CHload();

GLjeopen();
linecnt=67;
linesperpg=66;
pagecnt=0;
head_prt = JEFALSE;
mon_chgd = JETRUE;
acct_chgd = JETRUE;
a12_chgd = JETRUE;
a11_chgd = JETRUE;
monlincnt = 0;
totmon = 0;
totacct = 0;
tota12 = 0;
tota11 = 0;
grand = 0;
strcpy(curmon,"");
strcpy(curacct,"");
strcpy(cura12,"");
strcpy(cura11,"");

}

void
GLprtdtl(jefld)
struct jefileinp *jefld;
{
	char day[SZDATE];
   char *desc;
	long lamt;

	/* find and total detail amount */
	lamt = jefld->amt;
	monlincnt++;
	totmon = totmon + lamt;

	if (!strcmp(curacct,"101") || !strcmp(curacct,"104"))
		return;


	/* Get string with day */
	strcpy(day,jefld->date+SZMON);

	/* Get description */
	desc = jefld->desc;

	/* Print detail line */
	printf("    %s/%s   %7ld.%02d %-30.30s\n",curmon,day,lamt/100,abs((int)(lamt%100)),desc);
	linecnt++;

}

void
GLfinals()
{
	void GLsubtotals();

	/* force subtotals for all report levels */
	strcpy(line,"9999,999,9999");
	jefld_ptr = GLjeparse(line);
	GLctrlbrk(jefld_ptr);
	(void)GLsubtotals(jefld_ptr);

	/* print grand total */
	printf("    %-30.30s       %7ld.%02d****\n","GRAND TOTAL",grand/100,abs((int)(grand%100)));
}
