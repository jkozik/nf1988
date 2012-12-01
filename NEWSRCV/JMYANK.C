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

#include "vv_sys.h"

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

#include "JSdefs.h"
#include "JSstruct.h"
#include "JSextern.h"

/* Global Definitions */
struct JSyankrec JSyanktab[MAXYANK];
int JSycnt,JSynxt;

/* Funcition Templates */

void
JMyank(cur,cnt)
struct JSfilerec *cur;
int cnt;
{
	/*
	** Yank 'cnt' records from JSfiletab starting at 'cur'
	*/
	struct JSfilerec *nxtptr;

	JSycnt = 0;
	nxtptr = cur;
	while (nxtptr != NULL && JSycnt<MAXYANK && JSycnt<cnt) {
		strcpy(JSyanktab[JSycnt].line,nxtptr->line);
		JSyanktab[JSycnt].prtlines = nxtptr->prtlines;
		JSycnt++;
		nxtptr = nxtptr->next;
	}
}

struct JSyankrec *
JMygetbeg(filename)
char *filename;
{
	/*
	** Get first record from yank buffer.
	** If JSycnt is 0, return NULL.
	*/

	/* return if JSycnt==0 */
	if (JSycnt == 0) 
		return(NULL);
	
	JSynxt = 1;
	/* set correct month name */
	JSyanktab[0].line[0] = filename[0];
	JSyanktab[0].line[1] = filename[1];
	return(&JSyanktab[0]);
}

struct JSyankrec *
JMygetnxt(filename)
char *filename;
{
	/*
	** Get next record from yank buffer
	** Return NULL on last record.
	*/

	if (JSycnt == JSynxt)
		return(NULL);

	/* set correct month name */
	JSyanktab[JSynxt].line[0] = filename[0];
	JSyanktab[JSynxt].line[1] = filename[1];
	return(&JSyanktab[JSynxt++]);
}
