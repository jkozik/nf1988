typedef enum {
	start,
	file,
	edit,
	editz,
	lnedit,
	report,
   repset,
	analrd,
	analdisp,
	glrptrd,
	glrptdisp,
	aarptrd,
	aarptdisp,
   quit,
   quikadtl
} menu;
extern menu state;

struct JSfilerec {
	char line[SZLINE+1];
	struct JSfilerec *next;
	struct JSfilerec *prev;
	int prtlines;
};
extern struct JSfilerec JSfiletab[MAXJEFILE];

struct JSundorec {
	char line[SZLINE+1];
	struct JSfilerec *rec;
	struct JSfilerec *next;
	struct JSfilerec *prev;
	int prtlines;
};
extern struct JSundorec JSundotab[MAXUNDO];

struct JSyankrec {
	char line[SZLINE+1];
	int prtlines;
};
extern struct JSyankrec JSyanktab[MAXYANK];

typedef enum {
	ENTRY,
	ENTRY_ESC,
	ESCONLY
} LNEDRET;

struct JSlnedrec {
	char day[SZDATE+1];
	struct {
		char acct[SZACCT+1];
		char amt[SZAMTFLD+1];
	} ln[MAXACCTS];
	char desc[SZDESC+1];
	int accts;
	char line[SZLINE+1];
};
extern struct JSlnedrec JSlnedtab;

typedef enum {
	LE_STARTLN,
	LE_DATE,
	LE_ACCT,
	LE_AMT,
	LE_DESC,
	LE_ENDLN,
	LE_DONE
} LE_STATE;

struct bufinfo {
	struct JSfilerec *JShead;
	struct JSfilerec *JStail;
	struct JSfilerec *JScurptr;
	struct JSfilerec *JStopptr;
	int JSrec_cnt;
	jebool fileopened;
	jebool filechgd;
	char filename[SZPATH];
	char filetmp[SZPATH];
};
extern struct bufinfo b1;
extern struct bufinfo prevb1;

/* content addressable array data structures */
struct CARREC {
   char idx[SZIDX];
   long amt;
};
extern struct CARREC cartab[MAXCAR];
extern int carcnt,lastidx;

extern WINDOW *menuline,*body,*prompt,*message,*chartbord,*charttext;
extern int JSrecend; /* last record in JSfiletab[] */

extern jebool JSpregluptodate;
extern char searchstr[10];

typedef struct {
	char **line;
	int curidx;
	int eolidx;
} GDLIST;
extern GDLIST *GDanal,*GDglrpt,*GDaarpt;
extern jebool JMheadon;
extern int JMlinespage;
extern char JMpsetup[30];
extern char curcracct[SZACCT+1];
