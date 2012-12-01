#ifndef turboc
#include <malloc.h>
#else
#include <malloc.h>
#endif

#include "curses.h"
#include <dos.h>
#include <io.h>
#include <string.h>
#include <ctype.h>
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

/* Global Definitions */
#define MAXGDREC	4000

/* Function Templates */
void GDdspg(GDLIST *);

int
GDload(list,fname)
GDLIST *list;
char *fname;
{
	FILE *fp;
	struct stat sbuf;
	char line[SZLINE];
	char prtstr[80];
	int rec_cnt;
	int isize;
	long totsize;



	/* Get the size, inbytes, of the input record */
	if ( stat(fname,&sbuf) < 0 ){
		JMprtbody("\nGDreport: stat cannot open input file");
		return(JEFAIL);
	}



	totsize = 0;
	rec_cnt = 0;

	/* Copy input file into memory */
	if ((fp=fopen(fname,"r")) == NULL) {
		JMprtbody("\nGDreport: cannot open input file");
		return(JEFAIL);
	}
	sprintf(prtstr,"Display: loading %s",fname);
	JMmsg(prtstr);

	while ( fgets(line,SZLINE,fp) != NULL) {
		isize=strlen(line);
		totsize=totsize+isize;
		rec_cnt++;
		/* check MAXGDREC */
		if (rec_cnt >= MAXGDREC) {
			sprintf(prtstr,"\n\rGDreport: File exceeds %d records.",MAXGDREC);
			JMmsg(prtstr);

			JMprtbody("\n\rGDreport: File Only Particially Readable\n");
			return(JEFAIL);
		}

		/* get memory for input line */
		list->line[list->curidx] = (char *)malloc(isize+2);
		if (list->line[list->curidx] == NULL){
			JMprtbody("\n\rGDreport: Ran out of memory for input file\n");
			JMprtbody("\n\rGDreport: File Only Particially Readable\n");
			return(JEFAIL);
		}

		/*
		sprintf(prtstr,"Display: Loading File-%s, Records-%d, Characters-%ld",fname,rec_cnt,totsize);
		JMmsg(prtstr); 
		*/

		*(list->line[list->curidx]) = '\0';
		strcpy(list->line[list->curidx],line);
		list->curidx++;
		list->eolidx++;

	} /* while */

	/* Input file read-in. Close it. */
   if (fclose(fp) != (int)NULL){
		JMprtbody("\n\rGDreport: cannot close input file");
	}

	sprintf(prtstr,"Display: Load Completed. File-%s, Records-%d, Characters-%ld",fname,rec_cnt,totsize);
	JMmsg(prtstr);

	return(JESUCCESS);
};

void
GDunload(list)
GDLIST *list;
{
	/*
	** Free up storage used by report display file
	*/

	int i;

	if (list == (GDLIST *)NULL) return;

	for (i=list->eolidx; i>0; i--) {
		free(list->line[i-1]);
		*(list->line[i-1])='\0';
	}
	list->curidx = 0;
	list->eolidx = 0;
	GDundef(list);
}
void
GDdspg(list)
GDLIST *list;
{
	/*
	** Display page, starting from GDcurlin for LINE-2 lines.
	** NOTE: do not display past list->eolidx.
	*/

	int i;
	scrollok(body,FALSE);
	wclear(body);

	waddstr(body,list->line[list->curidx]);
	for(i=list->curidx+1; i<list->curidx+LINES-2 && i<list->eolidx; i++) {
		waddch(body,'\r');
		waddstr(body,list->line[i]);
	}
	wrefresh(body);
	scrollok(body,TRUE);
	return;
}

void
GDhome(list)
GDLIST *list;
{
	/*
	** Display the first page, setting list->curidx equal to 0.
	*/

	list->curidx = 0;

	GDdspg(list);
	return;
}

void
GDend(list)
GDLIST *list;
{
	/*
	** Display the last page:
	**  set list->curidx = list->eolidx,
	**  then call GDpgup.
	*/

	if (list->eolidx == 0) return;

	list->curidx = list->eolidx;

	GDpgup(list);
	return;
}

void
GDpgdn(list)
GDLIST *list;
{
	/*
	** Move list->curidx forward LINES-2
	*/
	int saveidx;

	saveidx = list->curidx + LINES-2;

	if (saveidx>=list->eolidx) {
		if (saveidx == list->eolidx) {
			beep();
			return;
		}
		list->curidx=list->eolidx;
		GDpgup(list);
	} else {
		list->curidx = saveidx;
		GDdspg(list);
	}
	return;
}
void
GDpgup(list)
GDLIST *list;
{
	/*
	** Move list->curidx back LINES-2
	*/
	int saveidx;
	/* beep if at beginning of file */
	if (list->curidx <= 0) {
		list->curidx = 0;
		beep();
		return;
	}

	saveidx = list->curidx - (LINES-2);

	if (saveidx<0) {
		list->curidx = 0;
	} else {
		list->curidx = saveidx;
	}
	GDdspg(list);
	return;
}


void
GDcurup(list)
GDLIST *list;
{
	/*
	** Move list->curidx back one line
	*/
	if (list->curidx <= 0) {
		list->curidx = 0;
		beep();
		return;
	}

	list->curidx--;
	GDdspg(list);
	return;
}
void
GDcurdn(list)
GDLIST *list;
{
	/*
	** Move list->curidx forward one line
	*/
	if (list->curidx+1 >= list->eolidx) {
		beep();
	} else {
		list->curidx++;
		GDdspg(list);
	}
	return;
}

void
GDsearch(list,str)
GDLIST *list;
char *str;
{
	/*
	** Search for 'str' -
	** - starting from the current cursor position
	** - if not found before eof, start searching at beginning of file
	*/

	char *curchr;
	int curline;
	int len;
   jebool anchored;

   anchored=JEFALSE;
	JMmsg("Searching...");
   curchr = list->line[list->curidx+1];
   curline=list->curidx+1;        /* start searching after current line */
	len = strlen(str);
   /*
   ** Test if searching for a three digit account number.
   ** If str="XXX^" then anchor search on 1st column
   */
   if (len==4 && str[3]=='^') {
      str[3]='\0';
      len=3;
      anchored=JETRUE;
   }
	while (curline<list->eolidx && strncmp(str,curchr,len)!=0) {
      if (*curchr == '\0' || anchored) {
			curline++;
			curchr = list->line[curline];
		} else {
			curchr++;
		}
	}
	if (strncmp(str,curchr,len) == 0) {
		list->curidx = curline;
		GDdspg(list);
		JMmsg("");
		return;
	}
	/* not found, so far.  try searching at beginning of file. */
	JMmsg("Search: Wrapped around file.");

	curchr=list->line[0];
	curline=0;
	while (curline<list->curidx && strncmp(str,curchr,len)!=0) {
      if (*curchr == '\0' || anchored) {
			curline++;
			curchr = list->line[curline];
		} else {
			curchr++;
		}
	}
	if (strncmp(str,curchr,len) == 0) {
		list->curidx = curline;
		GDdspg(list);
		JMmsg("Search: Wrapped around file - FOUND");
		return;
	} else {
		JMmsg("Search: Not found.");
		return;
	}
	return;
}
GDLIST *
GDdefine()
{
	/* 
	** Allocate memory for a GDLIST structure.
	*/
	GDLIST *list;
	list = (GDLIST *)malloc(sizeof(GDLIST));
	list->line = (char **)malloc(MAXGDREC * sizeof(char *));
	list->curidx = 0;
	list->eolidx = 0;
	return(list);

}
void GDundef(list)
GDLIST *list;
{
	/*
	** Deallocate memory for GDLIST
	*/
	free(list->line);
	free(list);
	list = (GDLIST *)NULL;
	return;
}
