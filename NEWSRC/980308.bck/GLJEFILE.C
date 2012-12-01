#include "curses.h"
#ifndef turboc
#include <direct.h>
#endif
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

#include "JSdefs.h"
#include "JSstruct.h"
#include "JSextern.h"

/* define global variables */
struct jefilerec *headje;
struct jefilerec jefiletab[MONTHS];
struct jefileinp jefields;

/* function templates */
int acctcmp(struct jefilerec *, struct jefilerec *);
struct jefileinp *GLjeparse(char *);


void
GLjeopen()
{
	char sglf[SZPATH+1];
	struct jefilerec *tabptr;
	int monidx;


JMprtbody("The following months are being processed:\n\r");

for ( monidx=0; monidx<MONTHS; monidx++) {

	/* zap jefilerec entry */
	tabptr = &jefiletab[monidx];
	tabptr->fp = NULL;
	tabptr->line[0] = '\0';
	tabptr->nxtje = NULL;

	/* sglf=00.sgl */
	strcpy(sglf,months[monidx]);
	strcat(sglf,".sgl");

	/* if sglf exists, analyze month */
	if ( (tabptr->fp=fopen(sglf,"r")) != NULL) {
		JMprtbody(months[monidx]);
		JMprtbody(" ");
		if (fgets(tabptr->line,SZLINE,tabptr->fp) != NULL) {
			/* insert record into jefile linked list */
			GLjeins(tabptr);
		}
	}

} /* end for */

JMprtbody("\n\r");

} /* return from GLjeopen() */

void
GLjeins(insptr)
struct jefilerec *insptr;
{
	/*
	** Insert line into ordered linked list of je file records.
	** Each record is linked to the next largest record.
	** The pointer, headje, points to the smallest record in the list.
	** The acending sequence is defined by account number and month.
	** If all account numbers are the same, the linked list will
	** be ordered by month.
	*/

	struct jefilerec *monptr, *prevptr;

	/* Test for if the list is empty */
	if (headje == NULL) {
		headje = insptr;
		headje->nxtje = NULL;
		return;
	}

	/* If the inserted line is less than the head of the list */
	if ( acctcmp(headje, insptr) > 0 ) {
		insptr->nxtje = headje;
		headje = insptr;
		return;
	}

	/* Search thru sorted linked list, insert in acending order */
	monptr = headje;
	while ( monptr != NULL && acctcmp(monptr, insptr) < 0 ) {
		prevptr = monptr;
		monptr = monptr->nxtje;
	}
	insptr->nxtje = monptr;
	prevptr->nxtje = insptr;

}


int
acctcmp(je1, je2)
struct jefilerec *je1, *je2;
{
	int scret;

	scret = strncmp (je1->line+5, je2->line+5, SZACCT);

	/* if the account number fields of the input fields are equal,
	** compare the months.  The function should never return 0 (equal).
	*/
	if (scret == 0 ){
		if ( je1 < je2 )
			return (-1);
		else
			return (1);
	} else return (scret);
}


void
GLjedel(delptr)
struct jefilerec *delptr;
{
	struct jefilerec *monptr,*prevptr;

	/* Find and delete line from sorted linked list */

	/* If list is empty, do nothing */
	if (headje == NULL)
		return;

	/* If deleting from head */
	if ( delptr == headje ) {
		headje = headje->nxtje;
		delptr->nxtje = NULL;
		return;
	}

	/* Search thru linked list */
	monptr = headje;
	prevptr = headje;
	while ( monptr != NULL && monptr != delptr ) {
		prevptr = monptr;
		monptr = monptr->nxtje;
	}

	/* if a match was found, unlink */
	if ( monptr == delptr ) {
		prevptr->nxtje = delptr->nxtje;
		delptr->nxtje = NULL;
	}
}

struct jefileinp *
GLjegetnxt(line)
char *line;
{
	struct jefilerec *monptr,*jefptr;
	int i;
	char prmtstr[40];

	/* return the next record in ascending sequence from the jefiles
	** The next record is at the head of the jefiletab linked list.
	** Copy the characters from the input buffer into the calling
	** buffer.  If the linked list is empty, return NULL
	*/

	/* test for no remaining input */
	if ( headje == NULL ) {
		for ( i=0; i < MONTHS; i++) {
			jefptr = &jefiletab[i];
			if (jefptr->fp != 0 || jefptr->nxtje != NULL || jefptr->line[0] != '\0'){
			   sprintf(prmtstr,"GLjefile: error found after all je files read.  File-%s.sgl\n\r",months[i]);
			   JMprtbody(prmtstr);
			}
		}
		return (NULL);
	}

	/* copy the next input record into 'line' */
	strcpy(line, headje->line);
	strcpy(headje->line, "");
	
	/* read the next record for the input je file */
	monptr = headje;
	GLjedel(headje); /* remove old input from linked list */
	if ( fgets(monptr->line, SZLINE, monptr->fp) != NULL ) {
		GLjeins(monptr);
	} else {
      if (fclose(monptr->fp)==EOF){
         fprintf(stderr,"GLjefile: line-'%s'\n",line);
			perror("error closing file");
      } else {
			monptr->fp = NULL;
      }
	}

	/* parse, assume valid input */
	return(GLjeparse(line));
}

struct jefileinp *
GLjeparse(line)
char *line;
{
	char *eoa,*sgldesc_ptr;
   char amtar[GLAMOUNT+1], *amtp, *amtarp;

	/*
	** parse fields from 00.sgl file input record:
	**  0101,101,1200,desc    -or-
	**  0101,101,1200
	**
	** 1-date, account-2, amt-3, desc-4
	*/

	/* Get date and month */
	strncpy(jefields.date,line,SZDATE);
	jefields.date[SZDATE] = '\0';
	strncpy(jefields.mon,line,SZMON);
	jefields.mon[SZMON] = '\0';

	/* Get account */
	strncpy(jefields.acct,line+GLACCT,SZACCT);
	jefields.acct[SZACCT] = '\0';

	/* Get subaccount fields: A11, A12 */
	strncpy(jefields.a11,line+GLACCT,SZA11);
	jefields.a11[SZA11] = '\0';
	strncpy(jefields.a12,line+GLACCT,SZA12);
	jefields.a12[SZA12] = '\0';

	/* Get amount */
   amtarp = &amtar[0];
   amtar[0] = '\0';
   for( amtp=line+GLAMOUNT; *amtp!=',' && *amtp!='\n'; amtp++) {
      if( *amtp != '.' ){ *amtarp = *amtp; amtarp++; }
   }
   *amtarp = '\0';

   jefields.amt = atol(amtar);

	/* Get description */
	eoa = strpbrk(line+GLAMOUNT,",\n"); /* assume success */
	if (*eoa != ',') {
		jefields.desc[0] = '\0';
	} else {
		/* strip off newline */
		sgldesc_ptr = eoa + 1;
		eoa = strpbrk(sgldesc_ptr,"\n"); /* assume success */
		*eoa = '\0';
		strncpy(jefields.desc,sgldesc_ptr,SZDESC);
		jefields.desc[SZDESC] = '\0';
	}


	return(&jefields);
}
