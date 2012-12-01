# Microsoft Visual C++ generated build script - Do not modify

PROJ = CHART
DEBUG = 1
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\NF\SRCPP\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = ACCT.CPP    
RC = rc
CFLAGS_D_DEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /D "_DOS" /FR /Fd"CHART.PDB"
CFLAGS_R_DEXE = /nologo /Gs /G2 /W3 /AM /Ox /D "NDEBUG" /D "_DOS" /FR 
LFLAGS_D_DEXE = /NOLOGO /NOE /NOI /STACK:5120 /ONERROR:NOEXE /INFO /CO /cp:10000
LFLAGS_R_DEXE = /NOLOGO /NOI /STACK:5120 /ONERROR:NOEXE 
LIBS_D_DEXE = lafxcrd oldnames llibce 
LIBS_R_DEXE = mafxcr oldnames mlibce 
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
SBRS = ACCT.SBR \
		AMT.SBR \
		CHART.SBR \
		CLSTEST.SBR \
		DESC.SBR \
		ENV.SBR \
		GLT.SBR \
		JE.SBR \
		MMDD.SBR


ACCT_DEP = c:\nf\srcpp\acct.h


AMT_DEP = c:\nf\srcpp\amt.h


CHART_DEP = c:\nf\srcpp\chart.h \
	c:\nf\srcpp\acct.h \
	c:\nf\srcpp\desc.h


CLSTEST_DEP = c:\nf\srcpp\chart.h \
	c:\nf\srcpp\acct.h \
	c:\nf\srcpp\desc.h \
	c:\nf\srcpp\je.h \
	c:\nf\srcpp\glt.h \
	c:\nf\srcpp\mmdd.h \
	c:\nf\srcpp\amt.h \
	c:\nf\srcpp\env.h


DESC_DEP = c:\nf\srcpp\desc.h


ENV_DEP = c:\nf\srcpp\env.h


GLT_DEP = c:\nf\srcpp\glt.h \
	c:\nf\srcpp\mmdd.h \
	c:\nf\srcpp\acct.h \
	c:\nf\srcpp\amt.h \
	c:\nf\srcpp\desc.h \
	c:\nf\srcpp\je.h


JE_DEP = c:\nf\srcpp\je.h \
	c:\nf\srcpp\glt.h \
	c:\nf\srcpp\mmdd.h \
	c:\nf\srcpp\acct.h \
	c:\nf\srcpp\amt.h \
	c:\nf\srcpp\desc.h


MMDD_DEP = c:\nf\srcpp\mmdd.h


all:	$(PROJ).EXE $(PROJ).BSC

ACCT.OBJ:	ACCT.CPP $(ACCT_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c ACCT.CPP

AMT.OBJ:	AMT.CPP $(AMT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AMT.CPP

CHART.OBJ:	CHART.CPP $(CHART_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CHART.CPP

CLSTEST.OBJ:	CLSTEST.CPP $(CLSTEST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CLSTEST.CPP

DESC.OBJ:	DESC.CPP $(DESC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DESC.CPP

ENV.OBJ:	ENV.CPP $(ENV_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENV.CPP

GLT.OBJ:	GLT.CPP $(GLT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c GLT.CPP

JE.OBJ:	JE.CPP $(JE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c JE.CPP

MMDD.OBJ:	MMDD.CPP $(MMDD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MMDD.CPP

$(PROJ).EXE::	ACCT.OBJ AMT.OBJ CHART.OBJ CLSTEST.OBJ DESC.OBJ ENV.OBJ GLT.OBJ JE.OBJ \
	MMDD.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
ACCT.OBJ +
AMT.OBJ +
CHART.OBJ +
CLSTEST.OBJ +
DESC.OBJ +
ENV.OBJ +
GLT.OBJ +
JE.OBJ +
MMDD.OBJ +
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
