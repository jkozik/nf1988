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


CHTYPE
wacctfld(win,buf,size)
WINDOW *win;
char *buf;
int size;
{
	/*
	** Input field similar to wgetstr()
	** Read characters using wgetch()
	** Echo using waddch()
	** Interpret DEL, INS, BS, HOME, END, etc
	** Limit input field to current line, length=size bytes
	** Characters returned in buf
	** Limit size of input to size bytes.
	** Delimit the field when a fixed number of characters 
	** are entered.
	*/
	int oy,ox;
	int curx,cury;
	int i;
	int nxtchr;
	CHTYPE ch;
	jebool insertmode;
	jebool exitfld;
	int attrsave;

	/* insertmode set off by default */
	insertmode = JEFALSE;

	/* Save current cursor location */
	getyx(win,oy,ox);

	/* display input field in standout */
	attrsave = wattrget(win);
	wattrset(win, A_COLOR(A_BLACK,A_CYAN) );
	for (i=0; i<size; i++) {
		waddch(win,' ');
	}

	/* display pre-initialized value of buf */
   if (strlen(buf) > (size_t)size) {
		buf[0]='\0';
	}
	mvwaddstr(win,oy,ox,buf);
	wmove(win,oy,ox);
	touchwin(chartbord);
	wrefresh(chartbord);
	wclear(charttext);
	JMchhelp(charttext,buf);
	wrefresh(charttext);
	wrefresh(win);

	/* Input field character processing */
	ch=getch();
	nxtchr=0;
	exitfld=JEFALSE;
	while (exitfld == JEFALSE) {
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
			
		case '\r':
		case KEY_ESC:
			exitfld=JETRUE;
			break;

		case KEY_LEFT:
			if (nxtchr > 0) {
				nxtchr--;
				wmove(win,cury,curx-1);
				wrefresh(win);
			} else {
				exitfld=JETRUE;
			}
			break;

		case KEY_RIGHT:
			if (buf[nxtchr] != 0 && nxtchr+1<size) {
				nxtchr++;
				wmove(win,cury,curx+1);
				wrefresh(win);
			} else {
				exitfld=JETRUE;
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
				buf[nxtchr]=(char)ch;
				waddstr(win,buf+nxtchr);
				nxtchr++;
				wmove(win,cury,curx+1);
				wrefresh(win);
			   } else {
				if (buf[nxtchr] == '\0') {
					buf[nxtchr+1] = '\0';
				}
				buf[nxtchr]=(char)ch;
				nxtchr++;
				if (nxtchr>=size) exitfld=JETRUE;
				waddch(win,ch);
				wrefresh(win);
			   }
			}
			break;
		}
		wclear(charttext);
		JMchhelp(charttext,buf);
		wrefresh(charttext);
		wrefresh(win);
		if (exitfld == JEFALSE)
			ch=getch();
	}
	wattrset(win, attrsave );
	wmove(win,oy,ox);
	for (i=0; i<size; i++) {
		waddch(win,' ');
	}
	mvwaddstr(win,oy,ox,buf);
	touchwin(win);
	wrefresh(win);
	if (nxtchr>=size) 
      return((char)NULL);
	else
		return(ch);
}
void
JMchhelp(win,buf)
WINDOW *win;
char *buf;
{
	/*
	** Prints the chart of accounts help window.
	** What gets printed is a function of buf's contents:
	** 1. buf="", print account numbers with length==1
	**    1 ASSESTS-WORKING
	**    2 ASSETS-FIXED
	**    3 LIABILITIES-SHORT TERM, etc.
	** 2. buf=="1", print accounts len=2 beginning with 1:
	**    1  ASSESTS-WORKING
	**    10 Cash
	**    11 Savings
	**    12 Investments, etc.
	** 3. buf=="12", print subaccount beginging with 12:
	**    12 Investments
	**    121 BSSP-JPK
	**    122 BSSP-CEK, etc.
	** 4. buf=="123", if len==3, do the same as case 3.
	*/
	
	struct chartrec *chptr;
	char *chacct;

	

	for (chptr = CHgetfst();chptr != NULL; chptr = CHgetnxt()) {
		chacct = chptr->acct;
		switch(strlen(buf)) {
		case 0:
		   if (strlen(chacct) == 1) {
			wprintw(win,"%s %.23s\n\r",chacct,chptr->text);
		   }
		   break;
		case 1:
		   if (strncmp(buf,chacct,1) == 0 && strlen(chacct) < 3) {
			wprintw(win,"%-2.2s %.22s\n\r",chacct,chptr->text);
		   }
		   break;
		case 2:
		case 3:
		   if (strncmp(buf,chacct,2) == 0) {
			wprintw(win,"%-3.3s %.21s\n\r",chacct,chptr->text);
		   }
		   break;
		default:
			break;
		}
	}
}
