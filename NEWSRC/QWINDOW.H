/* ------------------- qwindow.h ----------------------- */

/*      Uncomment this for stacked windows 
 *      rather than layered windows.
 *
   #define FASTWINDOWS
 *
 */

/* ------ window colors ---------- */
#define RED   4
#define GREEN 2
#define BLUE  1
#define WHITE (RED+GREEN+BLUE)
#define YELLOW (RED+GREEN)
#define AQUA (GREEN+BLUE)
#define MAGENTA (RED+BLUE)
#define BLACK 0
#define BRIGHT 8
#define DIM 0

#define BORDER 0
#define TITLE 1
#define ACCENT 2
#define NORMAL 3
#define ALL 4

#define TRUE 1
#define FALSE 0
#define QERROR -1
#define QOK 0

/* ------------- window controller structures ----------- */
typedef struct field {		/* data entry field description*/
	char *fmask;			/* field data entry mask	   */
	int fprot;				/* field protection			   */
	char *fbuff;			/* field buffer				   */
	int ftype;				/* field type				   */
	int frow;				/* field row				   */
	int fcol;				/* field column				   */
	void (*fhelp)(char *);	/* field help function		   */
	char *fhwin;			/* field help window		   */
	int flx, fly;			/* help window location		   */
	int (*fvalid)(char *);	/* field validation function   */
	struct field *fnxt;		/* next field on template 	   */
	struct field *fprv;		/* previous field on template  */
} FIELD;
typedef struct _wnd {
	int _wv;		  /* true if window is visible     */
	int _hd;		  /* true if window was hidden     */
	char *_ws;		  /* points to window save block   */
	char *_tl;		  /* points to window title		   */
	int _wx;		  /* nw x coordinate			   */
	int _wy;		  /* nw y coordinate			   */
	int _ww;		  /* window width				   */
	int _wh;		  /* window height			       */
	int _wsp;		  /* scroll pointer			       */
	int _sp;		  /* selection pointer		       */
	int _cr;		  /* cursor x location		       */
	int btype;		  /* border type				   */
	int wcolor[4];	  /* colors for window 			   */
	int _pn;		  /* previous normal color		   */
	struct _wnd *_nx; /* points to next window         */
	struct _wnd *_pv; /* points to previous window     */
	FIELD *_fh;		  /* points to 1st data entry fld  */	
	FIELD *_ft;		  /* points to last data entry fld */	
} QWINDOW;
typedef struct w_menu {
	char *mname;
	char **mselcs;
	void (**func)(int, int);
} MENU;

#define SAV 	(wnd->_ws)
#define WTITLE  (wnd->_tl)
#define COL 	(wnd->_wx)
#define ROW 	(wnd->_wy)
#define WIDTH 	(wnd->_ww)
#define HEIGHT 	(wnd->_wh)
#define SCROLL  (wnd->_wsp)
#define SELECT  (wnd->_sp)
#define WCURS   (wnd->_cr)
#define WBORDER	(wnd->wcolor[BORDER])
#define WTITLEC	(wnd->wcolor[TITLE])
#define WACCENT	(wnd->wcolor[ACCENT])
#define WNORMAL	(wnd->wcolor[NORMAL])
#define PNORMAL (wnd->_pn)
#define BTYPE	(wnd->btype)
#define NEXT    (wnd->_nx)
#define PREV    (wnd->_pv)
#define WCOLOR  (wnd->wcolor)
#define VISIBLE (wnd->_wv)
#define HIDDEN  (wnd->_hd)
#define FHEAD	(wnd->_fh)
#define FTAIL   (wnd->_ft)

#define NW   	(wcs[wnd->btype].nw)
#define NE   	(wcs[wnd->btype].ne)
#define SE   	(wcs[wnd->btype].se)
#define SW   	(wcs[wnd->btype].sw)
#define SIDE 	(wcs[wnd->btype].side)
#define LINE 	(wcs[wnd->btype].line)

/* ------ general-purpose functions and macros ----- */
void clear_screen(void);
int vmode(void);
unsigned video_address(void);
void cursor(int, int);
void curr_cursor(int *, int *);
int cursor_type(void);
void set_cursor_type(int);
int get_char(void);
int scroll_lock(void);
char far *getdta(void);
void setdta(char far *);
unsigned peek(unsigned, unsigned);
char peekb(unsigned, unsigned);
void poke(unsigned, unsigned, unsigned);
void vpoke(unsigned, unsigned, unsigned);
int vpeek(unsigned, unsigned);

/* ----- window functions and macros ------- */
QWINDOW *establish_window(int, int, int, int);
void set_border(QWINDOW *, int);
void set_colors(QWINDOW *, int, int, int, int);
void set_intensity(QWINDOW *, int);
void set_title(QWINDOW *, char *);
void display_window(QWINDOW *);
void delete_window(QWINDOW *);
void clear_window(QWINDOW *);
void hide_window(QWINDOW *);
void wprintf(QWINDOW *, char *, ...);
void wputchar(QWINDOW *, int);
void close_all(void);
void wcursor(QWINDOW *, int, int);
void error_message(char *);
void clear_message(void);
int get_selection(QWINDOW *, int, char *);
#define reverse_video(wnd) wnd->wcolor[3]=wnd->wcolor[2]
#define normal_video(wnd) wnd->wcolor[3]=wnd->_pn
#define rmove_window(wnd,x,y) repos_wnd(wnd, x, y, 0)
#define move_window(wnd,x,y) repos_wnd(wnd, COL-x, ROW-y, 0)
#define forefront(wnd) repos_wnd(wnd, 0, 0, 1)
#define rear_window(wnd) repos_wnd(wnd, 0, 0, -1)

/* ----- internal to window processes ----- */
void qscroll(QWINDOW *, int);
void repos_wnd(QWINDOW *, int, int, int);
void acline(QWINDOW *, int);
#define accent(wnd)	acline(wnd, WACCENT)
#define deaccent(wnd) acline(wnd, WNORMAL)
#define clr(bg,fg,in) ((fg)|(bg<<4)|(in))
#define vad(x,y) ((y)*160+(x)*2)
/* ------ editor function ------- */
void text_editor(QWINDOW *, char *, unsigned);
/* -------- menu function ------- */
void menu_select(char *name, MENU *mn);
/* ----- help functions ------- */
void load_help(char *);
void set_help(char *, int, int);
/* ----- data entry functions ---- */
void init_template(QWINDOW *);
FIELD *establish_field(QWINDOW *,int,int,char *,char *,int);
void clear_template(QWINDOW *);
void field_tally(QWINDOW *);
int data_entry(QWINDOW *);
void wprompt(QWINDOW *, int, int, char *);
void error_message(char *);
void clear_notice(void);
void field_window(FIELD *, char *, int, int);
#define field_protect(f,s)  f->fprot=s
#define field_help(f,h)     f->fhelp=h
#define field_validate(f,v) f->fvalid=v

#ifdef MSC50
#define MF(sg,of) \
  ((void far *)(((unsigned long)(sg)<<16)|(unsigned)(of)))
#define poke(sg,of,wd) (*((int far*)MF((sg),(of)))=(int)(wd))
#define peek(sg,of)    (*((int far*)MF((sg),(of))))
#define peekb(sg,of)   (*((char far*)MF((sg),(of))))
#endif

#ifdef NOCGA
#define vpoke(sg,of,ch) poke(sg,of,ch)
#define vpeek(sg,of) peek(sg,of)
#endif

/* ------- tsr prototypes ---------- */
void resinit(void);
int resident(char *);
void terminate(void);
void restart(void);
void suspend(void);
int get_char(void);
void popup(void);



