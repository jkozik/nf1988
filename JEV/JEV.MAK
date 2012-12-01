# Microsoft Visual C++ generated build script - Do not modify

PROJ = JEV
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\NF\JEV\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_AFXDLL" /D "_DEBUG" /FR /GA /GEf /Fd"JEV.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AL /O1 /D "NDEBUG" /D "_AFXDLL" /FR /GA /GEf 
LFLAGS_D_WEXE = /NOLOGO /NOD /NOE /PACKC:61440 /STACK:20480 /ALIGN:16 /ONERROR:NOEXE /CO /LINE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:20480 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mfc250d oldnames libw llibcew commdlg.lib shell.lib 
LIBS_R_WEXE = mfc250 oldnames libw llibcew commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = JEV.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		JEV.SBR \
		MAINFRM.SBR \
		JEVDOC.SBR \
		JEVVIEW.SBR \
		ENV.SBR \
		CHART.SBR \
		ACCT.SBR \
		DESC.SBR \
		GLT.SBR \
		JE.SBR \
		AMT.SBR \
		MMDD.SBR \
		JEDIALOG.SBR \
		CHDIALOG.SBR


JEV_RCDEP = c:\nf\jev\res\jev.ico \
	c:\nf\jev\res\jevdoc.ico \
	c:\nf\jev\res\jev.rc2


STDAFX_DEP = c:\nf\jev\stdafx.h


JEV_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\jev.h \
	c:\nf\jev\env.h \
	c:\nf\jev\chart.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\desc.h \
	c:\nf\jev\mainfrm.h \
	c:\nf\jev\jevdoc.h \
	c:\nf\jev\je.h \
	c:\nf\jev\glt.h \
	c:\nf\jev\mmdd.h \
	c:\nf\jev\amt.h \
	c:\nf\jev\jevview.h


MAINFRM_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\jev.h \
	c:\nf\jev\env.h \
	c:\nf\jev\chart.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\desc.h \
	c:\nf\jev\mainfrm.h


JEVDOC_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\mainfrm.h \
	c:\nf\jev\jev.h \
	c:\nf\jev\env.h \
	c:\nf\jev\chart.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\desc.h \
	c:\nf\jev\jevdoc.h \
	c:\nf\jev\je.h \
	c:\nf\jev\glt.h \
	c:\nf\jev\mmdd.h \
	c:\nf\jev\amt.h


JEVVIEW_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\jev.h \
	c:\nf\jev\env.h \
	c:\nf\jev\chart.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\desc.h \
	c:\nf\jev\mainfrm.h \
	c:\nf\jev\jevdoc.h \
	c:\nf\jev\je.h \
	c:\nf\jev\glt.h \
	c:\nf\jev\mmdd.h \
	c:\nf\jev\amt.h \
	c:\nf\jev\jevview.h \
	c:\nf\jev\jedialog.h \
	c:\nf\jev\chdialog.h


ENV_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\jev.h \
	c:\nf\jev\env.h \
	c:\nf\jev\chart.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\desc.h


CHART_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\chart.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\desc.h


ACCT_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\acct.h


DESC_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\desc.h


GLT_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\glt.h \
	c:\nf\jev\mmdd.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\amt.h \
	c:\nf\jev\desc.h \
	c:\nf\jev\je.h


JE_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\je.h \
	c:\nf\jev\glt.h \
	c:\nf\jev\mmdd.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\amt.h \
	c:\nf\jev\desc.h


AMT_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\amt.h


MMDD_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\mmdd.h


JEDIALOG_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\mainfrm.h \
	c:\nf\jev\jev.h \
	c:\nf\jev\env.h \
	c:\nf\jev\chart.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\desc.h \
	c:\nf\jev\jedialog.h \
	c:\nf\jev\je.h \
	c:\nf\jev\glt.h \
	c:\nf\jev\mmdd.h \
	c:\nf\jev\amt.h \
	c:\nf\jev\chdialog.h \
	c:\nf\jev\jevdoc.h \
	c:\nf\jev\jevview.h


CHDIALOG_DEP = c:\nf\jev\stdafx.h \
	c:\nf\jev\jev.h \
	c:\nf\jev\env.h \
	c:\nf\jev\chart.h \
	c:\nf\jev\acct.h \
	c:\nf\jev\desc.h \
	c:\nf\jev\chdialog.h


all:	$(PROJ).EXE $(PROJ).BSC

JEV.RES:	JEV.RC $(JEV_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r JEV.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

JEV.OBJ:	JEV.CPP $(JEV_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c JEV.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

JEVDOC.OBJ:	JEVDOC.CPP $(JEVDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c JEVDOC.CPP

JEVVIEW.OBJ:	JEVVIEW.CPP $(JEVVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c JEVVIEW.CPP

ENV.OBJ:	ENV.CPP $(ENV_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENV.CPP

CHART.OBJ:	CHART.CPP $(CHART_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CHART.CPP

ACCT.OBJ:	ACCT.CPP $(ACCT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ACCT.CPP

DESC.OBJ:	DESC.CPP $(DESC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DESC.CPP

GLT.OBJ:	GLT.CPP $(GLT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c GLT.CPP

JE.OBJ:	JE.CPP $(JE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c JE.CPP

AMT.OBJ:	AMT.CPP $(AMT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AMT.CPP

MMDD.OBJ:	MMDD.CPP $(MMDD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MMDD.CPP

JEDIALOG.OBJ:	JEDIALOG.CPP $(JEDIALOG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c JEDIALOG.CPP

CHDIALOG.OBJ:	CHDIALOG.CPP $(CHDIALOG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CHDIALOG.CPP


$(PROJ).EXE::	JEV.RES

$(PROJ).EXE::	STDAFX.OBJ JEV.OBJ MAINFRM.OBJ JEVDOC.OBJ JEVVIEW.OBJ ENV.OBJ CHART.OBJ \
	ACCT.OBJ DESC.OBJ GLT.OBJ JE.OBJ AMT.OBJ MMDD.OBJ JEDIALOG.OBJ CHDIALOG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
JEV.OBJ +
MAINFRM.OBJ +
JEVDOC.OBJ +
JEVVIEW.OBJ +
ENV.OBJ +
CHART.OBJ +
ACCT.OBJ +
DESC.OBJ +
GLT.OBJ +
JE.OBJ +
AMT.OBJ +
MMDD.OBJ +
JEDIALOG.OBJ +
CHDIALOG.OBJ +
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
	$(RC) $(RESFLAGS) JEV.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	JEV.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) JEV.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
