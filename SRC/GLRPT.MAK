# Microsoft Visual C++ generated build script - Do not modify

PROJ = GLRPT
DEBUG = 1
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\NF\SRC\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = GLRPT.C     
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /D "_DOS" /FR /Fd"GLRPT.PDB"
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
SBRS = GLRPT.SBR \
		CHVALID.SBR \
		GLENV.SBR \
		GLJEFILE.SBR


GLRPT_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


CHVALID_DEP = c:\nf\src\glextern.h \
	c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h


GLENV_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


GLJEFILE_DEP = c:\nf\src\glextern.h \
	c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h


all:	$(PROJ).EXE $(PROJ).BSC

GLRPT.OBJ:	GLRPT.C $(GLRPT_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c GLRPT.C

CHVALID.OBJ:	CHVALID.C $(CHVALID_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c CHVALID.C

GLENV.OBJ:	GLENV.C $(GLENV_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GLENV.C

GLJEFILE.OBJ:	GLJEFILE.C $(GLJEFILE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GLJEFILE.C

$(PROJ).EXE::	GLRPT.OBJ CHVALID.OBJ GLENV.OBJ GLJEFILE.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
GLRPT.OBJ +
CHVALID.OBJ +
GLENV.OBJ +
GLJEFILE.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\lang\msvc\lib\+
d:\lang\msvc\mfc\lib\+
c:\lib\curses\+
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
