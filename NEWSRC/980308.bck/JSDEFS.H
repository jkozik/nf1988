#define KEY_NL '\n'
#define KEY_ESC '\033'
#define SZIDX SZDESC
#define MAXCAR 400
#define MAXJEFILE 235
#define MAXYANK 20
#define MAXUNDO 20
#define CTRL(x) (x & 0x1f)
#define MAXACCTS 15
#define SZDAY 2
#define SZAMTFLD 11
#define KEY_RETURN '\r'
#define JMERROR(text) sprintf(prtstr,"Record-%d, %s ERROR:\n%s\n",rec_cnt,text,line);inperrcnt++;JMprtbody(prtstr);
