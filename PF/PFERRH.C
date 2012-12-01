/* PFerrh.c - Error handler */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wfd.h>

#include "PFdefs.h"
#include "PFstruct.h"
#include "PFextern.h"

#define TOLOWER(x) tolower(x)


/*----------------------------------------------------------------------------*/
/*  Error messages                                     		              */
/*----------------------------------------------------------------------------*/
char *_wnemsg[] =			/* VCS Error messages		      */
{
"No error",                                                    /* NO ERROR    */
"Insufficient memory",                                         /* MEMLACK     */
"Memory corrupted",                                            /* BADHEAP     */
"Error reading file",                                          /* READERR     */
"Unexpected end of file",                                      /* BAD_EOF     */
"Bad parameter value ",                                        /* BADPARM     */
"Error opening file",                                          /* ERR_OPEN    */
"Error closing file",                                          /* ERR_CLOSE   */
"Error writing file",                                          /* WRITEERR    */
"Full disk",                                                   /* DISKFULL    */
"Too many lines in file",                                      /* MFILETOOBIG */
"Window coordinates invalid",                                  /* BADWNCOORD  */
"Window member wn.location must be 0",                         /* BADWNLOC    */
"Window dimensions not INSIDE or FULL",                        /* BADWNDIM    */
"File row number is negative",                                 /* MFROWNEG    */
"File row number is too large",                                /* MFROWTOOBIG */
"No MFILE pointer installed in WINDOW",                        /* NOMFILEPTR  */
"Error opening pipe",                                          /* ERR_POPEN   */
"Error closing pipe",                                          /* ERR_PCLOSE  */
"No window image was saved",                                   /* NOWNIMAGE   */
"Bad scroll direction",                                        /* BADSCRDIR   */
"NULLP not allowed as argument",                               /* BADPTR      */
"Axes do not fit within window",                               /* AXESNOFIT   */
"Bar coordinates are invalid",                                 /* BADBARCOORD */
"Video move direction not IN or OUT",                          /* BADVMDIR    */
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
"WINDOW structure is corrupted",                               /* BADWNSTRUC  */
"MFILE structure is corrupted",                                /*BADMFILESTRUC*/
"The Traceback string has been corrupted",                     /* TRSTRBAD    */
"The Call Log has been cor-\nrupted",                          /* CALLLOGBAD  */
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
/*----------------------------------------------------------------------------*/
/*  This is the start of the Windows for Data Error messages		      */
/*----------------------------------------------------------------------------*/
"Data conversion error",                                       /* DCV_ERROR   */
"Invalid picture",                                             /* BADPIC      */
"Invalid field coordinates",                                   /* BADFLDCOORD */
"Invalid prompt coordinates",                                  /* BADPRMPTCOOR*/
"Invalid text coordinates",                                    /* BADTEXTCOORD*/
"Invalid date string",                                         /* BADDATE     */
"Invalid (negative) julian date",                              /* BADJULDATE  */
"Invalid time string",                                         /* BADTIME     */
"Invalid (negative) number of seconds",                        /* BADSECONDS  */
"Invalid menu field definition",                               /* BADMENUDEF  */
"Invalid menu form",                                           /* BADMENUFORM */
"Attempted to invoke a NULL PFI",                              /* NULLPFI     */
"No data conversion function",                                 /* NODCVFUNC   */
"No picture symbol function",                                  /* NOPICSYMFUNC*/
"Non-existent field",                                          /* NONEXISTFLD */
"Cannot free standard form",                                   /* NOFREESTDFRM*/
"An invalid text string was passed",                           /* BADTEXT     */
"DFIELD structure is corrupted",                               /* BADFLDSTRUC */
"DFORM structure is corrupted",                                /* BADFRMSTRUC */
"All fields are protected - no place to move",                 /* ALLFLDSPROT */
"Function table full",                                         /* FULLTABLE   */
"Form is not on screen",                                       /* FMNOTUP     */
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
NULLP,
"Relation number is out of range (0<rel<MAXREL)",              /* BADREL      */
"Maximum database files opened (MAXDBFILE)",                   /* DBFULL      */
"Database file id is out of range (0<dbfid<MAXDBFILE)",        /* BADDBFID    */
"Domain is out of range (0<domain<MAXDMDESCTAB)",              /* BADDOMAIN   */
"Found unexpected delimitor (comma, newline, etc.)",           /* BADDELIM    */
"More that MAXACCTAMT pairs found in JETRAN input file",       /* ACCTOVFLOW  */
"More than 12 amounts found in BUDGET input file",             /* BADAMTCNT   */
"Unexpected count of characters found for domain",             /* BADLEN      */
"Month found out of range",     			       /* BADMONTH    */
"Day found out of range",      				       /* BADDAY      */
"Amount not valid",                                            /* BADAMT      */
"Account not found in chart",                                  /* BADACCTCHART*/
"Merge input inconsistent. Relation types different.",         /* BADMERGEREL */
NULLP,								/* spare 13   */
NULLP,								/* spare 14   */
NULLP,								/* spare 15   */
NULLP,								/* spare 16   */
NULLP,								/* spare 17   */
NULLP,								/* spare 18   */
NULLP,								/* spare 19   */
"Directory \$F\$YEAR does not exist",   			/* UNKDIR     */
"File '00' does not exist",     				/* MISSING00  */
"File 'chart' does not exist",  			      /* MISSINGCHART */
NULLP,								/* spare 23   */
NULLP,								/* spare 24   */
NULLP,								/* spare 25   */
NULLP,								/* spare 26   */
NULLP,								/* spare 27   */
NULLP,								/* spare 28   */
NULLP,								/* spare 29   */
NULLP,								/* spare 30   */
};

/*----------------------------------------------------------------------------*/
/* PFerrh(fcn_name) - Error handler                                           */
/*                                                                            */
/* fcn_name: Name of function where error was found.                          */
/*                                                                            */
/* Returns:                                                                   */
/*  Nothing.                                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
int 
PFerrh(p)
char *p;
{
    struct PFerrs *err;
    WINDOW wn;
    int key;
    int twndebug = _wndebug;		/*save _wndebug 		      */
    int err_code = _wn_err;		/*save _wn_err			      */

    _wndebug = OFF;			/*force debugging off		      */
    _wn_err = 0;			/*force no error		      */
    defs_wn(&wn, CENTER_WN, CENTER_WN, 12, v_coq, BDR_DLNP);
    if(_lattsw == ON)			/*are we using physical or logical att*/
    {
	sw_att(LERROR, &wn);		/*using logical attributes	      */
	sw_bdratt(LERROR, &wn);
    }
    else
    {
	sw_att(REVERSE, &wn);		/*using physical attributes	      */
	sw_bdratt(REVERSE, &wn);
    }
    sw_name("Error Function", &wn);

/*----------------------------------------------------------------------------*/
/*  Make this a pop-up window.	Recognize that if the error was because of    */
/*  insufficient memory, then we may not have enough memory left to save the  */
/*  underlying image.  If this is the case, we may not be able to pop-down    */
/*  this window if the user elects to continue. 			      */
/*----------------------------------------------------------------------------*/
    sw_popup(ON, &wn);

    set_wn(&wn);
    v_st("An error was detected by the ", &wn);
    v_st(p, &wn);
    v_st("() function.\n\n", &wn);
    err = &PFerrgdata;
    if (err->filename[0] != '\0') {
		v_printf(&wn, "File-%s Line-%d Relation Type-%s\n",err->filename,err->currow+1,err->relname);
		v_printf(&wn, "Input-%s",err->line);
    }
    v_st("\nThe error message is\n\n", &wn);
    if (err_code >= 1000) {
	/*v_st(PFemsg[err_code-1000], &wn);*/
    } else {
    	v_st(wnerrmsg(err_code), &wn);
    }
    v_st(".\n\nDo you want to continue [y/n]?", &wn);
    pl_csr(&wn);
    do
    {
	key = ki();
	key = TOLOWER(key);
	if(key == 'y')
	{
	    unset_wn(&wn);
	    _wndebug = twndebug;	/*restore debugging state	      */
	    *PFerrln1 = '\0';
	    *PFerrln2 = '\0';
	    return(0);
	}
	else if(key == 'n')
	{
	    mv_csr(v_rwq - 2, 0, &wn0);
	    exit_wfc();
	    PFexit(err_code);
	}
    }while(TRUE);
}
