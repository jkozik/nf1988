#include "curses.h"
#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include <io.h>
#ifndef turboc
#include <search.h>
#include <direct.h>
#include <sys/types.h>
#endif
#include <stdlib.h>

#include <sys/stat.h>

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

#include "JSdefs.h"
#include "JSstruct.h"
#include "JSextern.h"

/* function templates */
long JEanalrpt(char *, char *);
char *JEsfix2s(char *, long);

/* Global definitions */
jebool subacct;
char prtstr[80];
FILE *analfp;
long runamt;

void
JManaldtl(acct) 
char *acct;
{
	int i;
	long monamt;
	char amtstr[20];

	char pglf[SZPATH+1];

	wclear(body);
	wrefresh(body);

	JMprtbody("analdtl: Starting...\n\r");

	/*
	** All output goes to file anal.out.
	*/
	if ((analfp=fopen("anal.out","w")) == NULL) {
		JMprtbody("analdtl: Output file cannot open\n\r");
		return;
	}
	JMwrprtsu(analfp);      /* printer setup string */

   (void) car_init();      /* initialize Content Addressible Array */
   subacct = CHsubacct(acct);

   runamt = 0;             /* running total */

	/* 
	** Generate report from 'month'.pgl
	*/
	/* for each month 00 - 12 */
	monamt = 0;
	for ( i=0; i<13; i++) {

		/* pglf=00.pgl */
		strcpy(pglf,months[i]);
		strcat(pglf,".pgl");

		/* if pglf exists, analyze month */
		if ( access(pglf,0) == 0) {
			monamt = monamt + JEanalrpt(months[i],acct);
         fprintf (analfp,"*YTD TOTAL %s -      %s*\n",months[i],JEsfix2s(amtstr,monamt));
		}

	}
   if (subacct) {
      fprintf(analfp,"\n**Sub-Account Totals -\n");
      for (i=0; i<carcnt; i++) {
         fprintf(analfp,"  %-18.18s",cartab[i].idx);
         fprintf(analfp," %s*",JEsfix2s(amtstr,cartab[i].amt));
         fprintf(analfp,"\n");
      }
   }
   fprintf (analfp,"**GRAND TOTAL -      %s**\n",JEsfix2s(amtstr,monamt));
	if (fclose(analfp) == EOF)
		JMprtbody("analdtl: close failed\n\r");

	JMprtbody("analdtl: Done.");
	return;
} 



long
JEanalrpt(month,acct)
char *month,*acct;
{
	FILE *pglfp;
	char pglf[SZPATH];
	char line[SZLINE];
   char *eoa, *cp, *desc;
	long lamt,totamt;
   int monrcnt,i;
	char amtstr[20];
   char amtar[GLAMOUNT+1], *amtp, *amtarp;

	/* Find all occurences of acct in the file month.pgl
	** and print out those records.  Give a total for month.
	*/


	strcpy(pglf,month);
	strcat(pglf,".pgl");

	lamt = 0;
	totamt = 0;
	monrcnt = 0;

	if ((pglfp=fopen(pglf,"r")) == NULL) {
		sprintf(prtstr,"analdtl: Error opening file-%s",pglf);
		JMprtbody(prtstr);
		return(0);
	}

	while ( fgets(line,SZLINE,pglfp) != NULL ) {
		if ( strncmp(acct,line+5,SZACCT) == 0) {
			/* Bump record count */
			monrcnt++;


			/* Convert amount to long int and accumulate */
         /* Get amount */
         amtarp = &amtar[0];
         amtar[0] = '\0';
         for( amtp=line+GLAMOUNT; *amtp!=',' && *amtp!='\n'; amtp++) {
            if( *amtp != '.' ){ *amtarp = *amtp; amtarp++; }
         }
         *amtarp = '\0';

         lamt = atol(amtar);
         runamt = runamt + lamt;


			totamt = totamt + lamt;

			/* Print input line, stick in decimal point
			** in amount:  1100 prints as 11.00
			*/
			eoa = strpbrk(line+GLAMOUNT,",\n"); /* assume success */
			fputc(' ',analfp);
			fputc(' ',analfp);
         /*
			for (cp=&line[0]; cp < line+GLAMOUNT; cp++) {
			   fputc(*cp,analfp);
			}
         */
         for (i=0; i<GLAMOUNT-1; i++) {
            if (i==2) fputc('/',analfp);
            if (i==4) { fputc(' ',analfp);continue;}
            fputc(line[i],analfp);
         }

         fprintf(analfp,"%s",JEsfix2s(amtstr,lamt));
         fprintf(analfp,"%s",JEsfix2s(amtstr,runamt));
			if(*eoa == ',') {
            fputc(' ',analfp);
            desc = eoa + 1;
            for (cp=eoa+1; *cp!='\n'; cp++) fputc(*cp, analfp);
            *cp = '\0';
         } else {
            *desc = '\0';
         }
	 if (subacct) {
	    if ( *acct < CAPACCT ) {	/* if Balance Sheet Account */
		if( (eoa=strpbrk(desc," ")) != NULL ) *eoa='\0';
	    }
            *car(desc) = *car(desc) + lamt;
         }

			fputc('\n',analfp);


		}
	}

   if (monrcnt > 0 ) {
		fprintf (analfp,"  *TOTAL - %s*\n",JEsfix2s(amtstr,totamt));
   }
	if ( fclose(pglfp) == EOF) {
		JMprtbody("analdtl: Error closing file\n\r");
	}

	return(totamt);
}
char *
JEsfix2s(strout, lamt)
char *strout;
long lamt;
{
	char *sptr;
	sptr=strout;
	if (lamt>-100 && lamt<0) {
      sprintf (sptr,"     -0.%02d",abs((int)(lamt%100)));
   } else {
      sprintf (sptr,"%7ld.%02d",lamt/100,abs((int)(lamt%100)));
   }
	return(strout);
}
