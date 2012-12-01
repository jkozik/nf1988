#include "curses.h"
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

#include "JSdefs.h"
#include "JSstruct.h"
#include "JSextern.h"


/* Current Report Level Data */
char curmon[SZDATE];
char curacct[SZACCT+1];
char cura12[SZACCT];
char cura11[SZACCT];


/* Total accumulators */
long totmon;
long totmondr;
long totmoncr;
long totacct;
long totacctdr;
long totacctcr;
long tota12;
long tota12dr;
long tota12cr;
long tota11;
long tota11dr;
long tota11cr;
long grand;
long granddr;
long grandcr;

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

int maxmon;
int curmonidx;

FILE *aafp;
struct jefileinp *jefld_ptr;
char line[SZLINE];

/* Function Templates */
static jebool GLctrlbrk(struct jefileinp *);
static void GLinit(void);
static void GLsubtotals(struct jefileinp *);
static void GLprtdtl(struct jefileinp *);
static void GLnewheads(void);
static void GLheadchk(void);
static void GLfinals(void);
static long *car(char *idx_str);
static void prtab2(char *, long,char *,long);

/* content addressable array data structures */
#define SZIDX 5
#define MAXCAR 400
struct CARREC {
	char idx[SZIDX];
	long amt;
};
struct CARREC cartab[MAXCAR];
int carcnt,lastidx;

int
JMaarpt(void)
{

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

return (JESUCCESS);
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
	for (; linecnt < linesperpg; linecnt++ ) fputc('\n',aafp);
	linecnt = 0;
	pagecnt++;

	/* print heading */
	time(&ltime);
	newtime = localtime(&ltime);
	fprintf(aafp,"\n%.24s     * * 19%s Audited Accounts * *  Page %d\n\n",asctime(newtime),year,pagecnt);
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
		curmonidx = (jefld->mon[0]-'0')*10 + jefld->mon[1]-'0';
		if (curmonidx < 0 || curmonidx > MAXMONCNT-1) {
			JMprtbody("aarpt: Month is found out of range(0-12)\n\r");
			JMprtbody(line);
		}
		/* Keep track of the largest month read (1-12) */
		if ( curmonidx > maxmon) 
			maxmon = curmonidx;

		totacct = totacct + totmon;
		totacctdr = totacctdr + totmondr;
		totacctcr = totacctcr + totmoncr;

		if (strcmp(curacct,"121")==0 && curmonidx==7){
			*car("b21") = totacct;
		}
		if (strcmp(curacct,"122")==0 && curmonidx==7){
			*car("b22") = totacct;
		}
		if (strcmp(curacct,"611")==0 && curmonidx==7){
			*car("i11") = totacct;
		}

		monlincnt = 0;
		totmon = 0;
		totmondr = 0;
		totmoncr = 0;
		strcpy(curmon,jefld->mon);
	}

	/* Process change in account number */
	if (acct_chgd == JETRUE) {

		tota12 = tota12 + totacct;
		tota12dr = tota12dr + totacctdr;
		tota12cr = tota12cr + totacctcr;

		*car(curacct) = *car(curacct) + totacct;

		totacct = 0;
		totacctdr = 0;
		totacctcr = 0;

		strcpy(curacct,jefld->acct);
	}

	/* Process change in first two digits in account number */
	if (a12_chgd == JETRUE) {

		tota11 = tota11 + tota12;
		tota11dr = tota11dr + tota12dr;
		tota11cr = tota11cr + tota12cr;

		*car(cura12) = *car(cura12) + tota12;

		tota12 = 0;
		tota12dr = 0;
		tota12cr = 0;
		strcpy(cura12,jefld->a12);
	}

	/* Process change in first digit in account number */
	if (a11_chgd == JETRUE) {

		grand = grand + tota11;
		granddr = granddr + tota11dr;
		grandcr = grandcr + tota11cr;

		*car(cura11) = *car(cura11) + tota11;

		tota11 = 0;
		tota11dr = 0;
		tota11cr = 0;
		strcpy(cura11,jefld->a11);
	}

	head_prt = JETRUE;
}

void
GLnewheads()
{
} /* return GLnewheads */

void
GLinit()
{
/* Read in chart of accounts file into array, charttab.
** This array will be queried to validate account numbers.
*/
	int i;

	wclear(body);						   
	wrefresh(body); 					   
								   
	JMprtbody("aarpt: Starting...\n\r");
								   
	/*							   
	** All output goes to file aa.out.			   
	*/							   
	if ((aafp=fopen("aa.out","w")) == NULL) {
		JMprtbody("aarpt: Output file cannot open\n\r");
	}							   

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
totmondr = 0;
totmoncr = 0;
totacct = 0;
totacctdr = 0;
totacctcr = 0;
tota12 = 0;
tota12dr = 0;
tota12cr = 0;
tota11 = 0;
tota11dr = 0;
tota11cr = 0;
grand = 0;
granddr = 0;
grandcr = 0;
strcpy(curmon,"");
strcpy(curacct,"");
strcpy(cura12,"");
strcpy(cura11,"");
JMwrprtsu(aafp);

maxmon=0;
curmonidx=0;

/* initialize content addressable array elements */
carcnt=0;
lastidx=0;
for (i=0; i<MAXCAR; i++) {
	cartab[i].amt = 0;
	cartab[i].idx[0] = '\0';
}

}

void
GLprtdtl(jefld)
struct jefileinp *jefld;
{
	long lamt;

	/* find and total detail amount */
	lamt = jefld->amt;
	totmon = totmon + lamt;
	if (lamt>0) totmondr = totmondr + lamt;
	else        totmoncr = totmoncr + lamt;

}
#define aadtl(acct1,acct2)	\
	aasdtl(acct1,acct2,CHlookup(acct1))

#define aasdtl(acct1,acct2,acctname)	\
	fprintf(aafp,"%-3.3s/%-3.3s %-30.30s %7ld.%02d %7ld.%02d\n", \
		acct1,acct2,acctname, \
		*car(acct1)/100,abs((int)(*car(acct1)%100)), \
		*car(acct2)/100,abs((int)(*car(acct2)%100)))

#define aacrdtl(acct1,acct2)	\
	if (*car(acct1) != 0 || *car(acct2) != 0) aadtl(acct1,acct2)


void
GLfinals()
{
	void GLsubtotals();
	long lamtc1s1,lamtc1s2;
	long lamtc2s1,lamtc2s2;

	/* force subtotals for all report levels */
	strcpy(line,"9999,999,9999");
	jefld_ptr = GLjeparse(line);
	GLctrlbrk(jefld_ptr);
	(void)GLsubtotals(jefld_ptr);

	fprintf(aafp,"---------------------- SAVINGS ACCOUNTS----------------------\n");
	fprintf(aafp,"ACCOUNT %-30.30s     AMOUNT   INTEREST\n","NAME");

	/* Bank accounts and interest */
	aadtl("101","822");
	aadtl("105","826");
	aadtl("111","823");
	aadtl("112","821");
	aadtl("113","834");
	aadtl("115","824");
	fprintf(aafp,"\n");
	
	/* IRAs */
	aadtl("231","861");
	aadtl("232","862");
	fprintf(aafp,"\n");

	/* BSSPs */
	fprintf(aafp,"        %-30.30s        JPK        CEK\n","");
	if (maxmon > 6) {
		aasdtl("b21","b22","BSSP First 6 Months");
	}
	aasdtl("121","122","YTD BSSP ");
	fprintf(aafp,"\n");

	/* Loan/charge balances and finance charge */
	fprintf(aafp,"-------------------LOANS AND CREDIT CARDS-------------------\n");
	fprintf(aafp,"ACCOUNT %-30.30s     BALANCE   FINANCE\n","NAME");
	aacrdtl("301","671");
	aacrdtl("302","672");
	aacrdtl("303","673");
	aacrdtl("312","674");
	aacrdtl("313","67a");
	aacrdtl("314","679");
	aacrdtl("316","67c");
	aacrdtl("321","67d");
	aacrdtl("322","678");
	aacrdtl("323","67b");
	fprintf(aafp,"\n");
	aacrdtl("404","648");
	aacrdtl("405","622");
	aacrdtl("412","642");
	fprintf(aafp,"\n");

	/* mortgage */
	aacrdtl("42","611");
	aadtl("14","");
	*car("i21") = *car("611") - *car("i11");
	aasdtl("i11","i21","1st 6 / 2nd 6 months interest");
	fprintf(aafp,"\n");

	/* Paycheck */
	fprintf(aafp,"----------------------INCOME AND TAXES----------------------\n");
	fprintf(aafp,"ACCOUNT %-30.30s        JPK        CEK\n","NAME");
	aadtl("801","811");
	aadtl("802","812");
	aadtl("803","813");
	aadtl("804","814");
	aadtl("807","817");
	fprintf(aafp,"\n");

	fprintf(aafp,"----------------------BALANCE SHEET----------------------\n");
	prtab2("ASSETS",0L,"LIABILITIES",0L);
	prtab2("  Cash/Savings",*car("10")+*car("11"),
		"  Credit Cards",*car("3"));
	prtab2("  Investments",*car("12"),"  Loans",
		*car("40")+*car("41"));
	prtab2("  Personal Property",*car("20"),"  Mortgage",*car("42"));
	prtab2("  House",*car("22"),"  Other",*car("43"));
	prtab2("  IRA/401(k)",*car("23"),"  TOTAL",*car("3")+*car("4"));
	lamtc1s1=*car("13");
	lamtc1s1=lamtc1s1+*car("14");
	lamtc1s1=lamtc1s1+*car("21");
	prtab2("  Other",lamtc1s1,"",0L);
	prtab2("  TOTAL",*car("1")+*car("2"),"",0L);

	lamtc1s1=*car("1");
	lamtc1s1=lamtc1s1+*car("2");
	lamtc1s1=lamtc1s1+*car("3");
	lamtc1s1=lamtc1s1+*car("4");
	prtab2("NET WORTH",lamtc1s1,"",0L);
	fprintf(aafp,"\n");

	fprintf(aafp,"----------------------INCOME/EXPENSE----------------------\n");
	prtab2("INCOME",0L,"EXPENSES",0L);
	prtab2("  Gross",*car("801")+*car("811"),"  Housing",
		*car("61"));
	prtab2("  401(k)",*car("807")+*car("817"),"  Transportation",
		*car("62"));
	prtab2("  Interest/Dividend",*car("82")+*car("83"),"  Food/Sundries",
		*car("63"));
	prtab2("  Nontaxable",*car("86"),"  Medical",*car("65"));
	prtab2("  Other",0L,"  Charity",*car("643"));
	lamtc1s1=*car("801");
	lamtc1s1=lamtc1s1+*car("811");
	lamtc1s1=lamtc1s1+*car("807");
	lamtc1s1=lamtc1s1+*car("817");
	lamtc1s1=lamtc1s1+*car("82");
	lamtc1s1=lamtc1s1+*car("83");
	lamtc1s1=lamtc1s1+*car("86");
	prtab2("  TOTAL",lamtc1s1,"  Finance Charges",*car("67"));
	prtab2("",0L,"  Child Care",*car("68"));

	lamtc2s1=*car("61");
	lamtc2s1=lamtc2s1+*car("62");
	lamtc2s1=lamtc2s1+*car("63");
	lamtc2s1=lamtc2s1+*car("65");
	lamtc2s1=lamtc2s1+*car("67");
	lamtc2s1=lamtc2s1+*car("68");
	lamtc2s1=lamtc2s1+*car("643");
	lamtc2s1=*car("6")-lamtc2s1;
	prtab2("",0L,"  Other",lamtc2s1);

	prtab2("PAYROLL TAXES",0L,"TOTAL",*car("6"));
	prtab2("  FWT",*car("812")+*car("802"),"",0L);
	prtab2("  FICA",*car("803")+*car("813"),"VARIABLE EXPENSES",0L); 
	prtab2("  SWT",*car("804")+*car("814"),"  Clothes",*car("70")); 
	lamtc1s2=*car("802");
	lamtc1s2=lamtc1s2+*car("812");
	lamtc1s2=lamtc1s2+*car("803");
	lamtc1s2=lamtc1s2+*car("813");
	lamtc1s2=lamtc1s2+*car("804");
	lamtc1s2=lamtc1s2+*car("814");
	prtab2("  Other",*car("8")-lamtc1s1-lamtc1s2,"  Fun",*car("71"));
	prtab2("  TOTAL",*car("8")-lamtc1s1,"  Gifts",*car("72"));
	prtab2("",0L,"  Household",*car("73"));
	prtab2("NET INCOME",*car("8"),"  Major",*car("74"));
	prtab2("",0L,"  XMAS",*car("76"));
	prtab2("",0L,"  Misc",*car("77"));
	prtab2("",0L,"  Publications",*car("79"));
	lamtc2s2=*car("75");
	lamtc2s2=lamtc2s2+*car("78");
	prtab2("",0L,"  Other",lamtc2s2);
	prtab2("",0L,"  TOTAL",*car("7"));
	lamtc1s1=*car("6");
	lamtc1s1=lamtc1s1+*car("7");
	lamtc1s1=lamtc1s1+*car("8");
	prtab2("CASH FLOW",lamtc1s1,"",0L);

	if (fclose(aafp) == EOF)
		JMprtbody("aarpt: close failed\n\r");

	JMprtbody("aarpt: Done.\n\r");




}

long *
car(idx_str)
char *idx_str;
{
	/*
	** Content addressible array of long int's.
	** Usage:  *car("101") = *car("101") + 1
	** Globals: cartab[], 
	**          lastidx,  -- most recently accessed
	**          carcnt,   -- next available record
	*/

	int i;
	
	/* CAR empty */
	if (carcnt == 0) {
		lastidx = 0;
		carcnt++;
		strncpy(cartab[lastidx].idx,idx_str,SZIDX);
		cartab[lastidx].idx[SZIDX] = '\0';
		cartab[lastidx].amt = 0;
		return(&cartab[lastidx].amt);
	}

	/* check most recently accessed CAR element */
	if (strcmp(cartab[lastidx].idx, idx_str) == 0) {
		return( &cartab[lastidx].amt );
	}

	/* do a linear, non-ordered, search of cartab */
	for (i=0; i<carcnt; i++) {
		if (strcmp(cartab[i].idx,idx_str) == 0) {
			lastidx=i;
			return( &cartab[lastidx].amt );
		}
	}

	/* linear search failed, add new CAR element */
	lastidx = carcnt++;
	if (carcnt >= MAXCAR) {
		fprintf(stderr,"\nJMaarpt: idx_str=%s\n",idx_str);
		fprintf(stderr,"\nJMaarpt: CAR full. Exiting...\n");
		JEinthand();
	}
	strncpy(cartab[lastidx].idx,idx_str,SZIDX);
	cartab[lastidx].idx[SZIDX] = '\0';
	cartab[lastidx].amt = 0;
	return( &cartab[lastidx].amt );
}
void
prtab2(label1,amt1,label2,amt2)
char *label1,*label2;
long amt1,amt2;
{
	/*
	** Print table assistant function. 
	** 1.  print label withing 20 characters.
	** 2.  round long int to nearest whole (assume 2 dec places)
	** 3.  print amt in 7 characters (blank if zero)
	*/

	long lamt1,lamt2;
	lamt1 = ((amt1+50)/100);
	lamt2 = ((amt2+50)/100);

	fprintf(aafp,"%-20.20s",label1);
	if (lamt1 != 0) {
		fprintf (aafp,"%7ld  ",lamt1);
	}
	else {
		fprintf(aafp,"         ");
	}

	fprintf(aafp,"%-20.20s",label2);
	if (lamt2 != 0) {
		fprintf (aafp,"%7ld\n",lamt2);
	}
	else {
		fprintf(aafp,"       \n");
	}
}
