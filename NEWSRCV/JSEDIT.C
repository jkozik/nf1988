
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

#include "vv_sys.h"
#include "vv_main.h"

#include "GLdefs.h"
#include "GLstruct.h"
#include "GLextern.h"

#include "JSdefs.h"
#include "JSstruct.h"
#include "JSextern.h"

/* Global Definitions */
WINDOWPTR menuline,body,prompt,message,chartbord,charttext;
menu state;
struct JSfilerec JSfiletab[MAXJEFILE];
struct bufinfo b1;
struct bufinfo prevb1;
struct JSlnedrec JSlnedtab;
int JSrecend;
jebool JSpregluptodate;



void
main(argc,argv) 
int argc;
char *argv[];
{
   UCHAR ch;
	menu ostate;

/* Setup GL environment */
(void) GLenvsetup();
JSpregluptodate=GLuptodate();
GDanal = (GDLIST *)NULL;
GDglrpt = (GDLIST *)NULL;
GDaarpt = (GDLIST *)NULL;

JMheadon = JEFALSE;
JMlinespage = 88;
strcpy(JMpsetup,"\\x0F\\x1B\\x30");

/* Read in chart of accounts file into array, charttab.
** This array will be queried to validate account numbers.
*/
(void)CHload();

init_vv();

/*
** Create and initialize windows
*/
/*
** Initialize menuline window
*/
menuline = wn_def(0,0,1,vs_colq(),LNORMAL,BDR_NULLP);
wn_up(menuline);

/*
** Initialize body window
*/
body = wn_def(1,0,vs_rowq()-2,vs_colq(),LCLACT,BDR_NULLP);
wn_up(body);

/*
** Initialize prompt window
*/
prompt = wn_def(vs_rowq()-6,22,1,35,LARROW,BDR_SLNP);

/*
** Initialize message window
*/
message = wn_def(vs_rowq()-1,0,1,vs_colq(),LNORMAL,BDR_NULLP);
wn_up(message);

/*
** Initialize chart help window:
**  charttext - Subwindow of chartbord; used for text.
*/
charttext = wn_def(5,50,14,27,LDEBUG,BDR_SLNP);
sw_title("Chart of Accounts",LDEBUG,TOPCENTER,chartbord);





/*
** Display initial menu
*/
ostate=quit;
state=start;
strcpy(b1.filename,"");
strcpy(b1.filetmp,"");
b1.fileopened=JEFALSE;
b1.filechgd=JEFALSE;

/*
** argv[1] holds the default file name.
** load the file. go into the editor.
*/
if (argc == 2){
	strcpy(b1.filename,argv[1]);
	strcpy(b1.filetmp,argv[1]);
	JSdspmenu(edit,&b1);
	if (JMload(&b1) == JESUCCESS) {
		state=edit;
	} 
}

while( state!=quit ) {

	if (ostate != state) {
		JSdspmenu(state,&b1);
		if (b1.fileopened == JETRUE && b1.filechgd == JETRUE && ostate == edit && state != editz) {
			JMsave("jtmp",b1.JShead);
		}
		if (b1.fileopened == JETRUE && ostate == start && state == edit) {
			b1.JStopptr = JMposcur(b1.JScurptr,b1.JStopptr);
		}
		if (JSpregluptodate == JEFALSE && ostate==start && state==report) {
			JMmsg("WARNING: pregl needs to be run");
		}

		ostate = state;
		strcpy(b1.filetmp,b1.filename);
	}

   ch=(UCHAR)ki();
	switch(state) {
	case start:
		state = JMstart(ch,&b1);
		break;

	case report:
		state = JMreport(ch);
		break;

	case repset:
		state = JMsettings(ch);
		break;

	case analrd:
	case glrptrd:
	case aarptrd:
		state = JMreprd(ch);
		break;

	case analdisp:
	case glrptdisp:
	case aarptdisp:
		state = JMrepdisp(ch);
		break;

	case file:
		state = JMfile(ch,&b1);
		break;

	case edit:
		state = JMedit(ch,&b1);
		break;

	case editz:
		if (ch != 'Z') {
         beep_vv(BPBELL,BPBELL);
			state = edit;
		} else {
			/* save current file */
			if (b1.fileopened == JETRUE) {
				JMsave(b1.filename,b1.JShead);
			}
			/* Close curses */
         exit_vv();
			/* Restore working directory */
			chdir(cwdstr);
			exit(1);
		}
		break;
	default:
		fprintf(stderr,"JSedit: unknown state\n");
		JMmsg("JSedit: unknown state");
		JEinthand();
		break;
	}
}
/* Close curses */
exit_vv();
/* Restore working directory */
chdir(cwdstr);
} /* end of main */
menu
JMstart(inp_ch,actbuf)
UCHAR inp_ch;
struct bufinfo *actbuf;
{
   UCHAR ch;
	char prmtstr[40];

	switch(inp_ch) {
	case 'q':
	case 'Q':
		if (actbuf->fileopened && actbuf->filechgd) {
			/* Prompt: "Save filename? [(y)/n]"*/
			sprintf(prmtstr,"Save %s? [(y)/n]",actbuf->filename);
			ch = wprmtch(prompt,prmtstr);
			switch(ch){
			case 'n':
			case 'N':
				break;
	
			default:
				/* Prompt: Save: filename-'...' */
				wprmtfld(prompt,"Save: Enter Filename-",actbuf->filetmp);
				if (actbuf->filetmp[0] == KEY_ESC) {
					return(start);
				} 
				strcpy(actbuf->filename,actbuf->filetmp);
				JMsave(actbuf->filename,actbuf->JShead);
				actbuf->filechgd=JEFALSE;
				break;
			}
		
		} /* end if (filechgd) */

		ch = wprmtch(prompt,"Quit: Press Y to Confirm.");
      if (ch == (UCHAR)'y')
			return(quit);
		else {
			return(state);
		}
		/*break;*/

	case 'f':
	case 'F':
		return(file);
		/*break;*/

	case 'r':
	case 'R':
		JSnotyet("Reports");
		return(report);
		/*break;*/

	case 'e':
	case 'E':
		return(edit);
		/*break;*/

	default:
      beep_vv(BPBELL,BPBELL);
		break;
	}
	return(state);
}

void
JSdspmenu(state,actbuf)
menu state;
struct bufinfo *actbuf;
{
	switch (state) {
	case start:
      v_st("Edit Reports Quit",menuline);
		break;

	case file:
      v_st("New Load Save",menuline);
		break;

	case lnedit:
      v_st("Line Edit Mode, ESC-Exit",menuline);
		break;
	
	case report:
      v_st("Pregl Settings Analdtl Glrpt aaRpt",menuline);
		break;

	case repset:
      v_st("Headings Lines",menuline);
		break;


	case analrd:
      v_st("Run Display",menuline);
		break;

	case analdisp:
      v_st("Search Account",menuline);
		break;

	case glrptrd:
      v_st("Run Display",menuline);
		break;

	case glrptdisp:
      v_st("Search Account",menuline);
		break;

	case aarptrd:
      v_st("Run Display",menuline);
		break;

	case aarptdisp:
      v_st("Search Account",menuline);
		break;


	case editz:
	case edit:
      v_st("File Append Insert Change Delete Search Yank Put Undo",menuline);
		if (actbuf->filename[0] != '\0') {
         cs_mv(0,60,menuline);
         v_printf(menuline,"File-%-4.4s Cnt-%-3d",actbuf->filename,b1.JSrec_cnt);
		}
		break;

	}
}

void
JSnotyet(func)
char *func;
{
   v_printf(message,"The Function '%s' Not Implemented Yet.",func);
}

void
JMprtbody(text)
char *text;
{
	/*
	** Display text in the body window:
	** middle 20 lines of screen.
	*/
   v_st(text,body);
}
void
JMmsg(text)
char *text;
{
	/*
	** Display text in the message window:
	** bottom line of screen.
	*/
   v_st(text,message);
}
