#include <stdio.h> 
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


/* function templates */
void JEinpchk(char *);

void
main()
{
	int i;

/* Setup GL environment */
(void) GLenvsetup();

/* Read in chart of accounts file into array, charttab.
** This array will be queried to validate account numbers.
*/
(void)CHload();

/*
** Check for the status of each of the JE input files (00, 01, ..., 12).
*/
for ( i=0; i < 13; i++){
	(void)JEinpchk(months[i]);
}

/* Restore working directory */
chdir(cwdstr);
} /* end of main */

void
JEinpchk(jeinpf)
char *jeinpf;
{
	struct stat sbuf1;
	struct stat sbuf2;
	struct stat sbuf3;
	FILE *jeinpfp,*pglfp;
	char pglf[SZPATH];
	char sglf[SZPATH];
	int srcp,srcs;
	int vrc;

	/* Check status of file
	** For purposes of comments the file name is '00'
	** If 00 does not exist, no processing required.
	*/
	if (stat(jeinpf,&sbuf1) != 0)
		return;  /* if the file does not exist, it's okay. */
	
	/* 
	** Construct file name string for 00.pgl
	*/
	strcpy(pglf,jeinpf);
	strcat(pglf,".pgl");
	srcp = stat(pglf,&sbuf2);
	strcpy(pglf,jeinpf);
	strcat(pglf,".pgl");

	/* 
	** Construct file name string for 00.sgl
	*/
	strcpy(sglf,jeinpf);
	strcat(sglf,".sgl");
	srcs = stat(sglf,&sbuf3);
	strcpy(sglf,jeinpf);
	strcat(sglf,".sgl");


	/*
	** if 00 has been modified since 00.pgl, regenerate 00.pgl and 00.sgl
	** if 00.pgl does not exist and 00 does, generate 00.pgl and 00.sgl
	** if 00.sgl does not exist and 00 does, generate 00.pgl and 00.sgl
	*/
	if (srcp == 0 && sbuf1.st_mtime > sbuf2.st_mtime || srcs || srcp){

		printf("Processing JE Input file - %s\n",jeinpf);

		/* The preceding 'stat' calls assure that the following
		** opens should always be successful, check for fail anyway.
		*/
		vrc=-1;
		if ((jeinpfp=fopen(jeinpf,"r")) == NULL)
			perror("JE input file cannot open");

		else if ((pglfp=fopen(pglf,"w")) == NULL)
			perror("Pregl Output file cannot open");

		else vrc=JEvalinp(jeinpfp,pglfp);

		/* These closes should never fail, check anyway
		*/
		if (fclose(jeinpfp) == EOF)
			perror("jeinpfp close failed");
		if (fclose(pglfp)   ==EOF)
			perror("pglfp close failed");

		/* Check JEvalinp error count
		** if >0, then delete 00.pgl file
		*/
		if (vrc > 0) {
			fprintf(stderr,"pregl: %d errors found, %s file not created\n",vrc,pglf);
			unlink(pglf); /* ignore if cannot delete */
		} else { /* create  00.sgl */
			if (JEglsort(pglf,sglf) == NULL) {
				fprintf(stderr,"pregl: sort failed, %d not created\n",sglf);
				unlink(sglf);
			}
		} /* if "Errors were found validating 00" */

	} /* If "New 00.pgl and 00.sgl are needed" */
}

