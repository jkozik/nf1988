# Microsoft Visual C++ generated build script - Do not modify

PROJ = CLOSE
DEBUG = 1
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = f:\NF\SRC\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = GLCLOSE.C   
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /D "_DOS" /FR /Fd"CLOSE.PDB"
CFLAGS_R_DEXE = /nologo /Gs /G2 /W3 /AM /Ox /D "NDEBUG" /D "_DOS" /FR 
LFLAGS_D_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /CO /STACK:5120
LFLAGS_R_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /STACK:5120
LIBS_D_DEXE = oldnames llibce
LIBS_R_DEXE = oldnames mlibce
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE)
LFLAGS = $(LFLAGS_D_DEXE)
LIBS = $(LIBS_D_DEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_DEXE)
LFLAGS = $(LFLAGS_R_DEXE)
LIBS = $(LIBS_R_DEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = GLCLOSE.SBR \
		CHVALID.SBR \
		GLJEFILE.SBR \
		GLENV.SBR


GLCLOSE_DEP = f:\nf\src\gldefs.h \
	f:\nf\src\glstruct.h \
	f:\nf\src\glextern.h


CHVALID_DEP = f:\nf\src\glextern.h \
	f:\nf\src\gldefs.h \
	f:\nf\src\glstruct.h


GLJEFILE_DEP = f:\nf\src\glextern.h \
	f:\nf\src\gldefs.h \
	f:\nf\src\glstruct.h


GLENV_DEP = f:\nf\src\gldefs.h \
	f:\nf\src\glstruct.h \
	f:\nf\src\glextern.h


all:	$(PROJ).EXE $(PROJ).BSC

GLCLOSE.OBJ:	GLCLOSE.C $(GLCLOSE_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c GLCLOSE.C

CHVALID.OBJ:	CHVALID.C $(CHVALID_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c CHVALID.C

GLJEFILE.OBJ:	GLJEFILE.C $(GLJEFILE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GLJEFILE.C

GLENV.OBJ:	GLENV.C $(GLENV_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GLENV.C

$(PROJ).EXE::	GLCLOSE.OBJ CHVALID.OBJ GLJEFILE.OBJ GLENV.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
GLCLOSE.OBJ +
CHVALID.OBJ +
GLJEFILE.OBJ +
GLENV.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\lang\msvc\lib\+
d:\lang\msvc\mfc\lib\+
f:\lib\curses\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
