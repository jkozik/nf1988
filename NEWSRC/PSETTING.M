/* ---------- psetting.c ----------- */

#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include "qwindow.h"
#include "keys.h"


int JMlinespage;
char DElinespage[3];

typedef enum {JEFALSE=0, JETRUE=1} jebool;
jebool JMheadon;
char DEheadon[2];


void main(void);
int validate_lines(char *);
int validate_headon(char *);
void main()
{
	WINDOW *wnd;
	FIELD *fld;

	/* initial values */
	JMlinespage=66;
	JMheadon=JETRUE;

	/* unpack variables into strings */
	sprintf(DElinespage,"%2d",JMlinespage);
	if (JMheadon==JETRUE) strcpy(DEheadon,"Y");
	else strcpy(DEheadon,"N");

	wnd = establish_window(10, 5, 6, 30);
	set_title(wnd, " Printer Settings ");
	set_colors(wnd, ALL, BLUE, AQUA, BRIGHT);
	set_colors(wnd, ACCENT, WHITE, BLACK, DIM);
	display_window(wnd);
	wprompt(wnd, 5, 1, "Lines Per Page:");
	wprompt(wnd, 5, 2, "Headings on:");
	init_template(wnd);
	fld = establish_field(wnd, 21, 1, "__", DElinespage, 'N');
	field_validate(fld,validate_lines);
	fld = establish_field(wnd, 21, 2, "_", DEheadon, 'A');
	field_validate(fld,validate_headon);
	while(data_entry(wnd) != ESC) ;
	/*delete_window(wnd); */

	/* pack variables into original data type */
	JMlinespage=atoi(DElinespage);
	if (*DEheadon=='Y') JMheadon=JETRUE;
	else                JMheadon=JEFALSE;
}

int validate_headon(bf)
char *bf;
{
	char sbuf[80];
	if (strcmp(bf,"Y")==0 || strcmp(bf,"N")==0 ) return OK;

	sprintf(sbuf," Y or N ");
	error_message(sbuf);
	return ERROR;
}

int validate_lines(bf)
char *bf;
{
	int i;
	i=atoi(bf);
	if (i >= 10 && i <= 99) {
		return OK;
	} else {
		error_message("Valid Range: 10..99");
		return ERROR;
	}
}
