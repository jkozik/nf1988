#include <io.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#ifndef turboc
#include <direct.h>
#include <sys/types.h>
#include <search.h>
#endif
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

/* Define Global Variables */

/* Current Report Level Data */
char curacct[SZACCT+1];

/* Total accumulators */
long totacct;
long incsumcr; /* total income */
long incsumdr; /* total expenses */


/* Report Level Changed Flags */
jebool first_rec;
jebool acct_chgd;

char line[SZLINE];
struct jefileinp *jefld_ptr;

FILE *new00_fp;

/* Function templates */
void GLinit(),GLclsu();
jebool GLctrlbrk(struct jefileinp *);
void GLsubtotals(struct jefileinp *);
void GLdtl(struct jefileinp *);
void GLfinals();
void GLpsumline(char *, long, char *);

void
main()
{

/* Setup GL environment */
(void)GLenvsetup();

/* Open new00 file */
(void)GLclsu();

(void)GLinit();

/* Detail Record Processing */
while ( (jefld_ptr=GLjegetnxt(line)) != NULL) {

	if (GLctrlbrk(jefld_ptr) == JETRUE)
		(void)GLsubtotals(jefld_ptr);

	(void)GLdtl(jefld_ptr);
}

(void) GLfinals();

/* close new00 */
if (fclose(new00_fp) == EOF)
	perror("could not close new00");



/* Restore working directory */
chdir(cwdstr);

} /* end of main */

jebool
GLctrlbrk(jefld)
struct jefileinp *jefld;
{
	/* Check for change in report level, generate subtotals */
	acct_chgd = JEFALSE;


	/* Check for change in acct */
	if ( strcmp(jefld->acct,curacct) ) {
		acct_chgd = JETRUE;
	}
	
	/* if a control break occurs, acct_chgd=JETURE */
	return(JETRUE);
}

void
GLsubtotals(jefld)
struct jefileinp *jefld;
{

	/* Process change in account number */
	if (acct_chgd == JETRUE) {
		if (*curacct < EXPACCT) {
			(void) GLpsumline(curacct,totacct,"Balance Forward");
		} else if (*curacct >= EXPACCT && *curacct != INCACCT) {
			incsumdr = incsumdr + totacct;
		} else if (*curacct == INCACCT) {
			incsumcr = incsumcr + totacct;
		} else {
			fprintf(stderr,"GLclose: Default account type, unexpected\n");
			JEinthand(1);
		}
		totacct = 0;
		strcpy(curacct,jefld->acct);
	}

}



void
GLinit()
{

/* clear out accumulaters */
totacct = 0;
incsumdr = 0;
incsumcr = 0;


/* initialize flags */
acct_chgd = JEFALSE;
first_rec = JETRUE;

/* Zap strings */
strcpy(curacct,"");

/* open JE files */
GLjeopen();

}

void
GLdtl(jefld)
struct jefileinp *jefld;
{

	/* total detail amount */
	totacct = totacct + jefld->amt;

}

void
GLfinals()
{
	char incacct[SZACCT+1];
	char finline[SZLINE];
	int iyear;

	/* force subtotals for all report levels */
	strncpy(finline,line,SZDATE);
	strcat(finline,",999,0000");
	strcpy(line,finline);
	jefld_ptr = GLjeparse(line);
	GLctrlbrk(jefld_ptr);
	(void)GLsubtotals(jefld_ptr);

	/*  Calculate income summary account number */
	iyear = atoi(year);
   if (iyear > 90 && iyear <= 99) {
      sprintf(incacct,"50%c",'a'+iyear-91);
   } else if (iyear < 82 || iyear > 99) {
		strcpy(incacct,"50?");
	} else {
		sprintf(incacct,"%3d",419+iyear);
	}
	/* print income summary amounts for year */
	(void) GLpsumline(incacct,incsumcr,"Balance Forward");
	(void) GLpsumline(incacct,incsumdr,"Balance Forward");

}

void
GLpsumline(acctstr,totamt,descptr)
char acctstr[SZACCT];
long totamt;
char *descptr;
{

	/* print total line -
	** 1. print account number
	** 2. print description
	** 3. print amount with 2 fixed decimal places
	*/

	if (first_rec == JETRUE) {
		first_rec = JEFALSE;
		return;
	}

	if (totamt != 0) {
		fprintf(new00_fp,"0000,%s,%ld.%.2d,%s\n",acctstr,totamt/100,abs((int)(totamt%100)),descptr);
	} 

}

void
GLclsu()
{
	char nextyear[3];
	struct stat sbuf1;
	char path[SZPATH+1];
	char newchart[SZPATH+1];
	char new00[SZPATH+1];

/* Open new00 file */

fprintf(stderr, "This script closes the current year by creating\n");
fprintf(stderr, "a new beginning balance file 00.\n");
fprintf(stderr, "Assuming closing year-'%s'\n",year);

strcpy(nextyear,year);
/* increment the nextyear string */
if (nextyear[1] == '9') {
	nextyear[0]++;
	nextyear[1] = '0';
} else {
	nextyear[1]++;
}

/* build path to new directory */
strcpy(path,"\\");
strcat(path,froot);
strcat(path,"\\");
strcat(path,nextyear);

/* does the new directory exist? */
if ((stat(path,&sbuf1) == 0 && sbuf1.st_mode&S_IFDIR != S_IFDIR) || stat(path,&sbuf1) == -1) {
	fprintf(stderr,"GLclose: The directory %s does not exists\n",path);
	JEinthand(1);
}

/* does the chart file exist for the new year? */
strcpy(newchart,path);
strcat(newchart,"\\chart");
if (access(newchart,0) != 0 ) {
	fprintf(stderr,"GLclose: The file '%s' does not exist\n",newchart);
	JEinthand(1);
}


/* open GLclose output file 'new00' */
strcpy(new00,path);
strcat(new00,"\\new00");
fprintf (stderr, "The new beginning balance file will be written to:\n %s\n",new00);
if ((new00_fp=fopen(new00,"w")) == NULL) {
	perror("could not open new00");
	JEinthand(1);
}
}
