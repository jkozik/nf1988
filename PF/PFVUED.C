/* PFvued.c - View/Edit Application files */

#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "stdio.h"
#include "io.h"
#include "wfd.h"
#include "PFdefs.h"
#include "PFstruct.h"
#include "PFextern.h"

/*----------------------------------------------------------------------------*/
/* Private View/Edit defines                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Private View/Edit Structures                                               */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Private View/Edit function templates                                       */
/*----------------------------------------------------------------------------*/
void VEtabdsp(void);

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/

/* budget derived fields */
DMdesc drdesc,crdesc;
char brecnumfld[15];

/* chart derived fields */
char crecnumfld[15];


/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                   VIEW/EDIT FUNCTIONS                                      */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* VEfload - Load file.  Filename in MDcurap->curfn.                          */
/*----------------------------------------------------------------------------*/
void
VEfload(void)
{
	char *fn="VEfload";

	INIT_MODULE(fn);

	/*
	** Test whether a modidified file is already loaded.
	*/
	if (MDcurap->curfid != 0 && DBismodfd(MDcurap->curfid) == YES) {
		VEfsave();
		MDcurap->prevfid = MDcurap->curfid;
	}

	/* 
	** Open data base entry
	*/
	MDstatus(LURGENT,"Loading...");
	MDcurap->curfid = DBopen(MDcurap->rel);

	/*
	** Read  in file
	*/
	DBimport(MDcurap->curfid, MDcurap->curfn);
	MDstatus(LMESSAGE,"Load Complete");
	MDstatoff();

	/*
	** Set cursor the beginning of file
	*/
	VEhome();

	EXIT_MODULE(fn);
	return;
}
/*----------------------------------------------------------------------------*/
/* VEfsave - Save file.  Filename in MDcurap->curfn.                          */
/*----------------------------------------------------------------------------*/
void
VEfsave(void)
{
	char *fn="VEfsave";
	FILEPATH filebck;
	char *dotptr;

	INIT_MODULE(fn);

	/*
	** Test whether a file is already loaded.
	*/
	if (MDcurap->curfid == 0) {
		EXIT_MODULE(fn);
		return;
	}

	/*
	** if file exists, rename it file.bck
	*/
	MDstatus(LURGENT,"Saving...");
	if (access(MDcurap->curfn,0) == 0) {
		/* force extention to .bck */
		strncpy(filebck,MDcurap->curfn,6);
		filebck[6]='\0';
		if ((dotptr=strchr(filebck,'.')) != NULLP)
			*dotptr = '\0';
		strcat(filebck,".bck");

		/* zap old backup file */
		remove(filebck);

		/* rename file */
		rename(MDcurap->curfn,filebck);
	}

	/*
	** Write out file
	*/
	DBexport(MDcurap->curfid, MDcurap->curfn);
	MDstatus(LURGENT,"Save Complete");
	
	MDstatoff();


	EXIT_MODULE(fn);
	return;
}
/*----------------------------------------------------------------------------*/
/* VEfnew  - New  file.  Filename in MDcurap->curfn.                          */
/*----------------------------------------------------------------------------*/
void
VEfnew(void)
{
	char *fn="VEfnew";

	INIT_MODULE(fn);

	/*
	** Test whether a modidified file is already loaded.
	*/
	if (MDcurap->curfid != 0 && DBismodfd(MDcurap->curfid) == YES) {
		VEfsave();
		MDcurap->prevfid = MDcurap->curfid;
	}

	/* 
	** Open data base entry
	*/
	MDstatus(LURGENT,"Creating...");
	MDcurap->curfid = DBopen(MDcurap->rel);

	MDstatus(LMESSAGE,"Complete");
	MDstatoff();

	EXIT_MODULE(fn);
	return;
}
/*----------------------------------------------------------------------------*/
/* VEhome  - Home key.                                                        */
/*----------------------------------------------------------------------------*/
int
VEhome(void)
{
	char *fn="VEhome";
	int (*formdsp)(char *);

	INIT_MODULE(fn);

	MDcurap->recptr = DBrdfirst(MDcurap->curfid,(DBRECPTR)MDcurap->buf);
	MDcurap->toprn = 1;
	MDcurap->crsrn = 1;

	switch(MDcurap->vutable) {
	case NO:	/* view in form format */
		formdsp = *MDcurap->formdsp;
		(*formdsp)("Home Form Display");
		break;

	case YES:	/* view in table format */
		VEtabdsp();
		break;
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VErefresh  - Redisplay current form or table.                              */
/*----------------------------------------------------------------------------*/
int
VErefresh(void)
{
	char *fn="VErefresh";
	int (*formdsp)(char *);

	INIT_MODULE(fn);


	switch(MDcurap->vutable) {
	case NO:	/* view in form format */
		formdsp = *MDcurap->formdsp;
		(*formdsp)("Refresh Form Display");
		break;

	case YES:	/* view in table format */
		VEtabdsp();
		break;
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VEend - End key.                                                           */
/*----------------------------------------------------------------------------*/
int
VEend(void)
{
	char *fn="VEend";
	int (*formdsp)(char *);

	INIT_MODULE(fn);
	MDcurap->recptr = DBrdlast(MDcurap->curfid,(DBRECPTR)MDcurap->buf);
	MDcurap->toprn = DBtotrec(MDcurap->curfid)-row_qty(&MDcurap->tabwn)+1;
	MDcurap->crsrn = DBtotrec(MDcurap->curfid);
	if (MDcurap->toprn < 1) MDcurap->toprn = 1;

	switch(MDcurap->vutable) {
	case NO:	/* view in form format */
		formdsp = *MDcurap->formdsp;
		(*formdsp)("End Form Display");
		break;

	case YES:	/* view in table format */

		VEtabdsp();
		break;
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VEpgdn - PgDn key.                                                         */
/*----------------------------------------------------------------------------*/
int
VEpgdn(void)
{
	char *fn="VEpgdn";
	int (*formdsp)(char *);
	DBRECPTR rec;

	INIT_MODULE(fn);

	MDcurap->toprn = MDcurap->toprn+row_qty(&MDcurap->tabwn);
	MDcurap->crsrn = DBrecnum(MDcurap->curfid)+row_qty(&MDcurap->tabwn);
	if (MDcurap->toprn > DBtotrec(MDcurap->curfid)) 
		MDcurap->toprn = DBtotrec(MDcurap->curfid)-row_qty(&MDcurap->tabwn)+1;
	if (MDcurap->crsrn > DBtotrec(MDcurap->curfid)) 
		MDcurap->crsrn = DBtotrec(MDcurap->curfid);

	switch(MDcurap->vutable) {
	case NO:	/* view in form format */
		rec = DBrdnext(MDcurap->curfid,(DBRECPTR)MDcurap->buf);
		if (rec == NULLP) {
			bell();
			EXIT_MODULE(fn);
			return(1);
		}
		MDcurap->recptr = rec;
		formdsp = *MDcurap->formdsp;
		(*formdsp)("PgDn Form Display");
		break;

	case YES:	/* view in table format */
		VEtabdsp();
		break;
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VEdn - Down arrow key                                                      */
/*----------------------------------------------------------------------------*/
int
VEdn(void)
{
	char *fn="VEdn";

	INIT_MODULE(fn);


	if (MDcurap->crsrn + 1 > DBtotrec(MDcurap->curfid) ) {
		bell();
		EXIT_MODULE(fn);
		return(1);
	}
	MDcurap->crsrn++;

	if (MDcurap->crsrn - MDcurap->toprn >= row_qty(&MDcurap->tabwn)) {
		MDcurap->toprn++;
	}
	switch(MDcurap->vutable) {
	case NO:	/* view in form format */
		kmdn();
		break;

	case YES:	/* view in table format */
		VEtabdsp();
		break;
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VEup - Up   arrow key                                                      */
/*----------------------------------------------------------------------------*/
int
VEup(void)
{
	char *fn="VEup";

	INIT_MODULE(fn);


	if (MDcurap->crsrn <= 1) {
		bell();
		EXIT_MODULE(fn);
		return(1);
	}
	(MDcurap->crsrn)--;

	if (MDcurap->crsrn < MDcurap->toprn) {
		MDcurap->toprn--;
	}

	switch(MDcurap->vutable) {
	case NO:	/* view in form format */
		kmup();
		break;

	case YES:	/* view in table format */
		VEtabdsp();
		break;
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VEpgup - PgUp key.                                                         */
/*----------------------------------------------------------------------------*/
int
VEpgup(void)
{
	char *fn="VEpgup";
	DBRECPTR rec;
	int (*formdsp)(char *);

	INIT_MODULE(fn);

	MDcurap->toprn = MDcurap->toprn-row_qty(&MDcurap->tabwn);
	MDcurap->crsrn = DBrecnum(MDcurap->curfid)-row_qty(&MDcurap->tabwn);
	if (MDcurap->toprn < 1) 
		MDcurap->toprn = 1;
	if (MDcurap->crsrn < 1) 
		MDcurap->crsrn = 1;


	switch(MDcurap->vutable) {
	case NO:	/* view in form format */
		rec = DBrdprev(MDcurap->curfid,(DBRECPTR)MDcurap->buf);
		if (rec == NULLP) {
			bell();
			EXIT_MODULE(fn);
			return(1);
		}
		MDcurap->recptr = rec;
		formdsp = *MDcurap->formdsp;
		(*formdsp)("PgUp Form Display");
		break;

	case YES:	/* view in table format */
		VEtabdsp();
		break;
	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VEfdbudget - Define and display budget record form                         */
/*----------------------------------------------------------------------------*/
int
VEfdbudget(void)
{
	char *fn="VEfdbudget";
	DFORMPTR fmp;
	DFIELDPTR fldp;
	struct DBchart chartrec;
	char numstr[10];
	struct DBbudget *bp;


	INIT_MODULE(fn);

	/*
	** Lookup any derived fields
	*/
	bp = (struct DBbudget *)MDcurap->buf;
	strcpy(DBselstr,bp->acctdr);
	if (DBrdfirst(chartid,(DBRECPTR)&chartrec) == NULLP) {
		strcpy(drdesc,"** UNKNOWN ACCOUNT **");
	} else {
		strcpy(drdesc,chartrec.desc);
	}
	strcpy(DBselstr,bp->acctcr);
	if (DBrdfirst(chartid,(DBRECPTR)&chartrec) == NULLP) {
		strcpy(crdesc,"** UNKNOWN ACCOUNT **");
	} else {
		strcpy(crdesc,chartrec.desc);
	}
	*DBselstr='\0';

	/* record number:  XXX/XXX    */
	itoaz(DBrecnum(MDcurap->curfid),numstr);
	strcpy(brecnumfld,numstr);
	strcat(brecnumfld,"/");
	itoaz(DBtotrec(MDcurap->curfid),numstr);
	strcat(brecnumfld,numstr);
	while (strlen(brecnumfld) < 7) strcat(brecnumfld," ");


	/*
	** If form is defined, display it
	*/
	if (MDcurap->fmp != NULLP) {
		fm_up(MDcurap->fmp);
		fm_upd(MDcurap->fmp);
		EXIT_MODULE(fn);
		return(1);
	}

	/*
	** Define budget form:
	** 01234567890123456789012345678901234567890123456789
	 0
	 1        ----ACCOUNT----
	 2        No. Description
	 3 Debit- XXX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	 4 Credit-XXX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	 5
	 6 Memo-  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	 7
	 8 JAN XXXXXX.XX    FEB XXXXXX.XX    MAR XXXXXX.XX
	 9 APR XXXXXX.XX    MAY XXXXXX.XX    JUN XXXXXX.XX
	10 JUL XXXXXX.XX    AUG XXXXXX.XX    SEP XXXXXX.XX
	11 OCT XXXXXX.XX    NOV XXXXXX.XX    DEC XXXXXX.XX
	12                                        XXX/XXX
	**
	*/
	fmp = fm_def(3,CENTER_WN,15,52,LHIGHLITE,BDR_LNP);
	sfm_opt(FORMCLEAR,OFF,fmp);
	sw_name("BUDGET",fmp->wnp);
	sw_margin(1,1,fmp->wnp);
	MDcurap->fmp = fmp;

	ftxt_def(1,7,"----ACCOUNT----",LHIGHLITE,fmp);
	ftxt_def(2,7,"No. Description",LHIGHLITE,fmp);
	fldp = fld_def(3,0,"Debit- ",FADJACENT,"XXX",F_STRING,
		(char *)bp->acctdr,fmp);
	ftxt_def(3,11,drdesc,LNORMAL,fmp);
	fldp = fld_def(4,0,"Credit-",FADJACENT,"XXX",F_STRING,
		(char *)bp->acctcr,fmp);
	ftxt_def(4,11,crdesc,LNORMAL,fmp);
	fldp = fld_def(6,0,"Memo-  ",FADJACENT,def_pic('X',30),F_STRING,
		(char *)bp->desc,fmp);
	fldp = fld_def(8,0,"JAN ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[0],fmp);
	fldp = fld_def(8,17,"FEB ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[1],fmp);
	fldp = fld_def(8,34,"MAR ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[2],fmp);

	fldp = fld_def(9,0,"APR ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[3],fmp);
	fldp = fld_def(9,17,"MAY ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[4],fmp);
	fldp = fld_def(9,34,"JUN ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[5],fmp);

	fldp = fld_def(10,0,"JUL ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[6],fmp);
	fldp = fld_def(10,17,"AUG ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[7],fmp);
	fldp = fld_def(10,34,"SEP ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[8],fmp);

	fldp = fld_def(11,0,"OCT ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[9],fmp);
	fldp = fld_def(11,17,"NOV ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[10],fmp);
	fldp = fld_def(11,34,"DEC ",FADJACENT,"99999.99",F_DECIMAL,
		(char *)&bp->amt[11],fmp);
	ftxt_def(12,40,brecnumfld,LNORMAL,fmp);


	fm_up(MDcurap->fmp);
	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VEfdchart - Define and display chart record form                           */
/*----------------------------------------------------------------------------*/
int
VEfdchart(void)
{
	char *fn="VEfdchart";
	DFORMPTR fmp;
	DFIELDPTR fldp;
	struct DBchart *cp;
	char numstr[10];

	INIT_MODULE(fn);

	/*
	** Update any derived fields
	*/

	/* record number:  XXX/XXX    */
	itoaz(DBrecnum(MDcurap->curfid),numstr);
	strcpy(crecnumfld,numstr);
	strcat(crecnumfld,"/");
	itoaz(DBtotrec(MDcurap->curfid),numstr);
	strcat(crecnumfld,numstr);
	while (strlen(crecnumfld) < 7) strcat(crecnumfld," ");
	

	/*
	** If form is defined, display it
	*/
	cp = (struct DBchart *)MDcurap->buf;
	if (MDcurap->fmp != NULLP) {
		fm_up(MDcurap->fmp);
		fm_upd(MDcurap->fmp);
		EXIT_MODULE(fn);
		return(1);
	}

	/*
	** Define chart form:
	** 01234567890123456789012345678901234567890123456789
	 0
	 1 Account No. XXX
	 2 Description XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	 3 Prev. Year  XXX
	 4                                         XXX/XXX
	*/
	fmp = fm_def(7,CENTER_WN,7,48,LHIGHLITE,BDR_LNP);
	sfm_opt(FORMCLEAR,OFF,fmp);
	sw_name("CHART",fmp->wnp);
	sw_margin(1,1,fmp->wnp);
	MDcurap->fmp = fmp;

	fldp = fld_def(1,0,"Account No. ",FADJACENT,"XXX",F_STRING,
		(char *)cp->acct,fmp);
	fldp = fld_def(2,0,"Description ",FADJACENT,def_pic('X',30),F_STRING,
		(char *)cp->desc,fmp);
	fldp = fld_def(3,0,"Prev. Year  ",FADJACENT,"XXX",F_STRING,
		(char *)cp->oacct,fmp);
	ftxt_def(4,36,crecnumfld,LNORMAL,fmp);


	fm_up(MDcurap->fmp);
	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* VEtabdsp - Display data base records in table view                         */
/*----------------------------------------------------------------------------*/
void
VEtabdsp(void)
{
	char *fn="VEtabdsp";
	int (*tabdsp)(char *);
	int i;
	DBRECPTR recptr;

	INIT_MODULE(fn);
	sw_name(MDcurap->curfn,&MDcurap->tabwn);
	if (!isset_wn(&MDcurap->tabwn)) {
		set_wn(&MDcurap->tabwn);
	}
	/*cl_wn(&MDcurap->tabwn);*/
	mv_cs(0,0,&MDcurap->tabwn);

	/*
	** set top of table file pointer
	*/
        MDcurap->recptr = DBrdseek(MDcurap->curfid,MDcurap->toprn,(DBRECPTR)MDcurap->buf);
	

	/* 
	** Print table: row_qty - 2 rows
	*/ 
	for (i=0; i<row_qty(&MDcurap->tabwn)&&recptr!=NULLP; i++) {
		tabdsp = *MDcurap->tabdsp;
		(*tabdsp)("Table Display");
	         recptr = DBrdnext(MDcurap->curfid,(DBRECPTR)MDcurap->buf);
	}

	/* somehow, clear to the end of the screen for small files */
	v_rw(' ', (row_qty(&MDcurap->tabwn)-i)*col_qty(&MDcurap->tabwn),&MDcurap->tabwn);

	/* restore record pointer */
	MDcurap->recptr = DBrdseek(MDcurap->curfid,MDcurap->crsrn,(DBRECPTR)MDcurap->buf);

	EXIT_MODULE(fn);
	return;
}
/*----------------------------------------------------------------------------*/
/* VEtdchart - Define and display table of chart records                      */
/*----------------------------------------------------------------------------*/
int
VEtdchart(void)
{
	char *fn="VEtdchart";
	struct DBchart *cp;

	INIT_MODULE(fn);

	/*
	** XXX XXXXXXXXXXXXXXXXXXXXXXXXXXXXX XXX
	*/
	cp = (struct DBchart *)MDcurap->buf;

	if (MDcurap->crsrn == DBrecnum(MDcurap->curfid)) {
		sw_att(LTABLITE, &MDcurap->tabwn);
	}
	v_printf(&MDcurap->tabwn,"%-3.3s %-30.30s %-3.3s \n",
		cp->acct,cp->desc,cp->oacct);
	if (MDcurap->crsrn == DBrecnum(MDcurap->curfid)) {
		sw_att(LTABLE, &MDcurap->tabwn);
	}
		

	EXIT_MODULE(fn);
	return(1);
}
