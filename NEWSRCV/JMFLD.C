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

void
wgetfld(win,buf,size)
WINDOWPTR  win;
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
	UCHAR ch;
	jebool insertmode;
	int attrsave;

	/* insertmode set off by default */
	insertmode = JEFALSE;

	/* get origin of input field */
   oy = win->r;
   ox = win->c;

	/* display input field in standout */
	attrsave = wattrget(win);
	wattrset(win, A_COLOR(A_BLACK,A_CYAN) );
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
	while(ch!=(UCHAR)'\r' && ch!=(UCHAR)KEY_ESC) {
      cury = win->r;
      curx = win->c;
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
				waddch(win,ch);
				wrefresh(win);
			   }
			}
			break;
		}
	ch=getch();
	}

	if (ch==(UCHAR)KEY_ESC) {
		buf[0]=KEY_ESC;
		buf[1]='\0';
		wmove(win,oy,ox);
			
		for (i=0; i<size; i++) {
			waddch(win,' ');
		}
		wmove(win,oy,ox);
	}
	leaveok(win,TRUE);
	wattrset(win, attrsave );
	wmove(win,oy,ox);
	for (i=0; i<size; i++) {
		waddch(win,' ');
	}
	mvwaddstr(win,oy,ox,buf);
	wrefresh(win);
}
UCHAR
wfixdfld(win,buf,size)
WINDOWPTR  win;
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
	UCHAR ch;
	jebool insertmode;
	jebool exitfld;
	int attrsave;

	/* insertmode set off by default */
	insertmode = JEFALSE;

	/* Save current cursor location */
   oy = win->r;
   ox = win->c;

	/* display input field in standout */
	attrsave = wattrget(win);
	wattrset(win, A_COLOR(A_BLACK,A_CYAN) );
	for (i=0; i<size; i++) {
		waddch(win,' ');
	}

	/* display pre-initialized value of buf */
	if (strlen(buf) > size) {
		buf[0]='\0';
	}
	mvwaddstr(win,oy,ox,buf);
	wmove(win,oy,ox);
	wrefresh(win);

	/* Input field character processing */
	ch=getch();
	nxtchr=0;
	exitfld=JEFALSE;
	while (exitfld == JEFALSE) {
      cury = win->r;
      curx = win->c;
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
	if (exitfld == JEFALSE)
		ch=getch();
	}
	wattrset(win, attrsave );
	wmove(win,oy,ox);
	for (i=0; i<size; i++) {
		waddch(win,' ');
	}
	mvwaddstr(win,oy,ox,buf);
	wrefresh(win);
	if (nxtchr>=size) 
		return(NULL);
	else
		return(ch);
}
UCHAR
wamtfld(win,buf,size)
WINDOWPTR  win;
char *buf;
int size;
{
	/*
	** Input field similar to wgetstr()
	** Numbers, +, -, . characters only.
	** Read characters using wgetch()
	** Echo using waddch()
	** Interpret DEL, INS, BS, HOME, END, etc
	** Limit input field to current line, length=size bytes
	** Characters returned in buf
	** Limit size of input to size bytes.
	** Delimit the field when a fixed number of characters 
	** are entered, or when two decimal places are entered.
	*/
	int oy,ox;
	int curx,cury;
	int i;
	int nxtchr;
	UCHAR ch;
	jebool insertmode;
	jebool exitamt;
	short attrsave;
	/* insertmode set off by default */
	insertmode = JEFALSE;

	/* Save current cursor location */
   oy = win->r;
   ox = win->c;

	/* display input field in standout */
	attrsave = wattrget(win);
	wattrset(win, A_COLOR(A_BLACK,A_CYAN) );
	for (i=0; i<size; i++) {
		waddch(win,' ');
	}

	/* display pre-initialized value of buf */
	if (strlen(buf) > size) {
		buf[0]='\0';
	}
	mvwaddstr(win,oy,ox,buf);
	wmove(win,oy,ox);
	wrefresh(win);

	/* Input field character processing */
	nxtchr=0;
	exitamt=JEFALSE;
	while (exitamt == JEFALSE) {
      cury = win->r;
      curx = win->c;
		ch=getch();
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
			
		case KEY_RETURN:
		case KEY_ESC:
			if (nxtchr+3<=size && nxtchr>0 && strpbrk(buf,".")==NULL)
				strcat(buf,".00");

			exitamt=JETRUE;
			break;

		case KEY_LEFT:
			if (nxtchr > 0) {
				nxtchr--;
				wmove(win,cury,curx-1);
				wrefresh(win);
			} else {
				exitamt=JETRUE;
			}
			break;

		case KEY_RIGHT:
			if (buf[nxtchr] != 0) {
				nxtchr++;
				wmove(win,cury,curx+1);
				wrefresh(win);
			} else {
				exitamt=JETRUE;
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
			if (nxtchr>=size || !isprint(ch) || (ch!='-' && ch!='.' && !isdigit(ch)) ) {
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
				if (nxtchr>3 && buf[nxtchr-3]=='.')
					exitamt=JETRUE;
				waddch(win,ch);
				wrefresh(win);
			   }
			}
			break;
		}
	   if(exitamt == JETRUE && strlen(buf)>0){

		if (strpbrk(buf,".") == NULL) {
			exitamt=JEFALSE;
			JMmsg("Invalid Amount: Exactly 2 decimal places required\n");
			wrefresh(win);
		}

		for(i=0; buf[i]!='\0' && exitamt==JETRUE; i++) {
			if(buf[i]=='-' && i!=0) {
			   exitamt=JEFALSE;
			   JMmsg("Invalid Amount: Unexpected sign.");
			   wrefresh(win);
			}
			if(buf[i]=='.' && buf[i+3]!='\0') {
			   exitamt=JEFALSE;
			   JMmsg("Invalid Amount: Exactly 2 decimal places required\n");
			   wrefresh(win);
			}
		}
			
	   }
	}
	wattrset(win, attrsave );
	wmove(win,oy,ox);
	for (i=0; i<size-strlen(buf); i++) {
		waddch(win,' ');
	}
	waddstr(win,buf);
	wrefresh(win);

	/* return last character pressed */
	switch(ch) {
	case KEY_ESC:
	case KEY_LEFT:
	case KEY_RIGHT:
	case KEY_RETURN:
		return(ch);
		/*break;*/
	default:
		break;
	}
	return(NULL);
}
