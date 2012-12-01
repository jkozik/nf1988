#include "curses.h"
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
#define CTRL(x) (x & 0x1f)

/* Global Definitions */
WINDOW *menuline,*prompt,*message;
menu state;
struct JSfilerec JSfiletab[MAXJEFILE];
struct JSfilerec *JShead,*JStail;
int JSrec_cnt;
char filename[SZPATH];
char filetmp[SZPATH];
jebool fileopened;
jebool filechgd;

/* Function Templates */
void JSdspmenu(menu);
menu JMstart(CHTYPE);
menu JMfile(CHTYPE);
menu JMedit(CHTYPE);
void JSnotyet(char *);
void wgetfld(WINDOW *, char *, int);
void JMnew();
int JMload(char *);

main() 
{
	int i;
	CHTYPE ch;
	menu ostate;

/* Setup GL environment */
(void) GLenvsetup();

/* Read in chart of accounts file into array, charttab.
** This array will be queried to validate account numbers.
*/
(void)CHload();

/*
** Initialize curses environment
*/
if (ERR == initscr() ) {
	fprintf(stderr, "JSedit: cannot initialize curses\n");
	JEinthand();
}
/* Function key translation */
keypad(stdscr, TRUE);
/* let the program echo characters */
noecho();
/* do not return after linefeed */
nonl();

/*
** Create and initialize windows
*/
menuline=newwin(1,80,0,0);
leaveok(menuline,TRUE);
wattrset(menuline, A_COLOR(A_BRIGHTWHITE,A_BLUE) );
wclear(menuline);

prompt=newwin(3,35,16,22);
leaveok(prompt,TRUE);
wclear(prompt);

message = newwin(1,80,22,0);
leaveok(message,TRUE);
wclear(message);

wrefresh(stdscr);


/*
** Display initial menu
*/
ostate=quit;
state=start;
strcpy(filename,"");
strcpy(filetmp,"");
fileopened=JEFALSE;
filechgd=JEFALSE;

while( state!=quit ) {

	if (ostate != state) {
		wclear(prompt);
		wrefresh(prompt);
		wclear(message);
		wrefresh(message);
		JSdspmenu(state);
		ostate = state;
		strcpy(filetmp,filename);
	}

	ch=getch();
	switch(state) {
	case start:
		state = JMstart(ch);
		break;

	case file:
		state = JMfile(ch);
		break;

	case edit:
		state = JMedit(ch);
		break;

	default:
		fprintf(stderr,"JSedit: unknown state\n");
		JEinthand();
		break;
	}
}
/* Close curses */
endwin();
/* Restore working directory */
chdir(cwdstr);
} /* end of main */
menu
JMstart(inp_ch)
CHTYPE inp_ch;
{
	CHTYPE ch;

	switch(inp_ch) {
	case 'q':
	case 'Q':
		if (fileopened && filechgd) {
			/* Prompt: "Save filename? [(y)/n]"*/
			wclear(prompt);
			box(prompt,S_VERT,S_HOR);
			mvwaddstr(prompt,1,1," Save-");
			wstandout(prompt);
			waddstr(prompt,filename);
			wstandend(prompt);
			waddstr(prompt,"? [(y)/n]");
			wrefresh(prompt);
	
			/* get reply */
			ch=getch();
			switch(ch){
			case '\r':
			case 'y':
			case 'Y':
				break;
	
			default:
				/* Prompt: Save: filename-'...' */
				wclear(prompt);
				box(prompt,S_VERT,S_HOR);
				mvwaddstr(prompt,1,1," Save: Enter Filename-");
				(void)wgetfld(prompt,filetmp,10);
				if (filetmp[0] == KEY_ESC) {
					wclear(prompt);
					wrefresh(prompt);
					return(start);
				} 
				strcpy(filename,filetmp);
				filechgd=JEFALSE;
				break;
			}
		
		} /* end if (filechgd) */

		wclear(prompt);
		box(prompt,S_VERT,S_HOR);
		mvwaddstr(prompt,1,1," Quit: Press Y to Confirm.");
		wrefresh(prompt);
		if (getch() == (CHTYPE)'y')
			return(quit);
		else {
			wclear(prompt);
			wrefresh(prompt);
			return(state);
		}
		break;

	case 'f':
	case 'F':
		return(file);
		break;

	default:
		beep();
		return(state);
		break;
	}
}
menu
JMedit(inp_ch)
CHTYPE inp_ch;
{
	switch(inp_ch) {
	case KEY_ESC:
		wclear(message);
		wrefresh(message);
		return(file);
		break;

	case 'I':
	case 'i':
		JSnotyet("Insert");
		break;
	
	case 'U':
	case 'u':
		JSnotyet("Update");
		break;

	case 'd':
	case 'D':
		JSnotyet("Delete");
		break;

	default:
		beep();
		break;
	}
	return(edit);
}

void
JSdspmenu(state)
menu state;
{
	wclear(menuline);
	switch (state) {
	case start:
		mvwaddstr(menuline,0,0,"File Quit");
		break;

	case file:
		mvwaddstr(menuline,0,0,"New Load Save");
		break;


	case edit:
		mvwaddstr(menuline,0,0,"Insert Update Delete");
		if (filename[0] != '\0') {
			wmove(menuline,0,60);
			wprintw(menuline,"File-%-4.4s Cnt-%-3d",filename,JSrec_cnt);
		}
		break;

	}
	wrefresh(menuline);
}

void
JSnotyet(func)
char *func;
{
	wclear(message);
	mvwaddstr(message,0,0,"The Function ");
	wstandout(message);
	waddstr(message,func);
	wstandend(message);
	waddstr(message," Not Implemented Yet.");
	wrefresh(message);
}

void
wgetfld(win,buf,size)
WINDOW *win;
char *buf;
int size;
{
	/*
	** Input field similar to wgetstr()
	** Read characters using wgetch()
	** Echo using waddch()
	** Interpret DEL, INS, BS, HOME, END
	** Limit input field to current line, length=size bytes
	** Characters returned in buf
	** Limit size of input to size bytes.
	*/
	int ox,oy;
	int curx,cury;
	int i;
	int nxtchr;
	CHTYPE ch;
	jebool insertmode;

	/* insertmode set off by default */
	insertmode = JEFALSE;

	/* get origin of input field */
	getyx(win,oy,ox);

	/* display input field in standout */
	wstandout(win);
	for (i=0; i<size; i++) {
		waddch(win,' ');
	}

	/* display pre-initialized value of buf */
	if (strlen(buf) > size) {
		buf[0]='\0';
	}
	mvwaddstr(win,oy,ox,buf);

	/* turn-on cursor */
	leaveok(win,FALSE);
	wmove(win,oy,ox);
	wrefresh(win);

	/* Input field character processing */
	ch=getch();
	nxtchr=0;
	while(ch!=(CHTYPE)'\r' && ch!=(CHTYPE)KEY_ESC) {
		getyx(win,cury,curx);
	   	switch(ch) {
		case erasechar():
			if (nxtchr > 0) {
				for(i=nxtchr-1; buf[i]!='\0'; i++){
					buf[i] = buf[i+1];
				}
				mvwaddstr(win,cury,curx-1,buf+nxtchr-1);
				waddch(win,' ');
				wmove(win,cury,curx-1);
				wrefresh(win);
				nxtchr--;
			} else {
				beep();
			}
			break;

		case KEY_DC:
			if (buf[nxtchr] != '\0') {
				for(i=nxtchr; buf[i]!='\0'; i++){
					buf[i] = buf[i+1];
				}
				waddstr(win,buf+nxtchr);
				waddch(win,' ');
				wmove(win,cury,curx);
				wrefresh(win);
			} else {
				beep();
			}
			break;
			

		case KEY_LEFT:
			if (nxtchr > 0) {
				nxtchr--;
				wmove(win,cury,curx-1);
				wrefresh(win);
			} else {
				beep();
			}
			break;

		case KEY_RIGHT:
			if (buf[nxtchr] != 0) {
				nxtchr++;
				wmove(win,cury,curx+1);
				wrefresh(win);
			} else {
				beep();
			}
			break;

		case KEY_HOME:
			nxtchr=0;
			wmove(win,oy,ox);
			wrefresh(win);
			break;

		case KEY_END:
			while (buf[nxtchr] != '\0') nxtchr++;
			wmove(win,oy,ox+nxtchr);
			wrefresh(win);
			break;

		case KEY_cEND:
		case CTRL('K'):
			for ( i=nxtchr; buf[i]!='\0'; i++) {
				waddch(win,' ');
			}
			buf[nxtchr] = '\0';
			wmove(win,cury,curx);
			wrefresh(win);
			break;

		case KEY_IC:
			if (insertmode == JETRUE)
				insertmode = JEFALSE;
			else 
				insertmode = JETRUE;
			wrefresh(win);
			break;

		case killchar():
			nxtchr=0;
			buf[0]='\0';
			wmove(win,oy,ox);
			
			for (i=0; i<size; i++) {
				waddch(win,' ');
			}
			wmove(win,oy,ox);
			wrefresh(win);
			break;

		default:
			if (nxtchr>=size || !isprint(ch) ) {
				beep();
			} else {
			   if (insertmode) {
				for (i=nxtchr; buf[i]!='\0'; i++);
				for (; i>=nxtchr; i-- ) {
					if ( !(i+1 >= size) )
					  buf[i+1] = buf[i];
				}
				buf[nxtchr]=ch;
				waddstr(win,buf+nxtchr);
				nxtchr++;
				wmove(win,cury,curx+1);
				wrefresh(win);
			   } else {
				if (buf[nxtchr] == '\0') {
					buf[nxtchr+1] = '\0';
				}
				buf[nxtchr]=ch;
				nxtchr++;
				waddch(win,ch);
				wrefresh(win);
			   }
			}
			break;
		}
	ch=getch();
	}
	wstandend(win);

	if (ch==(CHTYPE)KEY_ESC) {
		buf[0]=KEY_ESC;
		buf[1]='\0';
		wmove(win,oy,ox);
			
		for (i=0; i<size; i++) {
			waddch(win,' ');
		}
		wmove(win,oy,ox);
	}
	leaveok(win,TRUE);
	wrefresh(win);
}
menu
JMfile(inp_ch)
CHTYPE inp_ch;
{
	CHTYPE ch;

	/*
	** If a file is opened and modified, the 
	** following code prompts the user to save the
	** the currently open file.
	*/
	switch(inp_ch) {
	case 'l':
	case 'L':
	case 'n':
	case 'N':

		if (fileopened && filechgd) {
			/* Prompt: "Save filename? [(y)/n]"*/
			wclear(prompt);
			box(prompt,S_VERT,S_HOR);
			mvwaddstr(prompt,1,1," Save-");
			wstandout(prompt);
			waddstr(prompt,filename);
			wstandend(prompt);
			waddstr(prompt,"? [(y)/n]");
			wrefresh(prompt);
	
			/* get reply */
			ch=getch();
			switch(ch){
			case '\r':
			case 'y':
			case 'Y':
				break;
	
			default:
				/* Prompt: Save: filename-'...' */
				wclear(prompt);
				box(prompt,S_VERT,S_HOR);
				mvwaddstr(prompt,1,1," Save: Enter Filename-");
				(void)wgetfld(prompt,filetmp,10);
				if (filetmp[0] == KEY_ESC) {
					wclear(prompt);
					wrefresh(prompt);
					return(start);
				} 
				strcpy(filename,filetmp);
				filechgd=JEFALSE;
				break;
			}
		
		} /* end if (filechgd) */
	} /* end switch */

	switch(inp_ch) {
	case KEY_ESC:
		wclear(message);
		wrefresh(message);
		return(start);
		break;

	case 'N':
	case 'n':
		wclear(prompt);
		box(prompt,S_VERT,S_HOR);
		mvwaddstr(prompt,1,1," New: Enter Filename-");
		(void)wgetfld(prompt,filetmp,10);
		if (filetmp[0] == KEY_ESC) {
			wclear(prompt);
			wrefresh(prompt);
			return(start);
		} else {
			if (access(filetmp,0) != 0) {
				strcpy(filename,filetmp);
				(void) JMnew();
				fileopened=JETRUE;
				filechgd=JEFALSE;
				return(edit);
			} else {
				wclear(message);
				waddstr(message,"File-");
				wstandout(message);
				waddstr(message,filetmp);
				wstandend(message);
				waddstr(message," Already Exists");
				wrefresh(message);
				return(file);
			}
		}
		break;
		return(edit);
		break;

	case 'L':
	case 'l':
		wclear(message);
		wrefresh(message);

		
		wclear(prompt);
		box(prompt,S_VERT,S_HOR);
		mvwaddstr(prompt,1,1," Load: Enter Filename-");
		(void)wgetfld(prompt,filetmp,10);

		if (filetmp[0] == KEY_ESC) {
			wclear(prompt);
			wrefresh(prompt);
			return(start);
		} else {
			wclear(message);
			if (JMload(filetmp) == JESUCCESS) {
				strcpy(filename,filetmp);
				fileopened=JETRUE;
				filechgd=JEFALSE;
				return(edit);
			} else {
				wrefresh(message);
				return(file);
			} /* access */
		} /* KEY_ESC test */
		break;

	case 'S':
	case 's':
		JSnotyet("Save");
		wclear(prompt);
		box(prompt,S_VERT,S_HOR);
		mvwaddstr(prompt,1,1," Save: Enter Filename-");
		(void)wgetfld(prompt,filetmp,10);
		if (filetmp[0] == KEY_ESC) {
			wclear(prompt);
			wrefresh(prompt);
			return(start);
		} 
		strcpy(filename,filetmp);
		filechgd=JEFALSE;
		return(file);
		break;

	default:
		beep();
		break;
	}
	return(file);
}
int
JMload(file)
char *file;
{
	FILE *fp;
	int rec_cnt;

	char line[SZLINE];

	int i;
	rec_cnt=0;


	/*
	** Open file for read only.
	*/
	if ((fp = fopen(file,"r")) == NULL ) {
		waddstr(message,"File-");
		wstandout(message);
		waddstr(message,file);
		wstandend(message);
		waddstr(message," Not Found");
		wrefresh(message);
		return(JEFAIL);
	}
	
	/* 
	** Initialize data structure JSfiletab[]
	*/
	for (i=0; i<MAXJEFILE; i++) {
		JSfiletab[i].line[0] = '\0';
		JSfiletab[i].next = NULL;
		JSfiletab[i].prev = NULL;
	}

	/*
	** Read input, validate, and store into data structure
	*/
	while ( fgets(line,sizeof(line),fp) != (char *)NULL) {
		/*
		** Validate input:
		** 1. Check for valid date: 0131,
		** 2. Check that first account number is valid: 101
		** 3. Support only one format:
		**    - 0131,-101,...
		** 4. If this much is okay, then the file must be okay!?
		*/
		if (getjdate(line)==NULL || getacct(line+SZDATE+2)==NULL) {
			waddstr(message,"File-");
			wstandout(message);
			waddstr(message,file);
			wstandend(message);
			waddstr(message," Does Not Conform to 0131,-101 format.");
			wprintw(message," Rec-%d.",rec_cnt+1);
			wrefresh(message);
			fclose(fp);
			fileopened=JEFALSE;
			filechgd=JEFALSE;
			return(JEFAIL);
		}

		/* copy line into JSfiletab[rec_cnt] */
		strcpy(JSfiletab[rec_cnt].line,line);
		if (rec_cnt > 0) {
			JSfiletab[rec_cnt].prev=&JSfiletab[rec_cnt-1];
			JSfiletab[rec_cnt-1].next=&JSfiletab[rec_cnt];
		}
		rec_cnt++;

	}
	JShead = &JSfiletab[0];
	JStail = &JSfiletab[rec_cnt];
	JSrec_cnt = rec_cnt;
	/* close file */
	fclose(fp);
	return ( JESUCCESS);
}
void
JMnew()
{

	int i;
	/* 
	** Initialize data structure JSfiletab[]
	*/
	for (i=0; i<MAXJEFILE; i++) {
		JSfiletab[i].line[0] = '\0';
		JSfiletab[i].next = NULL;
		JSfiletab[i].prev = NULL;
	}
	JShead = &JSfiletab[0];
	JStail = JShead;
	JSrec_cnt = 0;
}
