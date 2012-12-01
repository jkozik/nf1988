/*		PFstruct.h - Global structure definitions	*/

/*----------------------------------------------------------------------------*/
/* Data Base Structures                                                       */
/*----------------------------------------------------------------------------*/
#define MAXACCTAMT 15
struct DBjetran {
	DMmonth mm;
	DMday dd;
	DMdesc desc;
	DMacct cracct;
	struct  {
		DMacct acct;
		DMamt amt;
	} p[MAXACCTAMT];
};

struct DBchart {
	DMgenacct acct;
	DMdesc desc;
	DMoldacct oacct;
};

struct DBpregl {
	DMmonth mm;
	DMday dd;
	DMacct acct;
	DMamt amt;
	DMdesc desc;
};

struct DBbudget {
	DMacct acctdr;
	DMacct acctcr;
	DMdesc desc;
	DMbudamt amt[12];
};
typedef char DBbuffer[sizeof(struct DBjetran)];  /* assume DBjetran is biggest */

/*----------------------------------------------------------------------------*/
/* Menu Driver data structures                                                */
/*----------------------------------------------------------------------------*/

typedef struct MDap {
	RELTYPE rel;
	FILEPATH dfltfn,curfn,prevfn;
	DBFILEID yankid,curfid,prevfid;
	DBRECPTR recptr;
	PFI formdsp,tabdsp;
	BOOL vutable;
	DFORMPTR fmp;
	DBbuffer buf;
	WINDOW tabwn;
	int toprn,crsrn;
} MDAP, *MDAPPTR;

typedef struct MDrpt {
	char *name;
	int linepage;
	BOOL headings;
	int charline;
	int detaillvl;
} MDRPT, *MDRPTPTR;

typedef enum {
	FFILE, 
	FILEBROWSE, 
	CITOH, 
	LASERJET
} OUTPUT_TO;
#define MAXREPORTS 7

typedef char DMyear[3];
typedef struct MDsettings {
	MDRPT rptset[MAXREPORTS];
	DMyear year;
	FILEPATH fdir;
	OUTPUT_TO out_to;
} MDSETTINGS, *MDSETPTR;

/*----------------------------------------------------------------------------*/
/* Global data structures                                                     */
/*----------------------------------------------------------------------------*/
struct PFerrs {
	char *filename;
	char *relname;
	char *line;
	int currow;
};
