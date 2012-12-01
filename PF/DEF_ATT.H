/* def_att.h -- contains information on logical attributes; nests in wfc.h
	     The logical attriute table declarations are in att_glob.h

    ************* Copyright 1985 by Vermont Creative Software **************

VERSION: v4.14
DATE:	 22-May-87

*/

/* Logical Attribute Table definitions					      */

#define PATTQ 2 			/*number of phys. atts per logical att*/

#define LATTQ 35			/*number of logical attributes	      */

#define LDOS	    0			/*DOS screen attributes 	      */
#define LNORMAL     1			/*Normal text			      */
#define LREVERSE    2			/*Reverse text			      */
#define LHIGHLITE   3			/*Highlighted text		      */
#define LURGENT     4			/*Attention ! (blink)		      */
#define LHELP	    5			/*Help message			      */
#define LERROR	    6			/*Error message 		      */
#define LMESSAGE    7			/*Borders			      */
#define LFIELDI     8			/*Inactive Field		      */
#define LFIELDA     9			/*Active Field			      */
#define LCHOICEI    10			/*Inactive choice		      */
#define LCHOICEA    11			/*Active choice 		      */
#define LMARK	    12			/*Mark				      */
#define LNODISPLAY  13			/*No display (noecho)		      */
#define LBLACK	    14			/*logical color attribute	      */
#define LBLUE	    15			/*logical color attribute	      */
#define LGREEN	    16			/*logical color attribute	      */
#define LCYAN	    17			/*logical color attribute	      */
#define LRED	    18			/*logical color attribute	      */
#define LMAGENTA    19			/*logical color attribute	      */
#define LBROWN	    20			/*logical color attribute	      */
#define LWHITE	    21			/*logical color attribute	      */
#define LAVR1       22			/*reserved logical attribute	      */
#define LAVR2	    23			/*reserved logical attribute	      */
#define LAVR3	    24			/*reserved logical attribute	      */
#define LAVR4	    25			/*reserved logical attribute	      */
#define LAVR5	    26			/*reserved logical attribute	      */
#define LAVR6	    27			/*reserved logical attribute	      */
#define LAVR7	    28			/*reserved logical attribute	      */
#define LAVR8	    29			/*reserved logical attribute	      */
#define LAVR9	    30			/*reserved logical attribute	      */
#define LAVR10	    31			/*reserved logical attribute	      */
#define LDIALOG     32			/*reserved logical attribute	      */
#define LTABLE      33			/*reserved logical attribute	      */
#define LTABLITE    34			/*reserved logical attribute	      */
