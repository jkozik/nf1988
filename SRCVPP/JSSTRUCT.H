typedef enum {
	start,
	file,
	edit,
	quit
} menu;

extern menu state;

struct JSfilerec {
	char line[SZLINE+1];
	struct JSfilerec *next;
	struct JSfilerec *prev;
};
extern struct JSfilerec JSfiletab[MAXJEFILE];

extern struct JSfilerec *JShead,*JStail;
