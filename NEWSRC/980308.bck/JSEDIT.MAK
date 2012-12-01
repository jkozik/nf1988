# Microsoft Visual C++ generated build script - Do not modify

PROJ = JSEDIT
DEBUG = 1
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\NF\NEWSRC\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = JSEDIT.C    
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /G2 /W3 /Zi /AL /Gt256 /Od /D "_DEBUG" /D "_DOS" /FR /Fd"JSEDIT.PDB"
CFLAGS_R_DEXE = /nologo /Gs /G2 /W3 /AM /Ox /D "NDEBUG" /D "_DOS" /FR 
LFLAGS_D_DEXE = /NOLOGO /NOI /STACK:5120 /SEG:196 /ONERROR:NOEXE /CO 
LFLAGS_R_DEXE = /NOLOGO /NOI /STACK:5120 /ONERROR:NOEXE 
LIBS_D_DEXE = oldnames llibce mlcurses qcprogs 
LIBS_R_DEXE = oldnames mlibce 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = ..\..\LIB\CURSES\MLCURSES.LIB 
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
SBRS = JSEDIT.SBR \
		CHVALID.SBR \
		GDREPORT.SBR \
		GLENV.SBR \
		GLJEFILE.SBR \
		JEGLSORT.SBR \
		JEVALINP.SBR \
		JMAARPT.SBR \
		JMACCTFL.SBR \
		JMANALDT.SBR \
		JMEDIT.SBR \
		JMFILE.SBR \
		JMFLD.SBR \
		JMGLRPT.SBR \
		JMLNEDIT.SBR \
		JMPREGL.SBR \
		JMREPORT.SBR \
		JMYANK.SBR


MLCURSES_DEP = 

JSEDIT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


CHVALID_DEP = c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h


GDREPORT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


GLENV_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


GLJEFILE_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JEGLSORT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JEVALINP_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMAARPT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMACCTFL_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMANALDT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMEDIT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\keys.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMFILE_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMFLD_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMGLRPT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMLNEDIT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMPREGL_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMREPORT_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\qwindow.h \
	c:\nf\newsrc\keys.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


JMYANK_DEP = c:\lib\curses\curses.h \
	c:\nf\newsrc\gldefs.h \
	c:\nf\newsrc\glstruct.h \
	c:\nf\newsrc\glextern.h \
	c:\nf\newsrc\jsdefs.h \
	c:\nf\newsrc\jsstruct.h \
	c:\nf\newsrc\jsextern.h


all:	$(PROJ).EXE $(PROJ).BSC

JSEDIT.OBJ:	JSEDIT.C $(JSEDIT_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c JSEDIT.C

CHVALID.OBJ:	CHVALID.C $(CHVALID_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c CHVALID.C

GDREPORT.OBJ:	GDREPORT.C $(GDREPORT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GDREPORT.C

GLENV.OBJ:	GLENV.C $(GLENV_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GLENV.C

GLJEFILE.OBJ:	GLJEFILE.C $(GLJEFILE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GLJEFILE.C

JEGLSORT.OBJ:	JEGLSORT.C $(JEGLSORT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JEGLSORT.C

JEVALINP.OBJ:	JEVALINP.C $(JEVALINP_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JEVALINP.C

JMAARPT.OBJ:	JMAARPT.C $(JMAARPT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMAARPT.C

JMACCTFL.OBJ:	JMACCTFL.C $(JMACCTFL_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMACCTFL.C

JMANALDT.OBJ:	JMANALDT.C $(JMANALDT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMANALDT.C

JMEDIT.OBJ:	JMEDIT.C $(JMEDIT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMEDIT.C

JMFILE.OBJ:	JMFILE.C $(JMFILE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMFILE.C

JMFLD.OBJ:	JMFLD.C $(JMFLD_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMFLD.C

JMGLRPT.OBJ:	JMGLRPT.C $(JMGLRPT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMGLRPT.C

JMLNEDIT.OBJ:	JMLNEDIT.C $(JMLNEDIT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMLNEDIT.C

JMPREGL.OBJ:	JMPREGL.C $(JMPREGL_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMPREGL.C

JMREPORT.OBJ:	JMREPORT.C $(JMREPORT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMREPORT.C

JMYANK.OBJ:	JMYANK.C $(JMYANK_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JMYANK.C

$(PROJ).EXE::	JSEDIT.OBJ CHVALID.OBJ GDREPORT.OBJ GLENV.OBJ GLJEFILE.OBJ JEGLSORT.OBJ \
	JEVALINP.OBJ JMAARPT.OBJ JMACCTFL.OBJ JMANALDT.OBJ JMEDIT.OBJ JMFILE.OBJ JMFLD.OBJ \
	JMGLRPT.OBJ JMLNEDIT.OBJ JMPREGL.OBJ JMREPORT.OBJ JMYANK.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
JSEDIT.OBJ +
CHVALID.OBJ +
GDREPORT.OBJ +
GLENV.OBJ +
GLJEFILE.OBJ +
JEGLSORT.OBJ +
JEVALINP.OBJ +
JMAARPT.OBJ +
JMACCTFL.OBJ +
JMANALDT.OBJ +
JMEDIT.OBJ +
JMFILE.OBJ +
JMFLD.OBJ +
JMGLRPT.OBJ +
JMLNEDIT.OBJ +
JMPREGL.OBJ +
JMREPORT.OBJ +
JMYANK.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
..\..\LIB\CURSES\MLCURSES.LIB+
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
