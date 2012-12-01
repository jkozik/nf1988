/*		PFextern.h - Global externals		*/

/*----------------------------------------------------------------------------*/
/* Global function templates                                                  */
/*----------------------------------------------------------------------------*/
void PFexit(int);
int PFerrh(char *);
void MDmnproc(void);

/*----------------------------------------------------------------------------*/
/* Data Base Function Templates                                               */
/*----------------------------------------------------------------------------*/
DBRET    DBinit(void);
DBFILEID DBopen(RELTYPE);
DBRET    DBclose(DBFILEID);
BOOL     DBismodfd(DBFILEID);
int      DBrecnum(DBFILEID);
int      DBtotrec(DBFILEID);

DBRET    DBimport(DBFILEID,char *);
DBRET    DBexport(DBFILEID,char *);

DBRECPTR DBrdfirst(DBFILEID,DBRECPTR);
DBRECPTR DBrdlast(DBFILEID,DBRECPTR);
DBRECPTR DBrdnext(DBFILEID,DBRECPTR);
DBRECPTR DBrdprev(DBFILEID,DBRECPTR);
DBRECPTR DBrdseek(DBFILEID,int,DBRECPTR);

DBRET    DBselect(DBFILEID,SELECTRET (*)());

DBRET    DBinsrec(DBFILEID,DBRECPTR);
DBRET    DBapprec(DBFILEID,DBRECPTR);
DBRET    DBdelrec(DBFILEID);

DBRET    DBsort(DBFILEID, int (*)(DBRECPTR *,DBRECPTR *));
DBRET    DBmerge(DBFILEID,DBFILEID, int (*)(DBRECPTR *,DBRECPTR*));
int	 DBcmpacct(DBRECPTR *,DBRECPTR *);
/*----------------------------------------------------------------------------*/
/* View/Edit Commands                                                         */
/*----------------------------------------------------------------------------*/
void VEfsave(void);
void VEfload(void);
void VEfnew(void);

int VEpgup(void);
int VEpgdn(void);
int VEhome(void);
int VEend(void);
int VErefresh(void);
int VEup(void);
int VEdn(void);

int (*formdsp)();
int (*tabdsp)();
int VEfdjetran(void);
int VEfdbudget(void);
int VEfdchart(void);
int VEtdjetran(void);
int VEtdbudget(void);
int VEtdchart(void);


/*----------------------------------------------------------------------------*/
/* Menu Driver Functions                                                      */
/*----------------------------------------------------------------------------*/
int MDnotyet(char *);
void MDstatus(int,char *);
void MDstatoff(void);
void MDdialog1(char *);
int MDdialog2(char *);
int MDprompt1(int, int, char *, char *, int, char *);

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
extern DBFILEID chartid,jetranid,preglid,spreglid,budgetid;
extern char DBselstr[20];
extern char PFerrln1[80],PFerrln2[80];
extern struct PFerrs PFerrgdata;

extern WINDOW MDstatwn;
extern int MDchnum;
extern MDAPPTR MDcurap;
extern MDAP MDjetran;
extern MDAP MDbudget;
extern MDAP MDchart;
extern MDSETTINGS MDset;
