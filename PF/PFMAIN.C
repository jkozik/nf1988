/*		PFdbmain.c - Data Base Code	*/

#include "string.h"
#include "ctype.h"
#include "stdlib.h"

/*#define WN_DEBUG*/
#include "wfd.h"
#include "wfd_glob.h"

#include "PFdefs.h"
#include "PFstruct.h"
#include "PFextern.h"

#include "signal.h"
#include "io.h"
#include "direct.h"

/*----------------------------------------------------------------------------*/
/* Global Variable  Definitions                                               */
/*----------------------------------------------------------------------------*/
DBFILEID chartid,jetranid,preglid,spreglid,budgetid;
char DBselstr[20];
char cwdstr[SZPATH];
char *froot,*year;
char PFerrln1[80],PFerrln2[80];
struct PFerrs PFerrgdata;


/*----------------------------------------------------------------------------*/
/* Local Funciton Templates                                                   */
/*----------------------------------------------------------------------------*/
DBRET PFinit(void);
DBRET PFpregl(char *jetranf);
void main(void);

void
main(void)
{

	PFinit();

	MDmnproc();
	/*PFpregl("01xx");*/


	PFexit(0);
}

/*----------------------------------------------------------------------------*/
/* PFinit() - Initialize data structures                                      */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         UNKDIR - directory \$F\$YEAR does not exist.                       */
/*         MISSING00 - the file '00' does not exist.                          */
/*         MISSINGCHART - the file 'chart' does not exist.                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/
int
PFinit(void)
{
	char *fn="PFinit";
	char path[SZPATH];

	/* define WFC and error handler */
	init_wfd();
	se_errorfp(PFerrh);
	INIT_MODULE(fn);

	/* clear error handler error message lines */
	*PFerrln1 = '\0';
	*PFerrln2 = '\0';
	memset(&PFerrgdata,0,sizeof(PFerrgdata));

	/*
	** save current working directory 
	*/
	if (getcwd(cwdstr,SZPATH) == NULL) *cwdstr = '\0';

	/* call PFexit() on ^C */
	signal(SIGINT,PFexit);

	/*
	** Read environment variables-
	**  F - root directory of financials
	**  YEAR - current year (e.g. "89")
	** Change to \$F\$YEAR directory
	*/
	if ( (froot=getenv("F")) == NULL) froot = "";
	if ( (year=getenv("YEAR")) == NULL) year = "";
	sprintf(path,"\\%s\\%s",froot,year);
	if (chdir(path) == -1) {
		_wn_err = UNKDIR;
		EXIT_MODULE(fn);
		return(0);
	}

	/*
	** Validate environment:
	** - 'chart' does not exist
	** - '00' does not exist
	*/
	if (access("00",0) == -1) {
		_wn_err = MISSING00;
		EXIT_MODULE(fn);
		return(0);
	}
	if (access("chart",0) == -1) {
		_wn_err = MISSINGCHART;
		EXIT_MODULE(fn);
		return(0);
	}
	
	/* initialize data base handler */
	DBinit();

	/* save current screen */
	sw_popup(ON,&wn0);
	set_wn(&wn0);
	v_rw(DARK_SHADE, v_rwq*v_coq, &wn0);
	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* PFexit() - Exits.  Restores the directory.                                 */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void
PFexit(err_code)
int err_code;
{
	err_code = err_code;
	fprintf(stderr,"\nTerminating ...\n");
	chdir(cwdstr);

	/* restore screen */
	unset_wn(&wn0);
	exit(1);
}

/*----------------------------------------------------------------------------*/
/* PFpregl(jetranf) - Test pregl funciton. Takes jetranf (e.g. 01) and        */
/*         creates 01.pgl and 01.sgl files.                                   */
/*                                                                            */
/* jetranf: File name string pointer to a file of type RLJETRAN.          */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
PFpregl(jetranf)
char *jetranf;
{
	char *fn="PFpregl";
	DBFILEID jetdbid,pgldbid;
	DBFILEID jetranin,jetranout,preglin,preglout,chartin,chartout;
	DBFILEID budgetin,budgetout;
	struct DBjetran *jetranptr,jetranrec;
	struct DBpregl *preglptr,preglrec;
	struct DBchart *chartptr,chartrec;
	struct DBbudget *budgetptr,budgetrec;
	DMacct tempacct;
	long amt;
	int i;
	char pglf[SZPATH];

	INIT_MODULE(fn);

	/* read-in jetranf, say "01" */
	jetdbid = DBopen(RLJETRAN);
	if (DBimport(jetdbid, jetranf) == 0) {
		EXIT_MODULE(fn);
		return(0);
	}

	/* read from 01 and convert to RLPREGL format into 01.pgl */
	pgldbid = DBopen(RLPREGL);
	jetranptr = (struct DBjetran *) DBrdfirst(jetdbid,(DBRECPTR)&jetranrec);
	while (jetranptr!=NULLP) {
		amt = 0;
		for (i=0; i<MAXACCTAMT && *(jetranptr->p[i].acct)!='\0'; i++) {
			memset((char *)&preglrec,0,sizeof(struct DBpregl));
			strcpy(preglrec.mm,jetranptr->mm);
			strcpy(preglrec.dd,jetranptr->dd);
			strcpy(preglrec.desc,jetranptr->desc);
			amt = amt + jetranptr->p[i].amt;
			preglrec.amt = jetranptr->p[i].amt;
			strcpy(preglrec.acct,jetranptr->p[i].acct);
			DBapprec(pgldbid,(DBRECPTR)&preglrec);
		}
		memset((char *)&preglrec,0,sizeof(struct DBpregl));
		strcpy(preglrec.mm,jetranptr->mm);
		strcpy(preglrec.dd,jetranptr->dd);
		strcpy(preglrec.desc,jetranptr->desc);
		preglrec.amt = -amt;
		strcpy(preglrec.acct,jetranptr->cracct);
		DBapprec(pgldbid,(DBRECPTR)&preglrec);

		jetranptr = (struct DBjetran *) DBrdnext(jetdbid,(DBRECPTR)&jetranrec);
	}
	sprintf(pglf,"%s.pgl",jetranf);
	DBexport(pgldbid,pglf);
	DBclose(pgldbid);
	DBclose(jetdbid);


	/* read-in, write-out jetran */
	jetranin = DBopen(RLJETRAN);
	DBimport(jetranin,"01xx");
	jetranout = DBopen(RLJETRAN);
	jetranptr = (struct DBjetran *)DBrdfirst(jetranin,(DBRECPTR)&jetranrec);
	while (jetranptr != NULLP) {
		DBapprec(jetranout, (DBRECPTR) jetranptr);
		jetranptr = (struct DBjetran *) DBrdnext(jetranin,(DBRECPTR)&jetranrec);
	}

	DBexport(jetranout,"01xx.out");
	DBclose(jetranout);
	DBclose(jetranin);

	/* read-in, write-out chart */
	chartin = DBopen(RLCHART);
	DBimport(chartin,"chart");
	chartout = DBopen(RLCHART);
	chartptr = (struct DBchart *)DBrdfirst(chartin,(DBRECPTR)&chartrec);
	while (chartptr != NULLP) {
		DBapprec(chartout, (DBRECPTR) chartptr);
		chartptr = (struct DBchart *) DBrdnext(chartin,(DBRECPTR)&chartrec);
	}

	DBexport(chartout,"chart.out");
	DBclose(chartout);
	DBclose(chartin);

	/* read-in, write-out pregl */
	preglin = DBopen(RLPREGL);
	DBimport(preglin,"01xx.pgl");
	preglout = DBopen(RLPREGL);
	preglptr = (struct DBpregl *)DBrdfirst(preglin,(DBRECPTR)&preglrec);
	while (preglptr != NULLP) {
		DBinsrec(preglout, (DBRECPTR) preglptr);
		preglptr = (struct DBpregl *) DBrdnext(preglin,(DBRECPTR)&preglrec);
	}

	DBexport(preglout,"01xx.pgo");
	DBclose(preglout);
	DBsort(preglin,DBcmpacct);
	DBexport(preglin,"01xx.sgl");
	preglout = DBopen(RLPREGL);
	DBimport(preglout,"01xx.sgl");
	DBmerge(preglin,preglout,DBcmpacct);
	DBexport(preglin,"01xx.mrg");
	DBclose(preglin);

	/* read-in, write-out budget */
	budgetin = DBopen(RLBUDGET);
	DBimport(budgetin,"budget");
	DBexport(budgetin,"budget.out");

	budgetout = DBopen(RLBUDGET);
	budgetptr = (struct DBbudget *)DBrdfirst(budgetin,(DBRECPTR)&budgetrec);
	while (budgetptr != NULLP) {
		DBapprec(budgetout, (DBRECPTR) budgetptr);
		strcpy(tempacct,budgetptr->acctdr);
		strcpy(budgetptr->acctdr,budgetptr->acctcr);
		strcpy(budgetptr->acctcr,tempacct);
		for(i=0; i<12; i++) budgetptr->amt[i] *= -1;
		DBapprec(budgetout, (DBRECPTR) budgetptr);
		budgetptr = (struct DBbudget *)DBrdnext(budgetin,(DBRECPTR)&budgetrec);
	}
	DBsort(budgetout,DBcmpacct);
	DBexport(budgetout,"budget.cr");
	DBclose(budgetout);
	DBclose(budgetin);

	

	EXIT_MODULE(fn);
	return(1);
}
