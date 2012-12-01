# Microsoft Visual C++ generated build script - Do not modify

PROJ = ANALDTL
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
FIRSTC = JEANALDT.C  
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /D "_DOS" /FR /Fd"ANALDTL.PDB"
CFLAGS_R_DEXE = /nologo /Gs /G2 /W3 /AM /Ox /D "NDEBUG" /D "_DOS" /FR 
LFLAGS_D_DEXE = /NOLOGO /NOI /STACK:5120 /ONERROR:NOEXE /CO 
LFLAGS_R_DEXE = /NOLOGO /NOI /STACK:5120 /ONERROR:NOEXE 
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
SBRS = JEANALDT.SBR \
		CHVALID.SBR \
		GLENV.SBR \
		JEVALINP.SBR


JEANALDT_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


CHVALID_DEP = c:\nf\src\glextern.h \
	c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h


GLENV_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


JEVALINP_DEP = c:\nf\src\gldefs.h \
	c:\nf\src\glstruct.h \
	c:\nf\src\glextern.h


all:	$(PROJ).EXE $(PROJ).BSC

JEANALDT.OBJ:	JEANALDT.C $(JEANALDT_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c JEANALDT.C

CHVALID.OBJ:	CHVALID.C $(CHVALID_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c CHVALID.C

GLENV.OBJ:	GLENV.C $(GLENV_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GLENV.C

JEVALINP.OBJ:	JEVALINP.C $(JEVALINP_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JEVALINP.C

$(PROJ).EXE::	JEANALDT.OBJ CHVALID.OBJ GLENV.OBJ JEVALINP.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
JEANALDT.OBJ +
CHVALID.OBJ +
GLENV.OBJ +
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
