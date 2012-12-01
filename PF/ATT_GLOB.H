/* att_glob.h --  contains default definitions and declarations of logical
		  attribute tables for use in Windows for C.  Nests in
		  wfc_glob.h.  The #defines for logical attributes are in
		  def_att.h, which is nested in wfc.h

    ************* Copyright 1985 by Vermont Creative Software **************

VERSION: v4.14
DATE:	 22-May-87

IMPLEMENTING LOGICAL OR PHYSICAL ATTRIBUTES

    Logical attributes will be implemented if ATT_LOGIC is defined.  This is the
    default condition set in wfc.h.

    To use physical attributes, #undef ATT_LOGIC here or in an include file
    that precedes this one.  Alternatively, the #define ATT_LOGIC statement in
    wfc.h could be commented out.  Generally, the include file for a specific
    application would set ATT_LOGIC.

THE LOGICAL-ATTRIBUTE TABLE

    The physical attributes associated with each logical attribute are specified
    in a logical-attribute table (two dimensional array), datt_tbl[][].  There
    is a row for each logical attribute; the number of rows in the table equals
    LATTQ.  The number of columns equals PATTQ, the number of physical
    attributes for each logical attribute.  LATTQ and PATTQ are #defined in
    def_att.h

    The system, as supplied has two physical attributes for each logical
    attribute:	a monochrome attribute, and a color attribute; thus PATTQ is set
    to two in att_def.h.  You can add more physical attributes by increasing the
    value of PATTQ and adding more columns to the logical attribute table.
*/

#ifdef ATT_LOGIC			/*LOGICAL ATTRIBUTES in use	      */
int _lattsw = 1;
char latt[LATTQ];			/*array of logical attributes	      */

char  datt_tbl [LATTQ] [PATTQ] =
{
   {NORMAL,		       c_att(WHITE, BLACK)},		   /*LDOS     */
   {NORMAL,		       c_att(WHITE, BLUE)},		   /*LNORMAL  */
   {REVERSE,		       c_att(BLUE, WHITE)},		   /*LREVERSE */
   {NORMAL + HIGH_INT,	       c_att(WHITE + LIGHT, BLUE)},	   /*LHIGHLITE*/
   {NORMAL + HIGH_INT + BLINK, c_att(RED + BLINK, BLACK)},	   /*LURGENT  */
   {NORMAL + HIGH_INT,	       c_att(BLUE, WHITE)},		   /*LHELP    */
   {REVERSE,		       c_att(RED, BLACK)},		   /*LERROR   */
   {NORMAL + HIGH_INT,	       c_att(WHITE + LIGHT, BLUE)},	   /*LMESSAGE */
   {NORMAL + HIGH_INT,	       c_att(CYAN, BLUE)},		   /*LFIELDI  */
   {REVERSE,		       c_att(BLACK, CYAN)},		   /*LFIELDA  */
   {NORMAL + HIGH_INT,	       c_att(BLACK, GREEN)},		   /*LCHOICEI */
   {REVERSE,		       c_att(GREEN, BLACK)},		   /*LCHOICEA */
   {REVERSE,		       c_att(BLUE, WHITE)},		   /*LMARK    */
   {0,			       c_att(BLUE, BLUE)},		   /*LNODISPLA*/
   {REVERSE,		       c_att(BLACK, BLUE)},		   /*LBLACK   */
   {REVERSE,		       c_att(BLUE, WHITE)},		   /*LBLUE    */
   {NORMAL,		       c_att(GREEN, BLUE)},		   /*LGREEN   */
   {NORMAL,		       c_att(CYAN, BLUE)},		   /*LCYAN    */
   {REVERSE,		       c_att(RED, BLUE)},		   /*LRED     */
   {REVERSE,		       c_att(MAGENTA, BLUE)},		   /*LMAGENTA */
   {NORMAL,		       c_att(BROWN, BLUE)},		   /*LBROWN   */
   {NORMAL,		       c_att(WHITE, BLUE)},		   /*LWHITE   */
   {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},			   /*RESERVED */
   {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},			   /*RESERVED */
   {NORMAL,		       c_att(WHITE, RED)}, 		   /*LDIALOG  */
   {NORMAL,		       c_att(BLACK, CYAN)}, 		   /*LTABLE   */
   {NORMAL,		       c_att(YELLOW, RED)} 		   /*LTABLITE */

};
int _attrowq = LATTQ;			/*number of rows in attribute table   */

#else					/*PHYSICAL ATTRIBUTES in use	      */

int _lattsw = 0;
char latt[1];				/*array of logical attributes	      */
char datt_tbl [1][PATTQ];
int _attrowq = 1;

#endif

int _attcolq = PATTQ;			/*number of columns in attribute table*/
