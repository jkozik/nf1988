# Microsoft Visual C++ generated build script - Do not modify

PROJ = PREGL
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
FIRSTC = CHVALID.C   
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /D "_DOS" /FR /Fd"PREGL.PDB"
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
SBRS = CHVALID.SBR \
		GLENV.SBR \
		JEGLSORT.SBR \
		JEPREGL.SBR \
		JEVALINP.SBR


CHVALID_DEP = c:\nf\src\glextern.h \
	c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h


GLENV_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


JEGLSORT_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


JEPREGL_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


JEVALINP_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


all:	$(PROJ).EXE $(PROJ).BSC

CHVALID.OBJ:	CHVALID.C $(CHVALID_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c CHVALID.C

GLENV.OBJ:	GLENV.C $(GLENV_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GLENV.C

JEGLSORT.OBJ:	JEGLSORT.C $(JEGLSORT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JEGLSORT.C

JEPREGL.OBJ:	JEPREGL.C $(JEPREGL_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JEPREGL.C

JEVALINP.OBJ:	JEVALINP.C $(JEVALINP_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JEVALINP.C

$(PROJ).EXE::	CHVALID.OBJ GLENV.OBJ JEGLSORT.OBJ JEPREGL.OBJ JEVALINP.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
CHVALID.OBJ +
GLENV.OBJ +
JEGLSORT.OBJ +
JEPREGL.OBJ +
JEVALINP.OBJ +
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
