/*		PFdb.c - Data Base Code	*/

#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "malloc.h"
#include "stdio.h"
#include "wfd.h"
#include "PFdefs.h"
#include "PFstruct.h"
#include "PFextern.h"

/*----------------------------------------------------------------------------*/
/* Private Data Base Structures                                               */
/*----------------------------------------------------------------------------*/
struct reldesc {
	char *name;
	int maxlines;
	int maxcols;
	DBRET (*importfcn)();
	DBRET (*exportfcn)();
	int struct_size;
};

struct dbfile {
	RELTYPE rel_no;
	MFILEPTR actmfp;
	MFILEPTR tempmfp;
	BOOL modified;
	SELECTRET (*selfcn)();
	int currow;
};

struct dmdesc {
	char *name;
	int minlen;
	int maxlen;
	char pic;
};


/*----------------------------------------------------------------------------*/
/* Private DB Macros                                                          */
/*----------------------------------------------------------------------------*/
#define val_dbfid(fn) if(dbfid<1 || dbfid>=MAXDBFILE) { \
			_wn_err=BADDBFID; \
			EXIT_MODULE(fn); \
			return(0); \
			}

/*----------------------------------------------------------------------------*/
/* Private DB Function Templates                                              */
/*----------------------------------------------------------------------------*/
SELECTRET (*selfcn)(struct dbfile *, DBRECPTR);

DBRET (*importfcn)(DBRECPTR output, char *input);
DBRET DBimpjetran(DBRECPTR output, char *input);
DBRET DBimpchart(DBRECPTR output, char *input);
DBRET DBimppregl(DBRECPTR output, char *input);
DBRET DBimpbudget(DBRECPTR output, char *input);

DBRET (*exportfcn)(char *output,  DBRECPTR input);
DBRET DBexpjetran(char *output,  DBRECPTR input);
DBRET DBexpchart(char *output,  DBRECPTR input);
DBRET DBexppregl(char *output,  DBRECPTR input);
DBRET DBexpbudget(char *output,  DBRECPTR input);



DBRET DBdmconv(DMTYPE domain,DMPTR outp,char **input,char *delimp);
DBRET DBdmtostr(DMTYPE domain,char *output,DMPTR input);
SELECTRET DBfindacct(struct dbfile *dbfptr, DBRECPTR dbrecptr);

/*----------------------------------------------------------------------------*/
/* Private Global Variables                                                   */
/*----------------------------------------------------------------------------*/
DBFILEID DBcmprel_no;

#define MAXDBFILE 8
struct dbfile dbfiletab[MAXDBFILE];

#define MAXREL 5
struct reldesc reldesctab[MAXREL] = {
	{"Undefined",0,0,NULLFP,NULLFP,0},
	{"JETRAN",200,255,DBimpjetran,DBexpjetran,sizeof(struct DBjetran)},
	{"CHART",300,80,DBimpchart,DBexpchart,sizeof(struct DBchart)},
	{"PREGL",400,80,DBimppregl,DBexppregl,sizeof(struct DBpregl)},
	{"BUDGET",400,175,DBimpbudget,DBexpbudget,sizeof(struct DBbudget)}
};

#define MAXDMDESCTAB 9
struct dmdesc dmdesctab[MAXDMDESCTAB] = {
	{"Undefined",0,0,' '},
	{"Account No.",3,3,'X'},
	{"Amount",0,8,'9'},
	{"Description",0,30,'X'},
	{"Month",2,2,'9'},
	{"Day",2,2,'9'},
	{"Old Account",1,3,'A'},
	{"General Account",1,3,'A'},
	{"Budget Amount",0,8,'9'}
};


/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                   PUBLIC DATA BASE FUNCITONS                               */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* DBinit() - Initialize data base structures                                 */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBinit(void)
{
	char *fn="DBinit";
	int i;

	INIT_MODULE(fn);
	for (i=0; i<MAXDBFILE; i++) {
		dbfiletab[i].rel_no = 0;
		dbfiletab[i].actmfp = NULLP; 
		dbfiletab[i].tempmfp = NULLP; 
		dbfiletab[i].modified = NO; 
		dbfiletab[i].selfcn = NULLFP; 
		dbfiletab[i].currow = 0;
	}

	*DBselstr = '\0';
	DBcmprel_no = 0;

	/* global db file ids */
	chartid = 0;
	jetranid = 0;
	preglid = 0;
	spreglid = 0;
	budgetid = 0;


	/* open chart for validating acct fields on importing */
	chartid = DBopen(RLCHART);
	DBimport(chartid,"chart");
	DBselect(chartid,DBfindacct);

	EXIT_MODULE(fn);
	return(1);
}


/*----------------------------------------------------------------------------*/
/* DBopen(rel) - Open a data base file of type 'rel'                          */
/*                                                                            */
/* rel:    The relation type (RLJETRAN, RLCHART, etc.).                       */
/*                                                                            */
/* Returns:                                                                   */
/* >0      The newly opened data base file id. (type DBFILEID)                */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADREL - rel is out of range (0<rel<MAXREL)                        */
/*         DBFULL - Maximum db files opened (MAXDBFILE)                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBFILEID
DBopen(rel)
RELTYPE rel;
{
	char *fn="DBopen";
	DBFILEID dbfid;
	struct dbfile *dbfptr;
	int i;

	INIT_MODULE(fn);

	/* validate rel */
	if (rel<1 || rel>=MAXREL) {
		_wn_err = BADREL;
		EXIT_MODULE(fn);
		return(0);
	}

	/* look for first empty dbfiletab entry */
	dbfid=0;
	for (i=1; i<MAXDBFILE; i++){
		dbfptr = &dbfiletab[i];
		if (dbfptr->rel_no == 0) {
			dbfid = i;
			dbfptr->rel_no = rel;
			dbfptr->actmfp = mf_def(NULLP,reldesctab[rel].maxlines,reldesctab[rel].maxcols);
			dbfptr->tempmfp = NULLP;
			dbfptr->modified = NO;
			dbfptr->currow = 0;
			break;
		}
	}

	/* check: is dbfiletab full? */
	if (dbfid == 0) {
		_wn_err = DBFULL;
	}
	EXIT_MODULE(fn);
	return(dbfid);
}


/*----------------------------------------------------------------------------*/
/* DBclose(dbfid) - Close the data base file id=dbfid                         */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBclose(dbfid)
DBFILEID dbfid;
{
	char *fn="DBclose";
	struct dbfile *dbfptr;
	MFILEPTR actmfp;
	struct reldesc *reldescp;
	DBRET (*impfcn)(DBRECPTR,char *);
	int row;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	actmfp = dbfptr->actmfp;
	reldescp = &reldesctab[dbfptr->rel_no];
	impfcn = reldescp->importfcn;

	/* free structures created by import function */
	if (impfcn != NULLFP) {
	  for (row=0; row<actmfp->ln_q; row++) {
		free_mem((char *)actmfp->farray[row]);
		actmfp->farray[row] = NULLP;
	  }
	}
	actmfp->ln_q = 0;


	/* release mfiles */
	if (dbfptr->actmfp != NULLP){
		mf_free(dbfptr->actmfp);
		dbfptr->actmfp = NULLFP;
	}
	if (dbfptr->tempmfp != NULLP){
		mf_free(dbfptr->tempmfp);
		dbfptr->tempmfp = NULLFP;
	}
	
	dbfptr->rel_no = 0;

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* DBrecnum(dbfid) - Return the current record number (start with 1)          */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/*                                                                            */
/* Returns:                                                                   */
/*  INT	   The current record index + 1                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
int
DBrecnum(dbfid)
DBFILEID dbfid;
{
	char *fn="DBrecnum";
	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	EXIT_MODULE(fn);
	return(dbfiletab[dbfid].currow+1);
}
/*----------------------------------------------------------------------------*/
/* DBtotrec(dbfid) - Return the total record count                            */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/*                                                                            */
/* Returns:                                                                   */
/*  INT	   The total number of records in db                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
int
DBtotrec(dbfid)
DBFILEID dbfid;
{
	char *fn="DBtotrec";
	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	EXIT_MODULE(fn);
	return(dbfiletab[dbfid].actmfp->ln_q);
}
/*----------------------------------------------------------------------------*/
/* DBismodfd(dbfid) - If the dbfid has been modified, return YES; else NO     */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/*                                                                            */
/* Returns:                                                                   */
/*  YES	   The dbfid has been modified.                                       */
/*                                                                            */
/*  NO     The dbfid has been opened but no insert, delete, or change         */
/*         has been performed.                                                */
/*----------------------------------------------------------------------------*/
BOOL
DBismodfd(dbfid)
DBFILEID dbfid;
{
	char *fn="DBismodfd";
	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	EXIT_MODULE(fn);
	return(dbfiletab[dbfid].modified);
}


/*----------------------------------------------------------------------------*/
/* DBrdfirst(dbfid,outbuf) - Read first record of database file into outbuf   */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* outbuf: Storage, provided by caller, where output structure is copied.     */
/*                                                                            */
/* Returns:                                                                   */
/* POINTER The pointer to the structure (char *) in the first dbfile          */
/*         record selected.  See also the DBselect() function.                */
/*         Points to outbuf structure.                                        */
/*                                                                            */
/* NULLP   Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)              */
/*         0 - No records selected                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRECPTR
DBrdfirst(dbfid,outbuf)
DBFILEID dbfid;
DBRECPTR outbuf;
{
	char *fn="DBrdfirst";
	struct dbfile *dbfptr;
	struct reldesc *reldescp;
	int row,ln_q;
	char *rwp;
	SELECTRET (*selfcn)(struct dbfile *, DBRECPTR);
	DBRET (*impfcn)(DBRECPTR, char *);
	MFILEPTR actmfp;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	impfcn = reldesctab[dbfptr->rel_no].importfcn;
	actmfp = dbfptr->actmfp;
	ln_q = actmfp->ln_q;
	selfcn = dbfptr->selfcn;
	reldescp = &reldesctab[dbfptr->rel_no];

	/* check: is MFILE empty? */
	if (ln_q == 0) {
		memset(outbuf,0,reldescp->struct_size);
		EXIT_MODULE(fn);
		return(NULLP);
	}

	/* if no select function, return first rec in MFILE */
	if (selfcn == NULLFP) {
		dbfptr->currow = 0;
		rwp = (char *)actmfp->farray[0];
		memcpy(outbuf,rwp,reldescp->struct_size);
		EXIT_MODULE(fn);
		return(outbuf);
	}

	/* Use select function to get first matching MFILE entry */
	for(row=0; row<ln_q; row++) {
		rwp = (char *)actmfp->farray[row];
		if ((*selfcn)(dbfptr, rwp) == MATCH) {
			dbfptr->currow = row;
			memcpy(outbuf,rwp,reldescp->struct_size);
			EXIT_MODULE(fn);
			return(outbuf);
		}
	}

	/* No match, return NULLP */
	memset(outbuf,0,reldescp->struct_size);
	EXIT_MODULE(fn);
	return(NULLP);
}
/*----------------------------------------------------------------------------*/
/* DBrdseek(dbfid,recnum,outbuf) - Read record number "recnum" of             */
/*                                 database file into outbuf                  */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* recnum: The record number, starting with 1, of the currently active rec    */
/* outbuf: Storage, provided by caller, where output structure is copied.     */
/*                                                                            */
/* Returns:                                                                   */
/* POINTER The pointer to the structure (char *) in the first dbfile          */
/*         record selected.  See also the DBselect() function.                */
/*         Points to outbuf structure.                                        */
/*                                                                            */
/* NULLP   Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)              */
/*         0 - No records selected                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRECPTR
DBrdseek(dbfid,recnum,outbuf)
DBFILEID dbfid;
int recnum;
DBRECPTR outbuf;
{
	char *fn="DBrdseek";
	struct dbfile *dbfptr;
	struct reldesc *reldescp;
	int ln_q;
	char *rwp;
	SELECTRET (*selfcn)(struct dbfile *, DBRECPTR);
	DBRET (*impfcn)(DBRECPTR, char *);
	MFILEPTR actmfp;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	impfcn = reldesctab[dbfptr->rel_no].importfcn;
	actmfp = dbfptr->actmfp;
	ln_q = actmfp->ln_q;
	selfcn = dbfptr->selfcn;
	reldescp = &reldesctab[dbfptr->rel_no];

	/* check: is MFILE empty? */
	if (ln_q == 0) {
		memset(outbuf,0,reldescp->struct_size);
		EXIT_MODULE(fn);
		return(NULLP);
	}

	/* check recnum range */
	if (recnum >=ln_q) 
		dbfptr->currow = ln_q - 1;

	if (recnum < 1)
		dbfptr->currow = 0;

	if (recnum >= 1 && recnum <ln_q)
		dbfptr->currow = recnum - 1;


	/* return record in MFILE */
	rwp = (char *)actmfp->farray[dbfptr->currow];
	memcpy(outbuf,rwp,reldescp->struct_size);
	EXIT_MODULE(fn);
	return(outbuf);
}
/*----------------------------------------------------------------------------*/
/* DBrdlast(dbfid,outbuf) - Read last record of database file into outbuf     */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* outbuf: Storage, provided by caller, where output structure is copied.     */
/*                                                                            */
/* Returns:                                                                   */
/* POINTER The pointer to the structure (char *) in the last dbfile           */
/*         record selected.  See also the DBselect() function.                */
/*         Points to outbuf structure.                                        */
/*                                                                            */
/* NULLP   Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)              */
/*         0 - No records selected                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRECPTR
DBrdlast(dbfid,outbuf)
DBFILEID dbfid;
DBRECPTR outbuf;
{
	char *fn="DBrdlast";
	struct dbfile *dbfptr;
	struct reldesc *reldescp;
	int ln_q;
	char *rwp;
	SELECTRET (*selfcn)(struct dbfile *, DBRECPTR);
	DBRET (*impfcn)(DBRECPTR, char *);
	MFILEPTR actmfp;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	impfcn = reldesctab[dbfptr->rel_no].importfcn;
	actmfp = dbfptr->actmfp;
	ln_q = actmfp->ln_q;
	selfcn = dbfptr->selfcn;
	reldescp = &reldesctab[dbfptr->rel_no];

	/* check: is MFILE empty? */
	if (ln_q == 0) {
		memset(outbuf,0,reldescp->struct_size);
		EXIT_MODULE(fn);
		return(NULLP);
	}

	/* if no select function, return last rec in MFILE */
	if (selfcn == NULLFP) {
		dbfptr->currow = ln_q-1;
		rwp = (char *)actmfp->farray[ln_q-1];
		memcpy(outbuf,rwp,reldescp->struct_size);
		EXIT_MODULE(fn);
		return(outbuf);
	}

	/* Use select function to get first matching MFILE entry */
	/* Start at end of file and read toward beginning
	for(row=ln_q-1; row>=0; row--) {
		rwp = (char *)actmfp->farray[row];
		if ((*selfcn)(dbfptr, rwp) == MATCH) {
			memcpy(outbuf,rwp,reldescp->struct_size);
			dbfptr->currow = row;
			EXIT_MODULE(fn);
			return(outbuf);
		}
	}

	/* No match, return NULLP */
	memset(outbuf,0,reldescp->struct_size);
	EXIT_MODULE(fn);
	return(NULLP);
}
/*----------------------------------------------------------------------------*/
/* DBrdnext(dbfid,outbuf) - Read next  record of database file into outbuf    */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* outbuf: Storage, provided by caller, where output structure is copied.     */
/*                                                                            */
/* Returns:                                                                   */
/* POINTER The pointer to the structure (char *) in the next  dbfile          */
/*         record selected.  See also the DBselect() function.                */
/*         Points to outbuf structure.                                        */
/*                                                                            */
/* NULLP   Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)              */
/*         0 - No records selected                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRECPTR
DBrdnext(dbfid,outbuf)
DBFILEID dbfid;
DBRECPTR outbuf;
{
	char *fn="DBrdnext";
	struct dbfile *dbfptr;
	struct reldesc *reldescp;
	int row,ln_q;
	char *rwp;
	SELECTRET (*selfcn)(struct dbfile *, DBRECPTR);
	DBRET (*impfcn)(DBRECPTR, char *);
	MFILEPTR actmfp;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	impfcn = reldesctab[dbfptr->rel_no].importfcn;
	actmfp = dbfptr->actmfp;
	ln_q = actmfp->ln_q;
	selfcn = dbfptr->selfcn;
	reldescp = &reldesctab[dbfptr->rel_no];

	/* check: is MFILE empty? */
	if (ln_q == 0) {
		memset(outbuf,0,reldescp->struct_size);
		EXIT_MODULE(fn);
		return(NULLP);
	}

	/* if no select function, return first rec in MFILE */
	if (selfcn == NULLFP) {
		row = dbfptr->currow + 1;
		if (row >= ln_q) return (NULLP);
		dbfptr->currow = row;
		rwp = (char *)actmfp->farray[row];
		memcpy(outbuf,rwp,reldescp->struct_size);

		EXIT_MODULE(fn);
		return(outbuf);
	}

	/* Use select function to get first matching MFILE entry */
	for(row=dbfptr->currow+1; row<ln_q; row++) {
		rwp = (char *)actmfp->farray[row];
		if ((*selfcn)(dbfptr, rwp) == MATCH) {
			dbfptr->currow = row;
			memcpy(outbuf,rwp,reldescp->struct_size);
			EXIT_MODULE(fn);
			return(outbuf);
		}
	}

	/* No match, return NULLP */
	memset(outbuf,0,reldescp->struct_size);
	EXIT_MODULE(fn);
	return(NULLP);
}
/*----------------------------------------------------------------------------*/
/* DBrdprev(dbfid,outbuf) - Read previous  record of database file into outbuf*/
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* outbuf: Storage, provided by caller, where output structure is copied.     */
/*                                                                            */
/* Returns:                                                                   */
/* POINTER The pointer to the structure (char *) in the previous  dbfile      */
/*         record selected.  See also the DBselect() function.                */
/*         Points to outptr structure.                                        */
/*                                                                            */
/* NULLP   Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)              */
/*         0 - No records selected                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRECPTR
DBrdprev(dbfid,outbuf)
DBFILEID dbfid;
DBRECPTR outbuf;
{
	char *fn="DBrdprev";
	struct dbfile *dbfptr;
	struct reldesc *reldescp;
	int row,ln_q;
	char *rwp;
	SELECTRET (*selfcn)(struct dbfile *, DBRECPTR);
	DBRET (*impfcn)(DBRECPTR, char *);
	MFILEPTR actmfp;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	impfcn = reldesctab[dbfptr->rel_no].importfcn;
	actmfp = dbfptr->actmfp;
	ln_q = actmfp->ln_q;
	selfcn = dbfptr->selfcn;
	reldescp = &reldesctab[dbfptr->rel_no];

	/* check: is MFILE empty? */
	if (ln_q == 0) {
		memset(outbuf,0,reldescp->struct_size);
		EXIT_MODULE(fn);
		return(NULLP);
	}

	/* if no select function, return first rec in MFILE */
	if (selfcn == NULLFP) {
		row = dbfptr->currow - 1;
		if (row < 0) return (NULLP);
		dbfptr->currow = row;
		rwp = (char *)actmfp->farray[row];
		memcpy(outbuf,rwp,reldescp->struct_size);

		EXIT_MODULE(fn);
		return(outbuf);
	}

	/* Use select function to get first matching MFILE entry */
	for(row=dbfptr->currow-1; row>=0; row--) {
		rwp = (char *)actmfp->farray[row];
		if ((*selfcn)(dbfptr, rwp) == MATCH) {
			dbfptr->currow = row;
			memcpy(outbuf,rwp,reldescp->struct_size);
			EXIT_MODULE(fn);
			return(outbuf);
		}
	}

	/* No match, return NULLP */
	memset(outbuf,0,reldescp->struct_size);
	EXIT_MODULE(fn);
	return(NULLP);
}

/*----------------------------------------------------------------------------*/
/* DBselect(dbfid,selfcn) - Define a select function, 'selfcn', for the dbfile*/
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* selfcn: Function pointer to select function that filters DBrdfirst         */
/*         and DBrdnext.  The function returns MATCH or NOMATCH.           */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBselect(dbfid,selfcn)
DBFILEID dbfid;
SELECTRET (*selfcn)();
{
	char *fn="DBselect";
	struct dbfile *dbfptr;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];

	dbfptr->selfcn=selfcn;

	EXIT_MODULE(fn);
	return(1);
}

/*----------------------------------------------------------------------------*/
/* DBinsrec(dbfid,recptr) - Insert data base record into dbfile=dbfid         */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* recptr: Pointer to the structure (cast into a char pointer) to be inserted */
/*         before current row (dbfptr->currow).                               */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBinsrec(dbfid,recptr)
DBFILEID dbfid;
DBRECPTR recptr;
{
	char *fn="DBinsrec";
	struct dbfile *dbfptr;
	struct reldesc *reldescp;
	MFILEPTR actmfp;
	char *dbrecptr;
	char **lnptr;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	actmfp = dbfptr->actmfp;
	reldescp = &reldesctab[dbfptr->rel_no];

	/* insert record into MFILE */
	dbrecptr = (DBRECPTR) get_mem(reldescp->struct_size);
	memcpy(dbrecptr,recptr,reldescp->struct_size);
	mf_rwins("", dbfptr->currow, actmfp);
	lnptr = (char **)&(actmfp->farray[dbfptr->currow]);
	free_mem(*lnptr);
	*lnptr = dbrecptr;

	EXIT_MODULE(fn);
	return(1);
}

/*----------------------------------------------------------------------------*/
/* DBapprec(dbfid,recptr) - Append data base record into dbfile=dbfid         */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* recptr: Pointer to the structure (cast into a char pointer) to be appended */
/*         after current row (dbfptr->currow).                                */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBapprec(dbfid,recptr)
DBFILEID dbfid;
DBRECPTR recptr;
{
	char *fn="DBapprec";
	struct dbfile *dbfptr;
	struct reldesc *reldescp;
	MFILEPTR actmfp;
	char *dbrecptr;
	char **lnptr;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	actmfp = dbfptr->actmfp;
	reldescp = &reldesctab[dbfptr->rel_no];

	/* append record into MFILE */
	dbrecptr = (DBRECPTR) get_mem(reldescp->struct_size);
	memcpy(dbrecptr,recptr,reldescp->struct_size);
	if (dbfptr->currow == actmfp->ln_q) {
		mf_rwins("", LAST_ROW, actmfp);
		lnptr = (char **) &(actmfp->farray[actmfp->ln_q-1]);
	} else {
		(dbfptr->currow)++;
		mf_rwins("", dbfptr->currow, actmfp);
		lnptr = (char **) &(actmfp->farray[dbfptr->currow]);
	}
	free_mem(*lnptr);
	*lnptr = dbrecptr;

	EXIT_MODULE(fn);
	return(1);
}

/*----------------------------------------------------------------------------*/
/* DBsort(dbfid,cmpfcn) - Sort db file.  The ordering comes from 'cmpfcn'     */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* cmpfcn: Same return as strcmp: >0, 0, or <0.                               */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBsort(dbfid,cmpfcn)
DBFILEID dbfid;
int (*cmpfcn)(DBRECPTR *,DBRECPTR *);
{
	char *fn="DBsort";
	struct dbfile *dbfptr;
	MFILEPTR actmfp;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	actmfp = dbfptr->actmfp;
	DBcmprel_no = dbfptr->rel_no;

	/* sort MFILE */
	qsort(actmfp->farray,actmfp->ln_q,sizeof(DBRECPTR),cmpfcn);

	DBcmprel_no = 0;

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* DBmerge(dbfid1,dbfid2,cmpfcn) - Merge dbfid2 into dbfid1.  Assume both     */
/*          are sorted according to the collating sequence given by cmpfcn.  */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* dbfid1:  The db file id assigned to the data base when DBopen'ed.          */
/* dbfid2:  The db file id assigned to the data base when DBopen'ed.          */
/* cmpfcn: Same return as strcmp: >0, 0, or <0.                               */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADMERGEREL - Relation types different.                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBmerge(dbfid1,dbfid2,cmpfcn)
DBFILEID dbfid1,dbfid2;
int (*cmpfcn)(DBRECPTR *,DBRECPTR *);
{
	char *fn="DBmerge";
	struct dbfile *dbfptr1,*dbfptr2;
	MFILEPTR outmfp;
	int maxlines, maxcols;
	DBRECPTR *f1,*f2,*outf;
	int cmp,row;
	int outln_q;

	INIT_MODULE(fn);

	/* Assign temporary pointers */
	dbfptr1 = &dbfiletab[dbfid1];
	dbfptr2 = &dbfiletab[dbfid2];

	/* validate dbfid1 and dbfid2:  must point to same relation type */
	if (dbfptr1->rel_no != dbfptr2->rel_no) {
		_wn_err = BADMERGEREL;
		EXIT_MODULE(fn);
		return(0);
	}
	DBcmprel_no = dbfptr1->rel_no;

	/* create merge output MFILE */
	maxlines = dbfptr1->actmfp->ln_q + dbfptr2->actmfp->ln_q + 10;
	maxcols  = reldesctab[dbfptr1->rel_no].maxcols;
	outmfp   = mf_def(NULLP, maxlines, maxcols);
	

	/* step thru dbfptr1 and dbfptr2, merging them into outmfp */
	f1 = (DBRECPTR *)(dbfptr1->actmfp->farray);
	f2 = (DBRECPTR *)(dbfptr2->actmfp->farray);
	outf = (DBRECPTR *)(outmfp->farray);
	outln_q = 0;
	while (*f1 != NULL && *f2 != NULL) {
		cmp = cmpfcn(f1,f2);
		if (cmp < 0) {
			*outf++ = *f1++;
			outln_q++;
		} else if (cmp == 0) {
			*outf++ = *f1++;
			outln_q++;
			*outf++ = *f2++;
			outln_q++;
		} else if (cmp > 0) {
			*outf++ = *f2++;
			outln_q++;
		}
	}

	/* merge complete.  check for left-overs in f1 or f2 */
	while (*f1 != NULL) { *outf++ = *f1++; outln_q++;}
	while (*f2 != NULL) { *outf++ = *f2++; outln_q++;}


	/* replace dbfid->actmfp with outmfp */
	for (row=0; row<dbfptr1->actmfp->ln_q; row++) {
		dbfptr1->actmfp->farray[row] = NULLP;
	}
	dbfptr1->actmfp->ln_q = 0;
	mf_free(dbfptr1->actmfp);
	outmfp->ln_q = outln_q;
	dbfptr1->actmfp = outmfp;

	DBcmprel_no = 0;

	EXIT_MODULE(fn);
	return(1);
}

/*----------------------------------------------------------------------------*/
/* DBimport(dbfid,filename) - Import ASCII data from 'filename.'              */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* filename: Char pointer to a filename.  This file will be read-in and       */
/*         converted to internal data structures.                             */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBimport(dbfid,filename)
DBFILEID dbfid;
char *filename;
{
	char *fn="DBimport";
	struct dbfile *dbfptr;
	MFILEPTR tempmfp,actmfp;
	int row;
	DBRET (*impfcn)(DBRECPTR,char *), ret;
	char *dbrecptr;
	char **lnptr;
	struct reldesc *reldescp;
	int maxlines,maxcols;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	actmfp = dbfptr->actmfp;
	reldescp = &reldesctab[dbfptr->rel_no];
	impfcn = reldescp->importfcn;
	maxlines = reldescp->maxlines;
	maxcols = reldescp->maxcols;

	/* read in filename */
	actmfp->fn = strsavep(filename);
	if (mf_rd(actmfp) == 0) {
 		EXIT_MODULE(fn);
		return(0);
	}

	/*
	** Check: import function defined
	*/
	if (impfcn == NULLFP) {
		EXIT_MODULE(fn);
		return(0);
	}

	/*
	** Run import conversion routine for each line in
	** actmfp, verifying validity; write structure to tempmfp
	*/
	PFerrgdata.filename = actmfp->fn;
	PFerrgdata.relname  = reldescp->name;
	tempmfp = mf_def(NULLP, maxlines, maxcols);
	for (row=0; row<actmfp->ln_q; row++) {
		PFerrgdata.currow = row;
		PFerrgdata.line = mf_rwp(row,actmfp);
		dbrecptr = (DBRECPTR) get_mem(reldescp->struct_size);
		if (dbrecptr == NULLP) {
			EXIT_MODULE (fn);
			return(0);
		}
		ret = (*impfcn)((DBRECPTR)dbrecptr,mf_rwp(row,actmfp));
		if (ret == 0) {
			/* print an error message !!!! */
			free_mem(dbrecptr);
		} else {
			mf_rwins("", LAST_ROW, tempmfp);
			lnptr = (char **)&(tempmfp->farray[tempmfp->ln_q-1]);
			free_mem(*lnptr);
			*lnptr = dbrecptr;
		}
		
	}

	/* use tempmfp as the active MFILE */
	mf_free(actmfp);
	dbfptr->actmfp = tempmfp;

	EXIT_MODULE(fn);
	memset(&PFerrgdata,0,sizeof(PFerrgdata));
	return(1);
}

/*----------------------------------------------------------------------------*/
/* DBexport(dbfid,filename) - Export db file to its ASCII formated file.      */
/*                                                                            */
/* dbfid:  The db file id assigned to the data base when DBopen'ed            */
/* filename: Char pointer to a filename.  This file will be written-to and    */
/*         converted from internal data structures.                           */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDBFID - dbfid is out of range ((0<dbfid<MAXDBFILE)              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBexport(dbfid,filename)
DBFILEID dbfid;
char *filename;
{
	char *fn="DBexport";
	MFILEPTR actmfp,tempmfp;
	struct dbfile *dbfptr;
	int row;
	DBRET (*expfcn)(char *, DBRECPTR), ret;
	struct reldesc *reldescp;
	int maxlines,maxcols;
	char *dbrecptr;

	INIT_MODULE(fn);

	/* validate dbfid */
	val_dbfid(fn);

	/* Assign temporary pointers */
	dbfptr = &dbfiletab[dbfid];
	actmfp = dbfptr->actmfp;
	reldescp = &reldesctab[dbfptr->rel_no];
	expfcn = reldescp->exportfcn;
	maxlines = reldescp->maxlines;
	maxcols = reldescp->maxcols;

	/*
	** Check: expfcn is NULLFP
	*/
	if (expfcn == NULLFP) {
		/* write out filename */
		mf_wr(filename,FWRITE,actmfp);
		EXIT_MODULE(fn);
		return(1);
	}

	/*
	** Run export conversion routine for each line in
	** actmfp; write lines to tempmfp.
	*/
	tempmfp = mf_def(NULLP, maxlines, maxcols);
	dbrecptr = get_mem(maxcols);
	for (row=0; row<actmfp->ln_q; row++) {
		*dbrecptr = '\0';
		ret = (*expfcn)(dbrecptr,(char *)actmfp->farray[row]);
		if (ret == 0) {
			/* print error message !!?? */
			free_mem(dbrecptr);
			EXIT_MODULE(fn);
			return(0);
		} else {
			mf_rwins(dbrecptr, LAST_ROW, tempmfp);
		}
	}
	free_mem(dbrecptr);

	/* write out filename */
	mf_wr(filename,FWRITE,tempmfp);
	mf_free(tempmfp);
	dbfptr->modified = NO;

	EXIT_MODULE(fn);
	return(1);
}

/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*          RECORD AND FIELD SPECIFIC DATA BASE ROUTINES                      */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* DBdmconv(domain,dmptr,stp,delimp) - convert domain string to internal      */
/*         format.  Called by DBimport().                                     */
/*                                                                            */
/* domain: The domain id - index to the dmdesctab array.                      */
/* dmptr:  Function output.  A pointer to the internal domain format.         */
/* stp:    Function input.  A char pointer to the import string.              */
/* delimp: Function input.  A char pointer to string of delimiters.           */
/*         E.g. a descrition bounded by comma or newline, delimp=",\n".       */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDOMAIN-domain is out of range ((0<domain<MAXDMDESCTAB)          */
/*         BADLEN - char count of domain is invalid                           */
/*         BADMONTH - month out of range (01<=month<=12)                      */
/*         BADDAY - day out of range (01<=day<=31)                            */
/*         BADDOMAIN - unknown domain                                         */
/*         BADACCTCHART - acct not found in chart                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
struct DBchart chartrec;
DBRET
DBdmconv(domain,dmptr,stp,delimp)
DMTYPE domain;
DMPTR dmptr;
char **stp;
char *delimp;
{
	char *fn="DBdmconv";
	DBRET dbret;
	char pic,ar[100],*arptr,*sptr;
	int ret,len,minlen,maxlen;
	BOOL done;
	int sign;
	long amt,*ldmptr;

	INIT_MODULE(fn);

	/* validate domain */
	if (domain<1 || domain>=MAXDMDESCTAB) {
		_wn_err = BADDOMAIN;
		EXIT_MODULE(fn);
		return(0);
	}

	/* Assign temporary pointers */
	pic = dmdesctab[domain].pic;
	minlen = dmdesctab[domain].minlen;
	maxlen = dmdesctab[domain].maxlen;
	done = NO;
	len = 0;
	arptr = ar;
	*arptr = '\0';
	sptr = *stp;

	/* Get characters from stp: upto maxlen characters,
	** or until character does not match pic char.
	*/
	while (done == NO && strchr(delimp,*sptr) == NULLP) {
	  ret = 0;
	  switch(pic) {
	  case  'X':	if (isprint(*sptr) != 0) ret = 1;
			break;

	  case	'9':	if (isdigit(*sptr) || *sptr=='-' || *sptr=='.')
				ret = 1;
			break;
	
	  case	'A':	if (isalnum(*sptr)) ret = 1;
			break;


	  }
	  if (ret == 1) {
		*arptr = *sptr;
		arptr++;
		sptr++;
		len++;
		if (len >= maxlen) done = YES;
	  } else {
		done = YES;
	  }
	} /* endwhile */

	*stp = sptr;
	*arptr = '\0';

	/* check that at least minlen digits collected */
	if (strlen(ar) < minlen) {
		_wn_err = BADLEN;
		EXIT_MODULE(fn);
		return(0);
	}


	/* validate and convert from string to internal data type */
	switch (domain) {
	case DMACCT:
		if (chartid != 0) {
			/* validate acct is found in chart */
			strcpy(DBselstr,ar);
			if (DBrdfirst(chartid,(DBRECPTR)&chartrec) == NULLP) {
				_wn_err = BADACCTCHART;
				EXIT_MODULE(fn);
				return(0);
			}
			*DBselstr = '\0';
		}
		/* fall thru !!! */
	case DMDESC:
	case DMOLDACCT:
	case DMGENACCT:
		strcpy( (char *)dmptr, ar);
		dbret = 1;
		break;
	
	case DMMONTH:
		if (strcmp(ar,"01") >= 0 || strcmp(ar,"12") <= 0) {
			dbret = 1;
			strcpy( (char *)dmptr, ar);
		} else {
			_wn_err = BADMONTH;
			dbret = 0;
		}
		break;

	case DMDAY:
		if (strcmp(ar,"01") >= 0 || strcmp(ar,"31") <= 0) {
			dbret = 1;
			strcpy( (char *)dmptr, ar);
		} else {
			dbret = 0;
			_wn_err = BADDAY;
		}
		break;

	case DMAMT:
	case DMBUDAMT:
		amt = 0;
		arptr = ar;
		sign = 1;
		if (*arptr == '-') {
			sign = -1;
			arptr++;
		}
		while (isdigit(*arptr)) {
			amt = amt*10 + (int)*arptr - (int)'0';
			arptr++;
		}
		if (*arptr == '.') {
			arptr++;
			if (isdigit(*arptr)) {
				amt = amt*10 + (int)*arptr - (int)'0';
				arptr++;
			}
			if (isdigit(*arptr)) {
				amt = amt*10 + (int)*arptr - (int)'0';
				arptr++;
			}
		} else {
			amt = amt * 100;
		}

		/* set sign */
		amt = amt*sign;

		if (*arptr != '\0') {
			_wn_err = BADAMT;
			dbret = 0;
		} else {
			dbret = 1;
			ldmptr = (long *) dmptr;
			*ldmptr = amt;
		}
		break;

	default:
		_wn_err = BADDOMAIN;
		dbret = 0;
		break;
	} /* switch */

	EXIT_MODULE(fn);
	return(dbret);
}

/*----------------------------------------------------------------------------*/
/* DBdmtostr(domain,stp,dmptr) - convert domain from internal format to string*/
/*         Called by DBexport().                                              */
/*                                                                            */
/* domain: The domain id - index to the dmdesctab array.                      */
/* stp:    Function output.  A char pointer to the export string.             */
/* dmptr:  Function input.  A pointer to the internal domain format.          */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDOMAIN-domain is out of range ((0<domain<MAXDMDESCTAB)          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBdmtostr(domain,stp,dmptr)
DMTYPE domain;
char *stp;
DMPTR dmptr;
{
	char *fn="DBdmtostr";
	DBRET dbret;
	char ar[100],*arptr;
	long amt;
	int sign,lsd;

	INIT_MODULE(fn);

	/* validate domain */
	if (domain<1 || domain>=MAXDMDESCTAB) {
		_wn_err = BADDOMAIN;
		EXIT_MODULE(fn);
		return(0);
	}

	/* Assign temporary pointers */
	*ar = '\0';
	arptr = ar;

	/* convert domain from internal format to char string */
	switch (domain) {
	case DMACCT:
	case DMDESC:
	case DMOLDACCT:
	case DMGENACCT:
	case DMMONTH:
	case DMDAY:
		strcat(stp, (char *)dmptr);
		break;

	case DMAMT:
	case DMBUDAMT:
		amt = * (long *) dmptr;
		/* sign */
		if (amt < 0L) {
			sign = -1;
			amt = amt * -1L;
		}

		/*
		** 10000 converts to
		**       DMAMT - 100.00
		**       DMBUDAMT - 100
		*/
		if (amt!=(amt/100L)*100L && domain==DMBUDAMT || domain==DMAMT) {
		   /* hundreths */
		   lsd = (int) ( amt - (amt/10L)*10L);
		   *arptr = (char) (lsd + (int)'0');
		   arptr++;
		   amt = amt/10L;
		
		   /* tenths */
		   lsd = (int) (amt - (amt/10L)*10L);
		   *arptr = (char) (lsd + (int)'0');
		   arptr++;
		   amt = amt/10L;

		   /* decimal */
		   *arptr = '.';
		   arptr++;
		} else {
		   amt = amt/100L;
		}

		/* string should have leading zero:  0.12, -0.01, etc. */
		if (amt == 0L) {
			*arptr = '0';
			arptr++;
		}

		/* integer part */
		while ( amt != 0L) {
			lsd = (int)(amt - (amt/10L)*10L);
			*arptr = (char) ((int)lsd + (int)'0');
			arptr++;
			amt = amt/10L;
		}



		/* sign */
		if (sign == -1) {
			*arptr = '-';
			arptr++;
		}
		*arptr = '\0';
		strcat(stp, strrev(ar));
		break;

	default:
		_wn_err = BADDOMAIN;
		dbret = 0;
		break;
	}
		
	EXIT_MODULE(fn);
	return(dbret);
}

/*----------------------------------------------------------------------------*/
/* DBimpchart(outptr,inpstp) - Convert an input RLCHART record to a DBchart   */
/*         structure.  The following is the input record syntax:              */
/*                                                                            */
/*         1. a,<DMGENACCT>,<DMDESC>                                          */
/*         2. a,<DMGENACCT>,<DMDESC>,<DMOLDACCT>                              */
/*                                                                            */
/*         Example: a,101,Gary-Wheaton Bank,101                               */
/*                                                                            */
/* outptr: The pointer to the DBchart structure cast to DBRECPTR              */
/* inpstp: Pointer to the input string read from import file.                 */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDELIM - Unexpected delimiter (comma, newline, etc.)             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBimpchart(outptr,inpstp)
DBRECPTR outptr;
char *inpstp;
{
	char *fn="DBimpchart";
	struct DBchart chartrec;
	char *stp;
	int fld,nfld,err;
	BOOL match,done;
	DBRET dbret;

	INIT_MODULE(fn);
	
	memset((char *)&chartrec,0,sizeof(chartrec));
	stp = inpstp;
	done = NO;

	/* Parse each field, store data in chartrec */
	for(fld=0; done==NO; fld++) {
	  err = 0;
	  nfld = 0;
	  match = NO;
	  switch(fld) {
	  case 0:	/* "a," */
		if (strncmp(stp,"a,",2) == 0) match = YES;
		err = BADDELIM;
		stp = stp+2;
		break;

	  case 1:	/* GENACCT */
		if (DBdmconv(DMGENACCT, (DMPTR)chartrec.acct, &stp, "") == 1) 
			match = YES;
		break;

	  case 2:	/* "," */
		if (*stp == ',') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 3:	/* description */
		if (DBdmconv(DMDESC, (DMPTR)chartrec.desc, &stp, ",\n") == 1)
			match = YES;
		break;

	  case 4:	/* "," or "\n" */
		err = BADDELIM;
		if (*stp == '\n') {
			dbret = 1;
			done = YES;
			match = YES;
		} else if (*stp == ',') {
			match = YES;
		}
		stp++;
		break;

	  case 5:	/* old account number */
		if (DBdmconv(DMOLDACCT, (DMPTR)chartrec.oacct, &stp, "") == 1)
			match = YES;
		break;
	
	  case 6:	/* '\n' */
	  default:
		err = BADDELIM;
		if (*stp == '\n') {
			dbret = 1;
			done = YES;
			match = YES;
		}
		break;
	  } /* switch */

	  if (match == NO) {
		if (err != 0) _wn_err = err;
		done = YES;
		dbret = 0;
	  }
	  if (nfld != 0) fld = nfld - 1;
	} /* for loop */

	/* copy chartrec to outptr data structure */
	if (dbret == 1) 
 		memcpy((char *)outptr,(char *)&chartrec,sizeof(chartrec));

	EXIT_MODULE(fn);
	return(dbret);
}

/*----------------------------------------------------------------------------*/
/* DBexpchart(outstp,inpptr) - Convert a DBchart structure to a RLCHART       */
/*         record.    The following is the output record syntax:              */
/*                                                                            */
/*         1. a,<DMGENACCT>,<DMDESC>                                          */
/*         2. a,<DMGENACCT>,<DMDESC>,<DMOLDACCT>                              */
/*                                                                            */
/*         Example: a,101,Gary-Wheaton Bank,101                               */
/*                                                                            */
/* inpptr: The pointer to the DBchart structure cast to DBRECPTR              */
/* outstp: Pointer to the export file output string.                          */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBexpchart(outstp,inpptr)
char *outstp;
DBRECPTR inpptr;
{
	char *fn="DBexpchart";
	struct DBchart *chartptr;

	INIT_MODULE(fn);

	chartptr = (struct DBchart *)inpptr;

	/* output "a," */
	strcat(outstp,"a,");

	/* output general account */
	DBdmtostr(DMGENACCT, outstp, (DMPTR)chartptr->acct);
	
	/* output "," */
	strcat(outstp,",");

	/* output description */
	DBdmtostr(DMDESC, outstp, (DMPTR)chartptr->desc);

	/* output old account, if non-blank */
	if (strlen(chartptr->oacct) > 0) {
		strcat(outstp,",");
		DBdmtostr(DMOLDACCT, outstp, (DMPTR)chartptr->oacct);
	}

	
	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* DBimppregl(outptr,inpstp) - Convert an input RLPREGL record to a DBpregl   */
/*         structure.  The following is the input record syntax:              */
/*                                                                            */
/*         1. <DMMONTH><DMDAY>,<DMACCT>,<DMAMT>                               */
/*         2. <DMMONTH><DMDAY>,<DMACCT>,<DMAMT>,<DMDESC>                      */
/*                                                                            */
/*         Example: 1231,101,1400.00,Pay Check                                */
/*                                                                            */
/* outptr: The pointer to the DBchart structure cast to DBRECPTR              */
/* inpstp: Pointer to the input string read from import file.                 */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDELIM - Unexpected delimiter (comma, newline, etc.)             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBimppregl(outptr,inpstp)
DBRECPTR outptr;
char *inpstp;
{
	char *fn="DBimppregl";
	struct DBpregl preglrec;
	char *stp;
	int fld,nfld,err;
	BOOL match,done;
	DBRET dbret;

	INIT_MODULE(fn);

	memset((char *)&preglrec,0,sizeof(preglrec));
	stp = inpstp;
	done = NO;

	/* Parse each field, store data in preglrec */
	for(fld=0; done==NO; fld++) {
	  err = 0;
	  nfld = 0;
	  match = NO;
	  switch(fld) {
	  case 0:	/* month */
		if (DBdmconv(DMMONTH, (DMPTR)preglrec.mm, &stp, "") == 1) 
			match = YES;
		break;

	  case 1:	/* day */
		if (DBdmconv(DMDAY, (DMPTR)preglrec.dd, &stp, "") == 1) 
			match = YES;
		break;

	  case 2:	/* "," */
		if (*stp == ',') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 3:	/* account */
		if (DBdmconv(DMACCT, (DMPTR)preglrec.acct, &stp, "") == 1) 
			match = YES;
		break;

	  case 4:	/* "," */
		if (*stp == ',') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 5:	/* amount */
		if (DBdmconv(DMAMT, (DMPTR)&preglrec.amt, &stp, "") == 1) 
			match = YES;
		break;

	  case 6:	/* "," or "\n" */
		err = BADDELIM;
		if (*stp == '\n') {
			dbret = 1;
			done = YES;
			match = YES;
		} else if (*stp == ',') {
			match = YES;
		}
		stp++;
		break;

	  case 7:	/* description */
		if (DBdmconv(DMDESC, (DMPTR)preglrec.desc, &stp, ",\n") == 1)
			match = YES;
		break;

	  case 8:	/* '\n' */
	  default:
		err = BADDELIM;
		if (*stp == '\n') {
			dbret = 1;
			done = YES;
			match = YES;
		}
		break;
	  } /* switch */

	  if (match == NO) {
		if (err != 0) _wn_err = err;
		done = YES;
		dbret = 0;
	  }
	  if (nfld != 0) fld = nfld - 1;
	} /* for loop */

	/* copy chartrec to outptr data structure */
	if (dbret == 1) 
 		memcpy((char *)outptr,(char *)&preglrec,sizeof(preglrec));

	EXIT_MODULE(fn);
	return(dbret);
}
/*----------------------------------------------------------------------------*/
/* DBexppregl(outstp,inpptr) - Convert a DBpregl structure to a RLPREGL       */
/*         record.    The following is the output record syntax:              */
/*                                                                            */
/*         1. <DMMONTH><DMDAY>,<DMACCT>,<DMAMT>                               */
/*         2. <DMMONTH><DMDAY>,<DMACCT>,<DMAMT>,<DMDESC>                      */
/*                                                                            */
/*         Example: 1231,101,1400.00,Pay Check                                */
/*                                                                            */
/* inpptr: The pointer to the DBpregl structure cast to DBRECPTR              */
/* outstp: Pointer to the export file output string.                          */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBexppregl(outstp,inpptr)
DBRECPTR inpptr;
char *outstp;
{
	char *fn="DBexppregl";
	struct DBpregl *preglptr;


	INIT_MODULE(fn);

	preglptr = (struct DBpregl *)inpptr;

	/* output month */
	DBdmtostr(DMMONTH, outstp, (DMPTR)preglptr->mm);

	/* output day */
	DBdmtostr(DMDAY, outstp, (DMPTR)preglptr->dd);

	/* output "," */
	strcat(outstp,",");

	/* output account */
	DBdmtostr(DMACCT, outstp, (DMPTR)preglptr->acct);
	
	/* output "," */
	strcat(outstp,",");

	/* output amount */
	DBdmtostr(DMAMT, outstp, (DMPTR)&preglptr->amt);
	
	/* output description */
	if (strlen(preglptr->desc) > 0) {
		strcat(outstp,",");
		DBdmtostr(DMDESC, outstp, (DMPTR)preglptr->desc);
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* DBimpjetran(outptr,inpstp) - Convert an input RLJETRANrecord to a DBjetran */
/*         structure.  The following is the input record syntax:              */
/*                                                                            */
/*         1. <DMMONTH><DMDAY>,<DMACCT>,<DMAMT>                               */
/*         2. <DMMONTH><DMDAY>,<DMACCT>,<DMAMT>,<DMDESC>                      */
/*         3. <DMMONTH><DMDAY>,-<DMACCT>,<DMAMT>;<DMACCT>-                    */
/*         4. <DMMONTH><DMDAY>,-<DMACCT>,<DMAMT>;<DMACCT>,<DMAMT>;...         */
/*            ;<DMACCT>-[,<DMDESC>]                                           */
/*                                                                            */
/*         Example: 1231,101,1400.00,Pay Check                                */
/*                  1231,-631,63.00;101-,Groceries                            */
/*                                                                            */
/* outptr: The pointer to the DBjetran structure cast to DBRECPTR             */
/* inpstp: Pointer to the input string read from import file.                 */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDELIM - Unexpected delimiter (comma, newline, etc.)             */
/*         ACCTOVFLOW - More than MAXACCTAMT account/amount pairs             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBimpjetran(outptr,inpstp)
DBRECPTR outptr;
char *inpstp;
{
	char *fn="DBimpjetran";
	struct DBjetran jetranrec;
	char *stp;
	int fld,nfld,err;
	BOOL match,done;
	DBRET dbret;
	int pidx;

	INIT_MODULE(fn);

	/* zap jetranrec */
	memset((char *)&jetranrec,0,sizeof(jetranrec));

	stp = inpstp;
	pidx = 0;
	done = NO;

	/* Parse each field, store data in jetranrec */
	for(fld=0; done==NO; fld++) {
	  err = 0;
	  nfld = 0;
	  match = NO;
	  switch(fld) {
	  case 0:	/* month */
		if (DBdmconv(DMMONTH, (DMPTR)jetranrec.mm, &stp, "") == 1) 
			match = YES;
		break;

	  case 1:	/* day */
		if (DBdmconv(DMDAY, (DMPTR)jetranrec.dd, &stp, "") == 1) 
			match = YES;
		break;

	  case 2:	/* "," or ",-" */
		if (strncmp(stp,",-",2) == 0) {
			stp++;
			nfld = 9;
			match = YES;
		} else if (*stp == ',') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 3:	/* account */
		if (DBdmconv(DMACCT, (DMPTR)jetranrec.p[0].acct, &stp, "") == 1) 
			match = YES;
		break;

	  case 4:	/* "," */
		if (*stp == ',') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 5:	/* amount */
		if (DBdmconv(DMAMT, (DMPTR)&jetranrec.p[0].amt, &stp, "") == 1) 
			match = YES;
		break;

	  case 6:	/* "," or "\n" */
		err = BADDELIM;
		if (*stp == '\n') {
			dbret = 1;
			done = YES;
			match = YES;
		} else if (*stp == ',') {
			match = YES;
		}
		stp++;
		break;

	  case 7:	/* description */
		if (DBdmconv(DMDESC, (DMPTR)jetranrec.desc, &stp, "\n") == 1)
			match = YES;
		break;

	  case 8:	/* '\n' */
		err = BADDELIM;
		if (*stp == '\n') {
			dbret = 1;
			done = YES;
			match = YES;
		}
		break;

	  case 9:	/* account */
		if (DBdmconv(DMACCT, (DMPTR)jetranrec.p[0].acct, &stp, "") == 1) 
			match = YES;
		break;

	  case 10:	/* "," */
		if (*stp == ',') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 11:	/* amount */
		if (DBdmconv(DMAMT, (DMPTR)&jetranrec.p[pidx].amt, &stp, "") == 1) 
			match = YES;
		break;

	  case 12:	/* ";" */
		if (*stp == ';') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 13:	/* account */
		if (DBdmconv(DMACCT, (DMPTR)jetranrec.cracct, &stp, "") == 1) 
			match = YES;
		break;

	  case 14:	/* "," or "-" */
		if (*stp == '-') {
			nfld = 6;
			match = YES;
		} else if (*stp == ',') {
			match = YES;
			nfld = 11;
			pidx++;
			if (pidx >= MAXACCTAMT) {
				err = ACCTOVFLOW;
				done = YES;
				match=NO;
			} else {
				strcpy(jetranrec.p[pidx].acct,jetranrec.cracct);
				*(jetranrec.cracct) = '\0';
			}
		}
		err = BADDELIM;
		stp++;
		break;

	  } /* switch */

	  if (match == NO) {
		if (err != 0) _wn_err = err;
		done = YES;
		dbret = 0;
	  }
	  if (nfld != 0) fld = nfld - 1;
	} /* for loop */

	/* copy jetranrec to outptr data structure */
	if (dbret == 1) 
 		memcpy((char *)outptr,(char *)&jetranrec,sizeof(jetranrec));

	EXIT_MODULE(fn);
	return(dbret);
}
/*----------------------------------------------------------------------------*/
/* DBexpjetran(outstp,inpptr) - Convert a DBjetran structure to a RLPREGL     */
/*         record.    The following is the output record syntax:              */
/*                                                                            */
/*         1. <DMMONTH><DMDAY>,<DMACCT>,<DMAMT>                               */
/*         2. <DMMONTH><DMDAY>,<DMACCT>,<DMAMT>,<DMDESC>                      */
/*         3. <DMMONTH><DMDAY>,-<DMACCT>,<DMAMT>;<DMACCT>-                    */
/*         4. <DMMONTH><DMDAY>,-<DMACCT>,<DMAMT>;<DMACCT>,<DMAMT>;...         */
/*            ;<DMACCT>-[,<DMDESC>]                                           */
/*                                                                            */
/*         Example: 1231,101,1400.00,Pay Check                                */
/*                  1231,-631,63.00;101-,Groceries                            */
/*                                                                            */
/* inpptr: The pointer to the DBjetran structure cast to DBRECPTR             */
/* outstp: Pointer to the export file output string.                          */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBexpjetran(outstp,inpptr)
DBRECPTR inpptr;
char *outstp;
{
	char *fn="DBexpjetran";
	struct DBjetran *jetranptr;
	int pidx;


	INIT_MODULE(fn);

	jetranptr = (struct DBjetran *)inpptr;

	/* output month */
	DBdmtostr(DMMONTH, outstp, (DMPTR)jetranptr->mm);

	/* output day */
	DBdmtostr(DMDAY, outstp, (DMPTR)jetranptr->dd);

	/* output "," */
	strcat(outstp,",");

	if (*(jetranptr->cracct) == '\0') {
	  /* Record format: 1231,101,42.63,desc */
	    /* output account */
	  DBdmtostr(DMACCT, outstp, (DMPTR)jetranptr->p[0].acct);
	
	  /* output "," */
	  strcat(outstp,",");
  
	  /* output amount */
	  DBdmtostr(DMAMT, outstp, (DMPTR)&jetranptr->p[0].amt);
  	
	  /* output description */
	  if (strlen(jetranptr->desc) > 0) {
		  strcat(outstp,",");
		  DBdmtostr(DMDESC, outstp, (DMPTR)jetranptr->desc);
	  }
	} else {
	  /* output "-" */
	  strcat(outstp,"-");

	  /* record format: 1231,-631,29.85;101-,desc */
	  for (pidx=0; pidx < MAXACCTAMT && *(jetranptr->p[pidx].acct) != '\0'; pidx++) {
		/* output account */
		DBdmtostr(DMACCT, outstp, (DMPTR)jetranptr->p[pidx].acct);
  
		/* output "," */
	  	strcat(outstp,",");
  
	  	/* output amount */
	  	DBdmtostr(DMAMT, outstp, (DMPTR)&jetranptr->p[pidx].amt);
  	
		/* output ";" */
	  	strcat(outstp,";");
	  }
  
	  /* output account */
	  DBdmtostr(DMACCT, outstp, (DMPTR)jetranptr->cracct);
  
	  /* output "-" */
	  strcat(outstp,"-");

	  /* output description */
	  if (strlen(jetranptr->desc) > 0) {
		  strcat(outstp,",");
		  DBdmtostr(DMDESC, outstp, (DMPTR)jetranptr->desc);
	  }

	} /* if-else */
	EXIT_MODULE(fn);
	return(1);
}

/*----------------------------------------------------------------------------*/
/* DBimpbudget(outptr,inpstp) - Convert an input RLBUDGET record to a DBbudget*/
/*         structure.  The following is the input record syntax:              */
/*                                                                            */
/*         1. <DMACCT>,<DMACCT>,<DMDESC>,<DMAMT>,...,<DMAMT>                  */
/*            0-12 amounts; missing amount => 0.00                            */
/*                                                                            */
/*         Example: 631,101,Groceries,350,350,350,350,350,350,350,350,350,350 */
/*                  714,101,YMCA Dues,,,,450                                  */
/*                  801,101,Dummy Budget record                               */
/*                                                                            */
/* outptr: The pointer to the DBchart structure cast to DBRECPTR              */
/* inpstp: Pointer to the input string read from import file.                 */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*         BADDELIM - Unexpected delimiter (comma, newline, etc.)             */
/*         BADAMTCNT - more that 12 months of budget data                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBimpbudget(outptr,inpstp)
DBRECPTR outptr;
char *inpstp;
{
	char *fn="DBimpbudget";
	struct DBbudget budgetrec;
	char *stp;
	int fld,nfld,err;
	BOOL match,done;
	DBRET dbret;
	int pidx;

	memset((char *)&budgetrec,0,sizeof(budgetrec));
	pidx = 0;

	INIT_MODULE(fn);

	done = NO;
	stp = inpstp;

	/* Parse each field, store data in budgetrec */
	for(fld=0; done==NO; fld++) {
	  err = 0;
	  nfld = 0;
	  match = NO;
	  switch(fld) {
	  case 0:	/* account */
		if (DBdmconv(DMACCT, (DMPTR)budgetrec.acctdr, &stp, "") == 1) 
			match = YES;
		break;

	  case 1:	/* "," */
		if (*stp == ',') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 2:	/* account */
		if (DBdmconv(DMACCT, (DMPTR)budgetrec.acctcr, &stp, "") == 1) 
			match = YES;
		break;

	  case 3:	/* "," */
		if (*stp == ',') match = YES;
		err = BADDELIM;
		stp++;
		break;

	  case 4:	/* description */
		if (DBdmconv(DMDESC, (DMPTR)budgetrec.desc, &stp, ",\n") == 1)
			match = YES;
		break;

	  case 5:	/* "," or "\n" */
		err = BADDELIM;
		if (*stp == '\n') {
			dbret = 1;
			done = YES;
			match = YES;
		} else if (*stp == ',') {
			match = YES;
			if (pidx >= 12) {
				err = BADAMTCNT;
				match = NO;
				done = YES;
				dbret = 0;
			}
		}
		stp++;
		break;

	  case 6:	/* amount */
		if (DBdmconv(DMBUDAMT, (DMPTR)&budgetrec.amt[pidx], &stp, "") == 1) {
			match = YES;
			pidx++;
			nfld = 5;
		}
		break;
	  } /* switch */

	  if (match == NO) {
		if (err != 0) _wn_err = err;
		done = YES;
		dbret = 0;
	  }
	  if (nfld != 0) fld = nfld - 1;
	} /* for loop */

	/* copy budgetrec to outptr data structure */
	if (dbret == 1) 
 		memcpy((char *)outptr,(char *)&budgetrec,sizeof(budgetrec));

	EXIT_MODULE(fn);
	return(dbret);
}
/*----------------------------------------------------------------------------*/
/* DBexpbudget(outstp,inpptr) - Convert a DBbudget structure to a RLBUDGET    */
/*         record.    The following is the output record syntax:              */
/*                                                                            */
/*         1. <DMACCT>,<DMACCT>,<DMDESC>,<DMAMT>,...,<DMAMT>                  */
/*            0-12 amounts; missing amount => 0.00                            */
/*                                                                            */
/*         Example: 631,101,Groceries,350,350,350,350,350,350,350,350,350,350 */
/*                  714,101,YMCA Dues,,,,450                                  */
/*                                                                            */
/* inpptr: The pointer to the DBbudget structure cast to DBRECPTR             */
/* outstp: Pointer to the export file output string.                          */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
DBRET
DBexpbudget(outstp,inpptr)
DBRECPTR inpptr;
char *outstp;
{
	char *fn="DBexpbudget";
	struct DBbudget *budgetptr;
	int pidx;

	INIT_MODULE(fn);

	budgetptr = (struct DBbudget *)inpptr;

	/* output account */
	DBdmtostr(DMACCT, outstp, (DMPTR)budgetptr->acctdr);
	
	/* output "," */
	strcat(outstp,",");

	/* output account */
	DBdmtostr(DMACCT, outstp, (DMPTR)budgetptr->acctcr);
	
	/* output "," */
	strcat(outstp,",");

	/* output description */
	DBdmtostr(DMDESC, outstp, (DMPTR)budgetptr->desc);

	/* output 12 months of budget amounts */
	for (pidx=0; pidx<12; pidx++) {
	  /* output "," */
	  strcat(outstp,",");

	  /* output amount */
	  DBdmtostr(DMBUDAMT, outstp, (DMPTR)&budgetptr->amt[pidx]);
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* DBfindacct(dbfptr,dbrecptr) - Select function to match acct field in       */
/*         record pointed to by dbrecptr.  Compare dbrecptr->acct with        */
/*         DBselstr.  The function DBselect() cause this function to be called*/
/*         when DBrdfirst or DBrdnext are executed.                           */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* dbfptr: Pointer to dbfiletab structure for record.                         */
/* dbrecptr: Pointer to the record being tested against DBselstr variable.    */
/*                                                                            */
/* Returns:                                                                   */
/*  MATCH: dbrecptr->acct equals string stored in DBselstr.                   */
/*                                                                            */
/*  NOMATCH: dbrecptr->acct not equal                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
SELECTRET
DBfindacct(dbfptr, dbrecptr)
struct dbfile *dbfptr;
DBRECPTR dbrecptr;
{
	struct DBchart *chartptr;
	SELECTRET match;

	chartptr = (struct DBchart *)dbrecptr;
	dbfptr = dbfptr;

	if (DBselstr == NULLP) return(NOMATCH);

	if (strcmp(DBselstr,chartptr->acct) == 0) {
		match = MATCH;
	} else {
		match = NOMATCH;
	}
	return(match);
}
/*----------------------------------------------------------------------------*/
/* DBcmpacct(dbrecptr1,dbrecptr2) - Compare acct field in dbrecptr1 and 2.    */
/*         This function uses DBcmprel_no to determine record format.         */
/*                                                                            */
/*                                                                            */
/* dbrecptr1: Pointer to one record being compared                            */
/* dbrecptr2: Pointer to the other record being compared                      */
/*                                                                            */
/* Returns:                                                                   */
/*  -1:  dbrecptr1->acct < dbrecptr2->acct                                    */
/*   0:  dbrecptr1->acct = dbrecptr2->acct                                    */
/*   1:  dbrecptr1->acct > dbrecptr2->acct                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/
int
DBcmpacct(dbrecptr1,dbrecptr2)
DBRECPTR *dbrecptr1,*dbrecptr2;
{
	char key1[8],key2[8];
	char *acct1,*acct2;
	int cmp;
	struct DBpregl *preglptr;
	struct DBchart *chartptr;
	struct DBbudget *budgetptr;

	switch(DBcmprel_no) {
	case RLPREGL:
		preglptr = (struct DBpregl *)*dbrecptr1;
		acct1 = preglptr->acct;
		strcpy(key1,preglptr->acct);
		strcat(key1,preglptr->mm);
		strcat(key1,preglptr->dd);
		preglptr = (struct DBpregl *)*dbrecptr2;
		acct2 = preglptr->acct;
		strcpy(key2,preglptr->acct);
		strcat(key2,preglptr->mm);
		strcat(key2,preglptr->dd);
		cmp = strcmp(key1,key2);
		if (cmp == 0) {
			if (acct1 < acct2) return(-1);
			else return(1);
		}
		return(cmp);
		break;

	case RLCHART:
		chartptr = (struct DBchart *)*dbrecptr1;
		acct1 = chartptr->acct;
		chartptr = (struct DBchart *)*dbrecptr2;
		acct2 = chartptr->acct;
		cmp = strcmp(acct1,acct2);
		if (cmp == 0) {
			if (acct1 < acct2) return(-1);
			else return(1);
		}
		return(cmp);
		break;

	case RLBUDGET:
		budgetptr = (struct DBbudget *)*dbrecptr1;
		acct1 = budgetptr->acctdr;
		budgetptr = (struct DBbudget *)*dbrecptr2;
		acct2 = budgetptr->acctdr;
		cmp = strcmp(acct1,acct2);
		if (cmp != 0) return(cmp);

		budgetptr = (struct DBbudget *)*dbrecptr1;
		acct1 = budgetptr->acctcr;
		budgetptr = (struct DBbudget *)*dbrecptr2;
		acct2 = budgetptr->acctcr;
		cmp = strcmp(acct1,acct2);
		if (cmp == 0) {
			if (acct1 < acct2) return(-1);
			else return(1);
		}
		return(cmp);
		break;

	case RLJETRAN:
	default:
		return(0);
	}
}

