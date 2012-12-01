
#include <string.h>
#include <ctype.h>
#ifndef turboc
#include <search.h>
#include <direct.h>
#include <sys/types.h>
#else
#include <dir.h>
#endif
#include <stdlib.h>
#include <sys/stat.h>

#include "qwindow.h"
#include "keys.h"

#include "vv_sys.h"

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

#include "JSdefs.h"
#include "JSstruct.h"
#include "JSextern.h"

/* Global Definitions */
char DElinespage[3];
char DEheadon[2];
GDLIST *GDanal,*GDglrpt,*GDaarpt;
jebool JMheadon;
int JMlinespage;
char JMpsetup[30];

/* function templates */
int validate_lines(char *);
int validate_headon(char *);
int validate_psetup(char *);

menu
JMreport(inp_ch)
UCHAR inp_ch;
{
	QWINDOW *wnd;
	FIELD *fld;

	switch(inp_ch) {
	case KEY_ESC:
		return(start);
		/* break */

	case 'p':
	case 'P':
		/* pregl */
		JMpregl();
		JSpregluptodate=JETRUE;
		JMmsg("");

		GDunload(GDanal);
		GDanal = NULL;

		GDunload(GDglrpt);
		GDglrpt = NULL;

		GDunload(GDaarpt);
		GDaarpt = NULL;

		return(report);
		break;

	case 's':
	case 'S':
		/* settings */
		wclear(body);
		leaveok(body,FALSE);
		wrefresh(body);

		/* unpack variables into strings */
		sprintf(DElinespage,"%2d",JMlinespage);
		if (JMheadon==JETRUE) strcpy(DEheadon,"Y");
		else strcpy(DEheadon,"N");
	
		/* data entry window */
		wnd = establish_window(10, 5, 7, 50);
		set_title(wnd, " Printer Settings ");
		set_colors(wnd, ALL, BLUE, AQUA, BRIGHT);
		set_colors(wnd, ACCENT, WHITE, BLACK, DIM);
		display_window(wnd);
		wprompt(wnd, 5, 1, "Lines Per Page:");
		wprompt(wnd, 5, 2, "Headings on:");
		wprompt(wnd, 5, 3, "Printer Setup:");

		init_template(wnd);
		fld = establish_field(wnd, 21, 1, "__", DElinespage, 'N');
		field_validate(fld,validate_lines);
		fld = establish_field(wnd, 21, 2, "_", DEheadon, 'A');
		field_validate(fld,validate_headon);
		fld = establish_field(wnd, 21, 3, "___________________", JMpsetup,'a');
		field_validate(fld,validate_psetup);

		while(data_entry(wnd) != ESC) ;
		delete_window(wnd); 
	
		leaveok(body,TRUE);
		wrefresh(body);

		/* pack variables into original data type */
		JMlinespage=atoi(DElinespage);
		if (*DEheadon=='Y') JMheadon=JETRUE;
		else                JMheadon=JEFALSE;
		return (state);
		break;

	case 'g':
	case 'G':
		/* glrpt */
		return(glrptrd);
		break;

	case 'r':
	case 'R':
		/* aarpt */
		return(aarptrd);
		break;

	case 'a':
	case 'A':
		/* analdtl */
		return(analrd);
		break;

	default:
		beep();
		break;
	}
	return(report);
}
menu
JMreprd(inp_ch)
UCHAR inp_ch;
{
	/*
	** Prompt user to Run or Display current report.
	*/
	UCHAR exitch;
	jebool acctvld;

	*searchstr='\0';
	switch(inp_ch) {
	case KEY_ESC:
		return(report);
		/* break */

	case 'd':
	case 'D':
		/* display */
		if (state == analrd)  {
			if (GDanal == (GDLIST *)NULL) {
				GDanal = GDdefine();
				if (GDanal == (GDLIST *)NULL) {
					JMmsg("Display: out of memory");
					return(analrd);
				}
				if (GDload(GDanal,"anal.out") == JEFAIL) {
					JMmsg("Display: anal.out not found");
					return(analrd);
				} 
			}
			GDhome(GDanal);
			return(analdisp);
		}else if (state == glrptrd) {
			if (GDglrpt == (GDLIST *)NULL) {
				GDglrpt = GDdefine();
				if (GDglrpt == (GDLIST *)NULL) {
					JMmsg("Display: out of memory");
					return(glrptrd);
				}
				if (GDload(GDglrpt,"gl.out") == JEFAIL) {
					JMmsg("Display: gl.out not found");
					return(glrptrd);
				} 
			}
			GDhome(GDglrpt);
			return(glrptdisp);
		}else if (state == aarptrd) {
			if (GDaarpt == (GDLIST *)NULL) {
				GDaarpt = GDdefine();
				if (GDaarpt == (GDLIST *)NULL) {
					JMmsg("Display: out of memory");
					return(aarptrd);
				}
				if (GDload(GDaarpt,"aa.out") == JEFAIL) {
					JMmsg("Display: gl.out not found");
					return(aarptrd);
				} 
			}
			GDhome(GDaarpt);
			return(aarptdisp);
		} else {
			return(report);
		}
		break;

	case 'r':
	case 'R':
		/* run */
		switch (state) {
		case analrd:
			/* prompt for account number */
		   leaveok(prompt,FALSE);
		   acctvld = JEFALSE;
		   while (acctvld == JEFALSE) {
			exitch =wprmtafld(prompt,"Enter Account-",searchstr);
		   	if (exitch == KEY_ESC) {
		   		/*
		   		** clear screen
		   		*/
		   		touchwin(body);
		   		wrefresh(body);

				leaveok(prompt,TRUE);
				return(report);
				break;
			}
	
		   	/* validate account number */
		   	acctvld=JETRUE;
		   	if (strlen(searchstr) != SZACCT) {
				JMmsg("Invalid Account: Must be three digits"); 
				beep();
				acctvld=JEFALSE;
		   	} else if (CHvalid(searchstr) == NULL) {
				JMmsg("Invalid Account Number");
				beep();
				acctvld=JEFALSE;
		   	}
		   } /* End of Validation Loop */
		   leaveok(prompt,TRUE);

		   /* run analdtl */
		   JManaldtl(searchstr);
		   if (GDanal != (GDLIST *)NULL) {
			GDunload(GDanal);
			GDanal = (GDLIST *)NULL;
		   }
		   JMmsg("Displaying...");
		   GDanal = GDdefine();
		   if (GDanal == (GDLIST *)NULL) {
			   JMmsg("Display: out of memory");
			   return(analrd);
		   }
		   if (GDload(GDanal,"anal.out") == JEFAIL) {
			   JMmsg("Display: anal.out not found");
			   return(analrd);
		   } 
		   GDhome(GDanal);
		   JMmsg("");
		   return(analdisp);
		   break;

		case glrptrd:
			/* run glrpt */
			JMmsg("glrpt: starting...");
			if (JMglrpt() != JESUCCESS) {
				JMmsg("glrpt: failed");
			} else {
				JMmsg("glrpt: successful");
			}
			if (GDglrpt != (GDLIST *)NULL) {
				GDunload(GDglrpt);
				GDglrpt = (GDLIST *)NULL;
			}
			JMmsg("Displaying...");
			GDglrpt = GDdefine();
			if (GDglrpt == (GDLIST *)NULL) {
		 		JMmsg("Display: out of memory");
		 		return(glrptrd);
			}
			if (GDload(GDglrpt,"gl.out") == JEFAIL) {
		 	JMmsg("Display: gl.out not found");
		 	return(glrptrd);
			} 
			GDhome(GDglrpt);
			JMmsg("");
			return(glrptdisp);

			break;

		case aarptrd:
			/* run aarpt */
			JMmsg("aarpt: starting...");
			if (JMaarpt() != JESUCCESS) {
				JMmsg("aarpt: failed");
			} else {
				JMmsg("aarpt: successful");
			}

		        if (GDanal != (GDLIST *)NULL) {
			    GDunload(GDanal);
			    GDanal = (GDLIST *)NULL;
		        }
			JMmsg("Displaying...");
			GDaarpt = GDdefine();
			if (GDaarpt == (GDLIST *)NULL) {
		 		JMmsg("Display: out of memory");
		 		return(aarptrd);
			}
			if (GDload(GDaarpt,"aa.out") == JEFAIL) {
		 	JMmsg("Display: gl.out not found");
		 	return(aarptrd);
			} 
			GDhome(GDaarpt);
			JMmsg("");
			return(aarptdisp);

			break;
		default:
			return(state);
			break;
		}
	default:
		beep();
		return(state);
		break;
	}
}

menu
JMrepdisp(inp_ch)
UCHAR inp_ch;
{
	/*
	** Prompt user to Display current report.
	** Give one of the following options:
	**  Search for any field
	**  Search for any account
	**  Home
	**  End
	**  PgUp
	**  PgDn
	**  Up one line
	**  Down one line
	*/

	jebool acctvld;
	UCHAR exitch;
	GDLIST *list;

	if (state == analdisp)
		list=GDanal;
	else if (state == glrptdisp)
		list=GDglrpt;
	else if (state == aarptdisp)
		list=GDaarpt;

	JMmsg("");
	switch(inp_ch) {
	case KEY_ESC:
		if (state == analdisp)
			return(analrd);
		else if (state == glrptdisp)
			return(glrptrd);
		else if (state == aarptdisp)
			return(aarptrd);
		/* break; */

	case KEY_HOME:
		GDhome(list);
		break;

	case KEY_END:
		GDend(list);
		break;

	case KEY_NPAGE:
		GDpgdn(list);
		break; 

	case KEY_PPAGE:
		GDpgup(list);
		break;

	case KEY_DOWN:
		GDcurdn(list);
		break;

	case KEY_UP:
		GDcurup(list);
		break;

	case 'a':
	case 'A':
		/* search for an account number */
			/* prompt for account number */
		   leaveok(prompt,FALSE);
		   acctvld = JEFALSE;
		   while (acctvld == JEFALSE) {
			exitch =wprmtafld(prompt,"Enter Account-",searchstr);
		   	if (exitch == KEY_ESC) {
		   		/*
		   		** clear screen
		   		*/
		   		touchwin(body);
		   		wrefresh(body);

				leaveok(prompt,TRUE);
				return(state);
				break;
			}
	
		   	/* validate account number */
		   	acctvld=JETRUE;
		   	if (strlen(searchstr) != SZACCT) {
				JMmsg("Invalid Account: Must be three digits"); 
				beep();
				acctvld=JEFALSE;
		   	} else if (CHvalid(searchstr) == NULL) {
				JMmsg("Invalid Account Number");
				beep();
				acctvld=JEFALSE;
		   	}
		   } /* End of Validation Loop */
		   leaveok(prompt,TRUE);

		   /*
		   ** clear screen
		   */
		   touchwin(body);
		   wrefresh(body);

  		   GDsearch(list,searchstr);
		break;

	case 's':
	case 'S':
		/* search for a string */
		wprmtfld(prompt,"Search-",searchstr);
		if (searchstr[0] == KEY_ESC) {
			wclear(prompt);
			wrefresh(prompt);
			touchwin(body);
			wrefresh(body);
			return(state);
		} 
		GDsearch(list,searchstr);

		break;
	default:
		JMmsg("Valid Keys: Home, End, PgUp, PgDn, \x18, \x19, ESC");
		beep();
	}
	return(state);
}
UCHAR
wprmtafld(win,prmttext,input)
WINDOWPTR  win;
char *prmttext;
char *input;
{
	wclear(win);
	box(win,S_VERT,S_HOR);
	mvwaddstr(win,1,2,prmttext);
	return(wacctfld(win,input,SZACCT));
}
menu
JMsettings(inp_ch)
UCHAR inp_ch;
{
	/* prompt user for report output options */
	switch(inp_ch) {
	case KEY_ESC:
		return(report);
		break;

	case 'h':
	case 'H':
		/* heading */

		break;

	case 'l':
	case 'L':
		/* lines per page */

		break;
	
	default:
		beep();
		break;
	}
	return(state);
}

int validate_headon(bf)
char *bf;
{
	char sbuf[80];
	if (strcmp(bf,"Y")==0 || strcmp(bf,"N")==0 ) return QOK;

	sprintf(sbuf," Y or N ");
	error_message(sbuf);
	return QERROR;
}

int validate_lines(bf)
char *bf;
{
	int i;
	i=atoi(bf);
	if (i >= 10 && i <= 99) {
		return QOK;
	} else {
		error_message("Valid Range: 10..99");
		return QERROR;
	}
}

int validate_psetup(bf)
char *bf;
{
	bf = bf;

	return(QOK);
}

void
JMwrprtsu(fp)
FILE *fp;
{
	char *p,*radix;
	char *dig1,*dig0;
	int outch;

	/*
	** For each character in the printer setup string, PMpsetup,
	** check for \xxx or \0xx and convert escape sequence to
	** character.
	*/
	for (p=JMpsetup; *p!='\0'; p++) {
		if (*p != '\\') {
			fputc(*p, fp);
			continue;
		}

		/* escape character found, translate into character */
		radix = p+1;
		dig1  = p+2;
		dig0  = p+3;

		switch(*radix) {
		case 'x':
		case 'X':	/* process \xxx */
			if (isxdigit(*dig1) && isxdigit(*dig0)) {
				if (isalpha(*dig1)) outch = tolower(*dig1) - 'a' + 10;
				else               outch = *dig1 - '0';

				outch = outch<<4;
				if (isalpha(*dig0)) outch = outch | (tolower(*dig0)-'a'+10);
				else					 outch = outch | *dig0-'0';

				fputc((char)outch, fp);
				p = p+3;

			} else {  /*  \x is not followed by two hex digits */
				fputc(*radix, fp);
				p++;
			}
			break;

		case '0':  /* process \0XX */
			if (isdigit(*dig1) && isdigit(*dig0)) {
				outch = ((*dig1-'0')*10) | (*dig0-'0');
				fputc((char)outch, fp);
				p = p+3;
			} else {
				fputc(*radix, fp);
				p++;
			}
			break;

		default:
			fputc(*radix, fp);
			p++;
			break;
		} /* switch */

	  	} /* for */



}
