#define SZCHTEXT 30
#define SZACCT 3
#define SZAMT 10
#define SZDATE 4
#define SZMON 2
#define SZDESC 30
#define SZLINE 255
#define MAXCHART 400
#define MAXJEINPREC 550
#define SZPATH 30

#define MONTHS 12+1
#define MAXMONCNT MONTHS+1
#define CAPACCT '5'
#define EXPACCT '6'
#define INCACCT '8'
#define EXPACCUM MAXMONCNT-1

#define SZMON 2
#define GLMON 0
#define GLACCT 5
#define GLAMOUNT 9
#define SZA11 1
#define SZA12 2

#define JESUCCESS 0
#define JEFAIL -1

#define SUMMARY 1
#define DETAILED 2

#define ERROR(text) fprintf(stderr,"Record-%d, %s ERROR:\n%s\n",rec_cnt,text,line);inperrcnt++;
