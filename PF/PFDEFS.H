/*		PFdefs.h - Global defines		*/

/*----------------------------------------------------------------------------*/
/* Data Base Type Defs                                                        */
/*----------------------------------------------------------------------------*/
typedef enum {
	RLJETRAN=1,
	RLCHART=2,
	RLPREGL=3,
	RLBUDGET=4
} RELTYPE;

typedef enum {
	MATCH,
	NOMATCH
} SELECTRET;

typedef int BOOL;

typedef enum {
	DMACCT=1,
	DMAMT=2,
	DMDESC=3,
	DMMONTH=4,
	DMDAY=5,
	DMOLDACCT=6,
	DMGENACCT=7,
	DMBUDAMT=8
} DMTYPE;

typedef int DBFILEID,DBRET;
typedef long DMamt,DMbudamt;
typedef char *DBRECPTR,*DMPTR;
typedef char DMmonth[3],DMday[3];
typedef char DMacct[4],DMoldacct[4],DMgenacct[4];
typedef char DMdesc[31];

/*----------------------------------------------------------------------------*/
/* Main definitions                                                           */
/*----------------------------------------------------------------------------*/
#define SZPATH 30
typedef char FILEPATH[SZPATH],*FILEPATHPTR;


/*----------------------------------------------------------------------------*/
/* Error Message Definitions                                                  */
/*----------------------------------------------------------------------------*/
#define BADREL 100	/* Relation number is out of range (0<rel<MAXREL)     */
#define DBFULL 101	/* Maximum database files opened (MAXDBFILE)          */
#define BADDBFID 102	/* Database file id is out of range                   */
#define BADDOMAIN 103	/* Domain is out of range (0<domain<MAXDMDESCTAB)     */
#define BADDELIM 104	/* Found unexpected delimitor (comma, newline, etc.)  */
#define ACCTOVFLOW 105	/* More that MAXACCTAMT pairs found in JETRAN         */
#define BADAMTCNT 106	/* More than 12 amounts found in BUDGET input file    */
#define BADLEN 107	/* Unexpected count of characters found for domain    */
#define BADMONTH 108	/* Month found out of range			      */
#define BADDAY 109	/* Day found out of range			      */
#define BADAMT 110	/* Amount not valid                                   */
#define BADACCTCHART 111	/* Account not found in chart                 */
#define BADMERGEREL 112	/* Relations types different                          */

#define UNKDIR 120	/* Directory \$F\$YEAR does not exist                 */
#define MISSING00 121	/* File '00' does not exist                           */
#define MISSINGCHART 122	/* File 'chart' does not exist                */
