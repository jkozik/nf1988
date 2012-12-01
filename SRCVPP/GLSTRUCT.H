struct chartrec {
	char acct[SZACCT+1];
	char text[SZCHTEXT+1];
};
extern struct chartrec charttab[MAXCHART];

struct jefilerec {
	FILE *fp;
	struct jefilerec *nxtje;
	char line[SZLINE];
};

struct jefileinp {
	char date[SZDATE+1];
	char mon[SZMON+1];
	char acct[SZACCT+1];
	char a11[SZA11+1];
	char a12[SZA12+1];
	long amt;
	char desc[SZDESC+1];
};

typedef enum {JEFALSE=0, JETRUE=1} jebool;

extern struct jefilerec jefiletab[MONTHS];
extern char cwdstr[SZPATH+1];
extern int chrec_cnt;
extern char *year;
extern char *froot;
extern char *months[MONTHS];
