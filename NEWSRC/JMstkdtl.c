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
long JEstkdtl(char *, char *);


/* Global definitions */
jebool subacct;
char prtstr[80];
FILE *stkdtlfp;
long runamt;

void
JMstkdtl(ticker) 
char *ticker;
{
	//int i;
	long monamt;
	char amtstr[20], stkdtlcmd[SZPATH];

	//char pglf[SZPATH+1];

	wclear(body);
	wrefresh(body);

	JMprtbody("stkdtl: Starting...\n\r");
#if FALSE
	/*
	** All output goes to file stkdtl.out.
	*/
	if ((stkdtlfp=fopen("stkdtl.out","w")) == NULL) {
		JMprtbody("stkdtl: Output file cannot open\n\r");
		return;
	}


   runamt = 0;             /* running total */
 
   fprintf (stkdtlfp,"**GRAND TOTAL -      %s**\n",JEsfix2s(amtstr,monamt));
	if (fclose(stkdtlfp) == EOF)
		JMprtbody("stkdtl: close failed\n\r");
#endif 

	strcpy( stkdtlcmd, "\\nf\\newsrc\\stkdtl " );
	strcat( stkdtlcmd, ticker );
	system( stkdtlcmd );		

	JMprtbody("stkdtl: Done.");
	return;
} 



long
JEstkdtl(month,acct)
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
		sprintf(prtstr,"stkdtldtl: Error opening file-%s",pglf);
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
			fputc(' ',stkdtlfp);
			fputc(' ',stkdtlfp);
         /*
			for (cp=&line[0]; cp < line+GLAMOUNT; cp++) {
			   fputc(*cp,stkdtlfp);
			}
         */
         for (i=0; i<GLAMOUNT-1; i++) {
            if (i==2) fputc('/',stkdtlfp);
            if (i==4) { fputc(' ',stkdtlfp);continue;}
            fputc(line[i],stkdtlfp);
         }

         fprintf(stkdtlfp,"%s",JEsfix2s(amtstr,lamt));
         fprintf(stkdtlfp,"%s",JEsfix2s(amtstr,runamt));
			if(*eoa == ',') {
            fputc(' ',stkdtlfp);
            desc = eoa + 1;
            for (cp=eoa+1; *cp!='\n'; cp++) fputc(*cp, stkdtlfp);
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

			fputc('\n',stkdtlfp);


		}
	}

   if (monrcnt > 0 ) {
		fprintf (stkdtlfp,"  *TOTAL - %s*\n",JEsfix2s(amtstr,totamt));
   }
	if ( fclose(pglfp) == EOF) {
		JMprtbody("stkdtldtl: Error closing file\n\r");
	}

	return(totamt);
}
