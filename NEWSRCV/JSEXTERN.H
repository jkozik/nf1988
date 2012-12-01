/* Function Templates */
/* jsedit.c */
menu JMstart(UCHAR,struct bufinfo *);
void JMpregl(void);
void JSdspmenu(menu,struct bufinfo *);
void JMmsg(char *);
void JMprtbody(char *);
void JSnotyet(char *);
void main(int, char **);
void JManaldtl(char *);
int JMglrpt(void);
int JMaarpt(void);
UCHAR wprmtafld(WINDOW *, char *, char *);

/* jmfile.c */
menu JMfile(UCHAR,struct bufinfo *);
void JMnew(struct bufinfo *);
int JMload(struct bufinfo *);
void JMsave(char *,struct JSfilerec *);
void JMinsrec(struct JSfilerec *,struct JSfilerec **, int *, jebool *,struct JSfilerec *,char *,int);
void JMapdrec(struct JSfilerec **,struct JSfilerec **, int *, jebool *,struct JSfilerec *,char *,int);
void JMdelrec(struct JSfilerec *,struct JSfilerec **,struct JSfilerec **,int *,jebool *);
struct JSfilerec *JMgetfree(void);
UCHAR wprmtch(WINDOW *, char *);
void JMudsave(struct JSfilerec *);
void JMudclr(void);
int JMundo(void);

/* jmacctfld */
UCHAR wacctfld(WINDOW *, char *, int);
void JMchhelp(WINDOW *, char *);

/* jmfld.c */
void wgetfld(WINDOW *, char *, int);
void wprmtfld(WINDOW *, char *, char *);
UCHAR wfixdfld(WINDOW *, char *, int);
UCHAR wamtfld(WINDOW *, char *, int);

/* jmedit.c */
menu JMedit(UCHAR,struct bufinfo *);
void JMdspg(struct JSfilerec *);
int JMdsrec(struct JSfilerec *,int);
struct JSfilerec *JMpgbk(struct JSfilerec *);
struct JSfilerec *JMpgfwd(struct JSfilerec *);
struct JSfilerec *JMinsert(struct bufinfo *,struct JSfilerec *,struct JSfilerec *, struct JSfilerec **, struct JSfilerec **);
struct JSfilerec *JMsearch(char *,struct JSfilerec *,struct JSfilerec *);
struct JSfilerec *JMput(struct bufinfo *,struct JSfilerec *,struct JSfilerec *, struct JSfilerec **, struct JSfilerec **);
struct JSfilerec *JMposcur(struct JSfilerec *,struct JSfilerec *);
int JMlnsdwn(struct JSfilerec *,struct JSfilerec *);
int JMlnedcvt(char *);

/* JMyank.c */
void JMyank(struct JSfilerec *,int);
struct JSyankrec *JMygetbeg(char *);
struct JSyankrec *JMygetnxt(char *);

/* jmlnedit.c */
LNEDRET JMlnedit(struct JSfilerec *,char *);
void JMlnedinit(struct JSfilerec *);

/* jeglvalid.c */
char *getdesc(char *);


/* curses.h */
void _winflag(WINDOW *,int,int);

/* GDreport.c */
int GDload(GDLIST *, char *);
void GDunload(GDLIST *);
void GDhome(GDLIST *);
void GDend(GDLIST *);
void GDdspg(GDLIST *);
void GDcurup(GDLIST *);
void GDcurdn(GDLIST *);
void GDpgup(GDLIST *);
void GDpgdn(GDLIST *);
void GDsearch(GDLIST *, char *);
GDLIST *GDdefine(void);
void GDundef(GDLIST *);

/* JMreport.c */
menu JMreport(UCHAR);
menu JMsettings(UCHAR);
menu JMreprd(UCHAR);
menu JMrepdisp(UCHAR);
void JMwrprtsu(FILE *);
char *JEsfix2s(char *, long);
