#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#ifndef turboc
#include <search.h>
#include <direct.h>
#else
#include <dir.h>
#endif

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"


/* Define global variables */
struct chartrec charttab[MAXCHART];
int chrec_cnt;
int chcuridx;


void
CHload() {

FILE *cfptr;

char line[SZLINE];
char *textptr;
char *eot;


/* Read in chart of accounts file into array, charttab.
** This array will be queried to validate account numbers.
** Assume that 'chart' exists in the current directory.
*/

if ((cfptr = fopen("chart","r")) == NULL ) {
	perror ("CHload: cannot open chart");
	chdir(cwdstr);
	exit(1);
}
chrec_cnt = 0;

/* Get input lines */
while ( fgets(line,sizeof(line),cfptr) != (char *)NULL) {
	/* Read and validate for one of the following formats:
	** - a,[1-8],text[,...]
	** - a,[1-8][0-9],text[,...]
	** - a,[1-8][0-9][0-9a-f],text[,...] 
	*/
	if ( (strlen(line) < 4 ) ||
	(strncmp(line,"a,",2) != 0) ||
	(line[2] < '1' || line[2] > '8' ) ) 
	{
		fprintf(stderr,"CHload: Found invalid record in chart:\n");
		fprintf(stderr,"%s\n",line);
		chdir(cwdstr);
		exit(1);
	}

	/* Validate input record: a,1,text,... */
	if (line[3] == ',') {
		line[3] = '\0';
		textptr = line + 4;

	/* Validate input record: a,12,text,... */
	} else if ( line[4] == ',') {
		if (!isdigit(line[3])) {
			fprintf(stderr,"CHload: Account number invalid in chart:\n");
			fprintf(stderr,"%s\n",line);
			chdir(cwdstr);
			exit(1);
		}
		
		line[4] = '\0';
		textptr = line + 5;

	/* Validate input record: a,123,text,... */
	} else if ( line [5] == ',' ) {
		if ( !isdigit(line[4]) && line[4] < 'a' && line[4] > 'f') {
			fprintf(stderr,"CHload: Account number invalid in chart:\n");
			fprintf(stderr,"%s\n",line);
			chdir(cwdstr);
			exit(1);
		}
		line[5] = '\0';
		textptr = line + 6;

	/* Input record invalid */
	} else {
		fprintf(stderr,"CHload: Account number invalid in chart:\n");
		fprintf(stderr,"%s\n",line);
		chdir(cwdstr);
		exit(1);
	}

	/* Find end of text which is either nl or ',' */
	eot = strpbrk(textptr,",\n");
	*eot = '\0';

	/* Copy input record into charttab */
	if (chrec_cnt > 0 && strcmp(charttab[chrec_cnt-1].acct,line+2) > 0)
	{
		fprintf(stderr,"CHload: chart is not sorted in accending order:\n");
		fprintf(stderr,"%s\n",line);
		chdir(cwdstr);
		exit(1);
	}
	strcpy(charttab[chrec_cnt].acct,line+2);
	strcpy(charttab[chrec_cnt].text,textptr);
	chrec_cnt++;

}

if (fclose(cfptr) == EOF ) {
	perror ("CHload: cannot close chart");
	chdir(cwdstr);
	exit(1);
}

}
	
char *
CHvalid(acct)
char *acct;
{
	char acct_str[SZACCT + 1];
	struct chartrec *ctptr;

	/* lookup account in charttab 
	** - Return char pointer to chartab if found
	** - Return NULL if not found
	*/

	strncpy(acct_str,acct,SZACCT);
	acct_str[SZACCT] = '\0';
	ctptr = (struct chartrec *)bsearch((const char *)&acct_str[0],(const char *)charttab,chrec_cnt,sizeof(charttab[0]),strcmp);

	if (ctptr == NULL)
		return ( NULL );
	else
		return(ctptr->text);
}

char *
CHlookup(acct)
char *acct;
{
	char *text;

	/* lookup description of acct; 
	** return "** Invalid Account **" if account not found.
	*/
	text = CHvalid(acct);
	if (text == NULL)
		return("** Invalid Account **");
	else
		return (text);
}

	
struct chartrec *
CHgetfst()
{
	/* 
	** Get first chart of accounts record.
	** Use CHgetnxt() to get all others.
	*/
	chcuridx = 1;
	return(&charttab[0]);
}

struct chartrec *
CHgetnxt()
{
	/* 
	** Get next chart of accounts record.
	** Use CHgetfst() to get first record.
	** Return NULL when no more.
	*/
	if (chcuridx >= chrec_cnt)
		return(NULL);
	else
		return(&charttab[chcuridx++]);
}
