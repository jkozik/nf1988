/*		PFmenu.c - Menu Drive Code */

#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "malloc.h"
#include "stdio.h"
#include "io.h"
#include "stdarg.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "dos.h"
#include "wfd.h"
#include "PFdefs.h"
#include "PFstruct.h"
#include "PFextern.h"

/*----------------------------------------------------------------------------*/
/* Private Menu defines                                                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Private Menu Driver Structures                                             */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Private Menu Driver function templates                                     */
/*----------------------------------------------------------------------------*/
int MDquit(char *);
int MDout_to(char *);

int RDproc(char *);

int MDchaf(char *);

int MDapmenu(char *);
int MDapload(char *);
int MDapsave(char *);
int MDapsvas(char *);
int MDapnew(char *);
int MDapview(char *);

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
WINDOW MDstatwn;
int MDchnum;
MDAPPTR MDcurap;
MDAP MDjetran = {RLJETRAN,"??","","",0,0,0,NULLP,MDnotyet,MDnotyet,NO,NULLP};
MDAP MDbudget = {RLBUDGET,"budget","","",0,0,0,NULLP,VEfdbudget,MDnotyet,NO,NULLP};
MDAP MDchart = {RLCHART,"chart","","",0,0,0,NULLP,VEfdchart,VEtdchart,NO,NULLP};
/*
MDAP MDjetran = {RLJETRAN,"??","","",0,0,0,NULLP,VEfdjetran,VEtdjetran,NO,NULLP};
MDAP MDbudget = {RLBUDGET,"budget","","",0,0,0,NULLP,VEfdbudget,VEtdbudget,NO,NULLP};
MDAP MDchart = {RLCHART,"chart","","",0,0,0,NULLP,VEfdchart,VEtdchart,NO,NULLP};
*/
MDSETTINGS MDset = {
	{
	{"jetran",66,YES,80,0},
	{"budget",66,YES,132,0},
	{"chart",88,YES,132,0},
	{"glrpt",66,YES,80,0},
	{"monsum",66,YES,132,0},
	{"audit",66,YES,80,0},
	{"balsht",66,YES,80,0},
	},
	"89",
	"\\nf",
	FFILE
};

/* private global variables */
DFORMPTR MNroot,MNap,MNrpt,MNsettings,MNutil,MNqry,MNout_to;
DFORMPTR MNapfile,MNapedit,MNapview,MNapsearch;

DKEYDEF apkeytbl[] =			/*Application Key Definition Table    */
{					/*The order here is unimportant.      */
#ifdef F_MENU
    {-K_F1, kdhelp},			/*invoke help key		      */
    {-K_LEFT, kmleft},			/*left arrow key		      */
    {-K_RIGHT, kmright},		/*right arrow key		      */
    {-K_UP, VEup},			/*up arrow key			      */
    {-K_DN, VEdn},			/*down arrow key		      */
    {K_ENTER, kmsel},			/*enter key			      */
    {K_ESC, kmesc},			/*escape key			      */
    {-K_HOME, VEhome}, 			/*home key			      */
    {-K_END, VEend},			/*end key			      */
    {-K_PGUP, VEpgup}, 			/*pgup key			      */
    {-K_PGDN, VEpgdn},			/*pgdn key			      */
    {-K_CHOME, kmfirst}, 		/*ctl-home key			      */
    {-K_CEND, kmlast},			/*ctl-end key			      */
    {PFITBL_DEFAULT, kmchar},		/*possible first character for item   */
    {0, NULLFP},			/*blank space in table		      */
    {0, NULLFP},
    {0, NULLFP},
    {0, NULLFP},
    {0, NULLFP},
#endif
    {PFITBL_END, NULLFP}		/*end of table marker		      */
};




/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                   MENU DRIVER FUNCTIONS                                    */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* MDmnproc() - Main Menu Driver function.  This function is called from      */
/*              the main program.                                             */
/*                                                                            */
/* Returns:                                                                   */
/*  1      Success.                                                           */
/*                                                                            */
/*  0      Error.  _wn_err is set to the following:                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void
MDmnproc(void)
{
	char *fn="MDmnproc";
	DFIELDPTR fld;

	INIT_MODULE(fn);

	/*
	** define root menu:
	**  "Transaction Budget Chart Query Report Settings Utilities"
	*/
	MNroot = mnfm_def(0,0,1,80,LNORMAL,BDR_0P);
	MNrpt = mnfm_dap(MNPULL, LNORMAL, BDR_LNP);
	MNout_to = mnfm_dap(MNPULL, LNORMAL, BDR_LNP);
	MNsettings = mnfm_dap(MNPULL, LNORMAL, BDR_LNP);
	MNutil = mnfm_dap(MNPULL, LNORMAL, BDR_LNP);

	MNap = mnfm_def(0,0,1,80,LNORMAL,BDR_0P);
	MNapfile = mnfm_dap(MNPULL, LNORMAL, BDR_LNP);
	MNapedit = mnfm_dap(MNPULL, LNORMAL, BDR_LNP);
	MNapview = mnfm_dap(MNPULL, LNORMAL, BDR_LNP);
	MNapsearch = mnfm_dap(MNPULL, LNORMAL, BDR_LNP);

	fld = mnf_def(0,0,"Transaction","View/Edit Journal Entry Transactions",
		NULLP,MDapmenu,MNroot);
	sf_userp( (char *)&MDjetran, fld);

	fld = mnf_def(0,12,"Budget","View/Edit Budget Detail",
		NULLP,MDapmenu,MNroot);
	sf_userp( (char *)&MDbudget, fld);

	fld = mnf_def(0,19,"Chart","View/Edit Chart of Accout Detail",
		NULLP,MDapmenu,MNroot);
	sf_userp( (char *)&MDchart, fld);

	fld = mnf_def(0,25,"Query","Set Query Filter for Reports",
		NULLP,MDnotyet,MNroot);
	sf_userp("Query",fld);

	fld = mnf_def(0,31,"Report","Select and Run Financial Reports",
		MNrpt,NULLFP,MNroot);

	fld = mnf_def(0,38,"Settings","Program and Report Settings",
		MNsettings,NULLFP,MNroot);

	fld = mnf_def(0,47,"Utilities","Periodic Closing Routines",
		MNutil,NULLFP,MNroot);

	fld = mnf_def(0,57,"Quit","Exit Program",
		NULLP,MDquit,MNroot);


	/*
	** define report submenu:
	**  Output to ...
	**  GLRPT
	**  MONSUM
	**  Audit Accounts
	**  Balance Sheet
	**  Budget vs Actual
	**  Transaction Detail
	**  Budget Detail
	**  Chart of Accounts
	*/
	fld = mnf_def(0,0,"Output to ...","Output to FILE, CITOH, or Laser",
		MNout_to,NULLFP,MNrpt);

	fld = mnf_def(1,0,"Glrpt","General Ledger Report",
		NULLP,MDnotyet,MNrpt);
	sf_userp("glrpt",fld);

	fld = mnf_def(2,0,"Monsum","Monthly Summary Report",
		NULLP,MDnotyet,MNrpt);
	sf_userp("monsum",fld);

	fld = mnf_def(3,0,"Audit","Report to Audit Key Accounts",
		NULLP,MDnotyet,MNrpt);
	sf_userp("audit",fld);

	fld = mnf_def(4,0,"Balance Sheet","Balance Sheet Report",
		NULLP,MDnotyet,MNrpt);
	sf_userp("balsht",fld);

	fld = mnf_def(5,0,"Budget vs Actual",
		"Report Compares Actual vs Budgeted Transactions",
		NULLP,MDnotyet,MNrpt);
	sf_userp("budact",fld);
	
	fld = mnf_def(6,0,"Transactions","Journal Entry Transaction Detail",
		NULLP,MDnotyet,MNrpt);
	sf_userp("jetran",fld);

	fld = mnf_def(7,0,"Budget Detail","Budget Detail Report",
		NULLP,MDnotyet,MNrpt);
	sf_userp("budget",fld);

	fld = mnf_def(8,0,"Chart","Chart of Accounts Report",
		NULLP,MDnotyet,MNrpt);
	sf_userp("chart",fld);

	/*
	** Output to ... submenu:
	**  FILE
	**  FILE/Browse
	**  C.ITOH
	**  LaserJet
	*/
	fld = mnf_def(0,0,"File","Output to a file",
		NULLP,MDout_to,MNout_to);
	sf_userp("File",fld);
	
	fld = mnf_def(1,0,"File/Browse","Output to a file, Browse output",
		NULLP,MDout_to,MNout_to);
	sf_userp("Browse",fld);

	fld = mnf_def(2,0,"C.ITOH","Output to C.ITOH Dot Matrix Printer",
		NULLP,MDout_to,MNout_to);
	sf_userp("CITOH",fld);

	fld = mnf_def(3,0,"Laser","Output to LaserJet Printer",
		NULLP,MDout_to,MNout_to);
	sf_userp("Laser",fld);


	/*
	** Settings submenu:
	**  Report settings
	**  Current Year
	**  Root Directory
	*/
	fld = mnf_def(0,0,"Report","Settings for Reports",
		NULLP,MDnotyet,MNsettings);
	sf_userp("Settings:  Report",fld);

	fld = mnf_def(1,0,"Year","Current Working Year",
		NULLP,MDnotyet,MNsettings);
	sf_userp("Settings: Year",fld);

	fld = mnf_def(2,0,"Directory","Root Directory of Finacial Data Base",
		NULLP,MDnotyet,MNsettings);
	sf_userp("Settings:  Directory",fld);

	/*
	** Utilities submenu:
	**  Create Next Year
	**  Close year
	*/
	fld = mnf_def(0,0,"Create Next Year","Setup directory for new year",
		NULLP,MDnotyet,MNutil);
	sf_userp("Create Next Year",fld);

	fld = mnf_def(1,0,"Close year","Create balance forward file for next year",
		NULLP,MDnotyet,MNutil);
	sf_userp("Close year",fld);

	/*
	** Application submenu:
	**  "File Edit View Search"
	*/
	fld = mnf_def(0,0,"File","Load or Save File",
		MNapfile,NULLFP,MNap);

	fld = mnf_def(0,5,"Edit","Insert, Change, or Update File Contents",
		MNapedit,NULLFP,MNap);

	fld = mnf_def(0,10,"View","Select View Option: Tabular or Form",
		MNapview,NULLFP,MNap);

	fld = mnf_def(0,15,"Search","Search by Account, Date, Amount, or Character String", 
		MNapsearch,NULLFP,MNap);

	/*
	** File submenu:
	**  Load
	**  New
	**  Save
	**  Save As
	*/
	fld = mnf_def(0,0,"Load","Read-in file",
		NULLP,MDapload,MNapfile);
	sf_userp("Load",fld);

	fld = mnf_def(1,0,"New","Create New File",
		NULLP,MDapnew,MNapfile);
	sf_userp("New",fld);

	fld = mnf_def(2,0,"Save","Save Current File",
		NULLP,MDapsave,MNapfile);
	sf_userp("Save",fld);

	fld = mnf_def(3,0,"Save As","Save Current File Under Different Name",
		NULLP,MDapsvas,MNapfile);
	sf_userp("SaveAs",fld);

	
	/*
	** Edit submenu:
	**  Insert
	**  Append
	**  Change
	**  Yank
	**  Put
	**  Undo
	*/
	fld = mnf_def(0,0,"Insert","Insert Record Before Current File Location",
		NULLP,MDnotyet,MNapedit);
	sf_userp("Edit",fld);

	fld = mnf_def(1,0,"Append","Insert Record After Current File Location",
		NULLP,MDnotyet,MNapedit);
	sf_userp("Edit",fld);

	fld = mnf_def(2,0,"Change","Change Record At Current File Location",
		NULLP,MDnotyet,MNapedit);
	sf_userp("Edit",fld);

	fld = mnf_def(3,0,"Yank","Copy Records Into 'Yank' Buffer",
		NULLP,MDnotyet,MNapedit);
	sf_userp("Edit",fld);

	fld = mnf_def(4,0,"Put","Insert Records From 'Yank' Buffer Before Current File Location",
		NULLP,MDnotyet,MNapedit);
	sf_userp("Edit",fld);

	fld = mnf_def(5,0,"Undo","Undo Previous Command",
		NULLP,MDnotyet,MNapedit);
	sf_userp("Edit",fld);

	/*
	** View submenu:
	**  Table
	**  Form
	*/
	fld = mnf_def(0,0,"Table","View Multiple Records Per Screen",
		NULLP,MDapview,MNapview);
	sf_userp("Table",fld);

	fld = mnf_def(1,0,"Form","View One Record Per Screen",
		NULLP,MDapview,MNapview);
	sf_userp("Form",fld);
	

	/*
	** Search submenu:
	**  Account
	**  Date
	**  Amount
	**  String
	*/
	fld = mnf_def(0,0,"Account","Search By Account",
		NULLP,MDnotyet,MNapsearch);
	sf_userp("Account Search",fld);

	fld = mnf_def(1,0,"Date","Search By Date",
		NULLP,MDnotyet,MNapsearch);
	sf_userp("Date Search",fld);

	fld = mnf_def(2,0,"Amount","Search By Amount",
		NULLP,MDnotyet,MNapsearch);
	sf_userp("Amount Search",fld);

	fld = mnf_def(3,0,"String","Search By Character String",
		NULLP,MDnotyet,MNapsearch);
	sf_userp("Character String Search",fld);

	/*
	** Set the menu message line
	*/
	se_mnmsg(MANUAL);
	pl_mnmsg(v_rwq-1, 0);

	mn_proc(0, MNroot);


	EXIT_MODULE(fn);
	return;
}
/*----------------------------------------------------------------------------*/
/* MDapmenu - Menu Driver for applications submenu                            */
/*----------------------------------------------------------------------------*/
int
MDapmenu(p)
char *p;
{
	char *fn="MDapmenu";
	extern DKEYDEF _mkeytbl[];

	INIT_MODULE(fn);
	/*
	** Set global pointer to active application
	*/
	MDcurap = (MDAPPTR)p;

	/*
	** set key table-
	**   K_PGUP  VEpgup()
	**   K_PGDN  VEpgdn()
	**   K_HOME  VEhome()
	**   K_END   VEend()
	*/
	se_keymtable(apkeytbl);

	/*
	** Define window for displaying file in table view
	** it might not get called.
	*/
	defs_wn(&MDcurap->tabwn,1,0,v_rwq-2,v_coq,BDR_LNP);
	sw_popup(YES, &MDcurap->tabwn);
	sw_scroll(OFF,&MDcurap->tabwn);
	sw_att(LTABLE,&MDcurap->tabwn);
	sw_bdratt(LTABLE,&MDcurap->tabwn);

	/*
	** if a file is already loaded, refresh the display
	*/
	if (MDcurap->curfid!=0 && DBtotrec(MDcurap->curfid)>0) {
		switch(MDcurap->vutable) {
		case NO: /* form */
	  	  if (MDcurap->fmp != NULLP) {
		  	  fm_up(MDcurap->fmp);
	  	  }
		  VErefresh();
		  break;

		case YES: /* table */
		  VErefresh();
		  break;
		}
	}


	mn_proc(0, MNap);

	/*
	** clear application area
	*/
	if (MDcurap->fmp != NULLP && isset_wn(MDcurap->fmp->wnp)) {
		fm_dn(MDcurap->fmp);
	}
	if (isset_wn(&MDcurap->tabwn)) {
		unset_wn(&MDcurap->tabwn);
	}

	se_keymtable(_mkeytbl);
	EXIT_MODULE(fn);
	return(0);
}
/*----------------------------------------------------------------------------*/
/* MDnotyet - Display "The xxxx command is not yet implemented"               */
/*----------------------------------------------------------------------------*/
int
MDnotyet(p)
char *p;
{
	char *fn="MDnotyet";
	char message[80];

	INIT_MODULE(fn);

	sprintf(message,"The %s command is not yet implemented.",p);
	MDdialog1(message);
	
	EXIT_MODULE(fn);
	return(0);
}

/*----------------------------------------------------------------------------*/
/* MDstatoff- Display status message and keep window up.                      */
/*----------------------------------------------------------------------------*/
void
MDstatoff(void)
{
	char *fn="MDstatoff";
	INIT_MODULE(fn);
	unset_wn(&MDstatwn);
	EXIT_MODULE(fn);
	return;
}
/*----------------------------------------------------------------------------*/
/* MDstatus - Display status message and keep window up.                      */
/*----------------------------------------------------------------------------*/
void
MDstatus(att,message)
int att;
char *message;
{
	char *fn="MDstatus";
	INIT_MODULE(fn);

	if (isset_wn(&MDstatwn)) {
		unset_wn(&MDstatwn);
	}
	defs_wn(&MDstatwn, 15, CENTER_WN, 3, strlen(message) + 4, BDR_DLNP);
	sw_popup(YES, &MDstatwn);
	sw_att(att,&MDstatwn);
	sw_bdratt(LERROR,&MDstatwn);
	set_wn(&MDstatwn);
	v_plst(0,CENTER_TEXT,message,&MDstatwn);

	EXIT_MODULE(fn);
	return;
}
/*----------------------------------------------------------------------------*/
/* MDdialog1 - Display message and press any key to continue.                 */
/*----------------------------------------------------------------------------*/
void
MDdialog1(message)
char *message;
{
	char *fn="MDdialog1";
	char *contnue="Press Any Key to Continue";
	int mlen,clen,maxlen;
	WINDOW wn;
	
	INIT_MODULE(fn);
	mlen = strlen(message);
	clen = strlen(contnue);
	maxlen = max(mlen,clen);

	defs_wn(&wn, 10, CENTER_WN, 5, maxlen+4, BDR_LNP);
	sw_popup(YES,&wn);
	sw_att(LDIALOG, &wn);
	sw_bdratt(LDIALOG, &wn);
	set_wn(&wn);

	v_plst(0,CENTER_TEXT, message, &wn);
	v_plst(2,CENTER_TEXT, contnue, &wn);
	
	ki();
	unset_wn(&wn);

	EXIT_MODULE(fn);
	return;
}
/*----------------------------------------------------------------------------*/
/* MDdialog2 - Display message and "OK" or "CANCEL"                           */
/*----------------------------------------------------------------------------*/
int
MDdialog2(message)
char *message;
{
	char *fn="MDdialog2";
	char *okcancel="OK     CANCEL";
	int mlen,clen,maxlen;
	MFILEPTR mfp;
	WINDOW wn,mwn;
	int ret;
	
	INIT_MODULE(fn);
	mlen = strlen(message);
	clen = strlen(okcancel);
	maxlen = max(mlen,clen);

	/* define simple menu="OK    CANCEL" */
	mfp = mf_def(NULLP, 1, 14);
	mf_rwrpl(okcancel, 0, mfp);

	/* define window, display message */
	defs_wn(&wn, 10, CENTER_WN, 5, maxlen+4, BDR_LNP);
	sw_popup(YES,&wn);
	sw_att(LDIALOG, &wn);
	sw_bdratt(LDIALOG, &wn);
	set_wn(&wn);
	v_plst(0,CENTER_TEXT, message, &wn);

	/* display menu, OK? or CANCEL? */
	defs_wn(&mwn, 14, CENTER_WN, 1, clen, BDR_0P);
	sw_popup(YES,&mwn);
	sw_att(LDIALOG, &mwn);
	sw_bdratt(LDIALOG, &mwn);
	sw_mf(mfp, &mwn);
	ret = menu2(&mwn, 2, 7, 2, 1);
	unset_wn(&wn);
	mf_free(mfp);

	EXIT_MODULE(fn);
	switch(ret) {
	case 0: /* ESC */
	case 2: /* CANCEL */
		return(0);
		
	case 1: /* OK */
		return(1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
/* MDprompt1 - Prompt for field (file name)                                   */
/*----------------------------------------------------------------------------*/
int
MDprompt1(row,col,prompt,pic,fld_type,data)
int row,col,fld_type;
char *prompt,*pic,*data;
{
	char *fn="MDprompt1";
	WINDOW wn;
	int ret;

	DFIELDPTR fld;
	DFORMPTR fmp;
	int fwidth;
	
	INIT_MODULE(fn);
	fwidth = max(strlen(prompt), strlen(pic))+4;
	fmp = fm_def(row,col,3,fwidth,fld_type,BDR_LNP);
	sw_name(prompt,fmp->wnp);
	sw_att(LBLUE, &wn);
	sw_bdratt(LBLUE, &wn);
	sfm_opt(VERIFYEXIT, OFF, fmp);
	
	fld = fld_def(0,1,"",FADJACENT,pic,F_STRING,data,fmp);

	ret = fm_proc(0, fmp);
	EXIT_MODULE(fn);
	return(ret);


}
/*----------------------------------------------------------------------------*/
/* MDapload - Load file starting with default file name                       */
/*----------------------------------------------------------------------------*/
int
MDapload(p)
char *p;
{
	char *fn="MDapload";
	int ret,fcnt;
	
	MFILEPTR mfp;
	char filename[14],*fp;
	struct stat st;
	unsigned short anded;
	WINDOW wn;
	struct find_t fbuf;

	INIT_MODULE(fn);
	p=p;

	/*
	** Prompt with default file name 
	*/
	strcpy(filename, MDcurap->dfltfn);
	ret = MDprompt1(10,CENTER_WN,"Enter File Name",
		"XXXXXXXXXXXX",F_STRING,filename);

	/* if ESC typed, return */
	if (ret == ABORT_FORM) {
		EXIT_MODULE(fn);
		return(0);
	}
	/*
	** Does file exist?  If so, load it!
	*/
	if (stat(filename,&st) == 0) {
		anded = st.st_mode & (unsigned short)S_IFREG;
		if (anded != 0) {
			strcpy(MDcurap->curfn,filename);
			VEfload();
			EXIT_MODULE(fn);
			return(1);
		} else {
			MDdialog1("Cannot Load Directory");
			EXIT_MODULE(fn);
			return(0);
		}
	}

	/*
	** File not found, maybe 
	**  1. wildcard characters
	**  2. file not found
	*/
	if (strpbrk(filename,"*?") == NULLP) {
		MDdialog1("File Not Found");
		EXIT_MODULE(fn);
		return(0);
	}
		

	/*
	** 1. Define an MFILE
	** 2. Copy all matching filename into MFILE
	** 3. Define menu window
	** 4. Prompt user
	*/
	mfp = mf_def(NULLP, 15, 13);

	ret = _dos_findfirst(filename, _A_NORMAL, &fbuf);
	for(fcnt=0; ret == 0 && fcnt < 15; fcnt++) {
		mf_rwrpl(fbuf.name,fcnt,mfp);
		ret = _dos_findnext(&fbuf);
	}
	if (fcnt == 0) {
		MDdialog1("No Files Match");
		EXIT_MODULE(fn);
		return(0);
	}

	defs_wn(&wn, CENTER_WN,CENTER_WN,2+fcnt,13+2+2, BDR_LNP);
	sw_popup(YES,&wn);
	sw_bdratt(LDIALOG, &wn);
	sw_att(LDIALOG, &wn);
	sw_mf(mfp, &wn);

	ret = menu2(&wn, fcnt, 13, 1, 1);

	/* Was escape pressed? */
	if (ret == 0) {
		mf_free(mfp);
		EXIT_MODULE(fn);
		return(0);
	}

	/*
	** The selected filename is mf_rwp(ret-1, mfp).
	** Verify that the file is readable and load it.
	*/
	strcpy(filename,mf_rwp(ret-1,mfp));
	fp = strchr(filename,'\n');
	if (fp != NULLP) *fp = '\0';
	mf_free(mfp);
	if (stat(filename,&st) == 0) {
		anded = st.st_mode & (unsigned short)S_IFREG;
		if (anded != 0) {
			strcpy(MDcurap->curfn,filename);
			VEfload();
			EXIT_MODULE(fn);
			return(1);
		}
	}

	MDdialog1("File Not Found");
	EXIT_MODULE(fn);
	return(0);
}
/*----------------------------------------------------------------------------*/
/* MDapsave - Save currently opened file under same name                      */
/*----------------------------------------------------------------------------*/
int
MDapsave(p)
char *p;
{
	char *fn="MDapsave";

	INIT_MODULE(fn);
	p=p;

	/*
	** Has any file been loaded?
	*/
	if (MDcurap->curfid == 0) {
		MDdialog1("Nothing to Save");
		EXIT_MODULE(fn);
		return(1);
	}

	VEfsave();
	EXIT_MODULE(fn);
	return(1);
}

/*----------------------------------------------------------------------------*/
/* MDapsvas - Save currently opened file under new name                       */
/*----------------------------------------------------------------------------*/
int
MDapsvas(p)
char *p;
{
	char *fn="MDapsvas";
	FILEPATH filename;
	struct stat st;
	unsigned short anded;
	int ret,okay;

	INIT_MODULE(fn);
	p=p;

	/*
	** Has any file been loaded?
	*/
	if (MDcurap->curfid == 0) {
		MDdialog1("Nothing to Save");
		EXIT_MODULE(fn);
		return(1);
	}

	/*
	** Prompt for file name.  Fill field with current filename.
	*/
	strcpy(filename,MDcurap->curfn);
	ret = MDprompt1(10,CENTER_WN,"Enter File Name",
		"XXXXXXXXXXXX",F_STRING,filename);

	/* if ESC typed, return */
	if (ret == ABORT_FORM) {
		EXIT_MODULE(fn);
		return(0);
	}

	/*
	** if filename exists, and is not a directory then prompt user.
	*/
	if (stat(filename,&st) == 0) {
		anded = st.st_mode & (unsigned short)S_IFREG;
		if (anded == 0) {
			/* file is a directory */
			MDdialog1("Cannot Write to a Directory");
			EXIT_MODULE(fn);
			return(1);
		} else {
			/* file exists, ask user */
			okay = MDdialog2("File Exists, Replace?");
			if (okay == 1) {
				strcpy(MDcurap->curfn,filename);
			} else {
				EXIT_MODULE(fn);
				return(0);
			}
		}
	} else {
		strcpy(MDcurap->curfn,filename);
	}

	/* file can be written */
	VEfsave();
	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* MDapnew  - Prompt for file name to newly create.                           */
/*----------------------------------------------------------------------------*/
int
MDapnew(p)
char *p;
{
	char *fn="MDapnew";
	int ret;
	char filename[14];
	struct stat st;
	unsigned short anded;
	int okay;

	INIT_MODULE(fn);
	p=p;

	/*
	** Prompt for file name. 
	*/
	strcpy(filename,"");
	ret = MDprompt1(10,CENTER_WN,"Enter File Name","XXXXXXXXXXXX",F_STRING,filename);

	/* if ESC typed, return */
	if (ret == ABORT_FORM) {
		EXIT_MODULE(fn);
		return(0);
	}

	/*
	** if filename exists, and is not a directory then, then ask user
	** to overwrite;
	** otherwise, create new file.
	*/
	if (stat(filename,&st) == 0) {
		anded = st.st_mode & (unsigned short)S_IFREG;
		if (anded != 0) {
			okay = MDdialog2("File Already Exists, Overwrite?");
			if (okay == 1) {
				strcpy(MDcurap->curfn,filename);
				VEfnew();
				EXIT_MODULE(fn);
				return(1);
			} else {
				EXIT_MODULE(fn);
				return(0);
			}
		} else {
			MDdialog1("Cannot Use Existing Directory");
			EXIT_MODULE(fn);
			return(0);
		}
	} else {
		
		strcpy(MDcurap->curfn,filename);
		VEfnew();
		EXIT_MODULE(fn);
		return(1);
	}
	return(1);
}
/*----------------------------------------------------------------------------*/
/* MDout_to - Prompt for output device selection.                             */
/*----------------------------------------------------------------------------*/
int
MDout_to(p)
char *p;
{
	char *fn="MDout_to";

	INIT_MODULE(fn);
	
	switch (*p) {
	case 'F': /* FILE */
		MDset.out_to = FFILE;
		break;

	case 'B': /* FILEBROWSE */
		MDset.out_to = FILEBROWSE;
		break;

	case 'C': /* CITOH */
		MDset.out_to = CITOH;
		break;

	case 'L': /* LASER */
		MDset.out_to = LASERJET;
		break;

	}

	EXIT_MODULE(fn);
	return(1);
}
/*----------------------------------------------------------------------------*/
/* MDquit - Prompt user if okay to exit program.                              */
/*----------------------------------------------------------------------------*/
int
MDquit(p)
char *p;
{
	char *fn="MDquit";
	int ret;

	INIT_MODULE(fn);
	p=p;

	ret = MDdialog2("Exiting Program");

	/* ret=1 means OK to exit */
	if (ret == 1) ret = -2;
	else ret = 0;

	EXIT_MODULE(fn);
	return(ret);
}
/*----------------------------------------------------------------------------*/
/* MDapview - Prompt user for view option: form or table                      */
/*----------------------------------------------------------------------------*/
int
MDapview(p)
char *p;
{
	char *fn="MDapview";

	INIT_MODULE(fn);

	switch (*p) {
	case 'F': /* form */
	        MDcurap->recptr = DBrdseek(MDcurap->curfid,MDcurap->crsrn,(DBRECPTR)MDcurap->buf);
		MDcurap->vutable = NO;
		break;

	case 'T': /* form */
		if (MDcurap->fmp != NULLP && isset_wn(MDcurap->fmp->wnp)) {
			fm_dn(MDcurap->fmp);
		}
		MDcurap->vutable = YES;
		break;

	}
	VErefresh();

	EXIT_MODULE(fn);
	return(1);
}
