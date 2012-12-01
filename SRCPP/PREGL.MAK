ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = PREGL
PROJFILE = PREGL.MAK
DEBUG = 1

BRFLAGS  =  /o $(PROJ).bsc
BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
BROWSE	= 1
CC  = cl
CFLAGS_G  = /W2 /BATCH /FR$*.sbr /Zn
CFLAGS_D  = /f /Zi /Od
CFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W2 /D_DOS /BATCH /FR$*.sbr /Zn
CXXFLAGS_D  = /f /Od /Zi /D_DEBUG
CXXFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
LLIBS_R  = MAFXCR
LLIBS_D  = MAFXCRD

FILES  = JEPREGL.C JEGLSORT.C GLENV.C CHVALID.C JEVALINP.C CHART.H CHART.CPP
OBJS  = JEPREGL.obj JEGLSORT.obj GLENV.obj CHVALID.obj JEVALINP.obj CHART.obj
SBRS  = JEPREGL.sbr JEGLSORT.sbr GLENV.sbr CHVALID.sbr JEVALINP.sbr CHART.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .c .cpp

JEPREGL.obj : JEPREGL.C GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoJEPREGL.obj JEPREGL.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoJEPREGL.obj JEPREGL.C
<<
!ENDIF

JEPREGL.sbr : JEPREGL.C GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRJEPREGL.sbr JEPREGL.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRJEPREGL.sbr JEPREGL.C
<<
!ENDIF

JEGLSORT.obj : JEGLSORT.C GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoJEGLSORT.obj JEGLSORT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoJEGLSORT.obj JEGLSORT.C
<<
!ENDIF

JEGLSORT.sbr : JEGLSORT.C GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRJEGLSORT.sbr JEGLSORT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRJEGLSORT.sbr JEGLSORT.C
<<
!ENDIF

GLENV.obj : GLENV.C GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoGLENV.obj GLENV.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoGLENV.obj GLENV.C
<<
!ENDIF

GLENV.sbr : GLENV.C GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRGLENV.sbr GLENV.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRGLENV.sbr GLENV.C
<<
!ENDIF

CHVALID.obj : CHVALID.C GLextern.h GLdefs.h GLstruct.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoCHVALID.obj CHVALID.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoCHVALID.obj CHVALID.C
<<
!ENDIF

CHVALID.sbr : CHVALID.C GLextern.h GLdefs.h GLstruct.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRCHVALID.sbr CHVALID.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRCHVALID.sbr CHVALID.C
<<
!ENDIF

JEVALINP.obj : JEVALINP.C GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoJEVALINP.obj JEVALINP.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoJEVALINP.obj JEVALINP.C
<<
!ENDIF

JEVALINP.sbr : JEVALINP.C GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRJEVALINP.sbr JEVALINP.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRJEVALINP.sbr JEVALINP.C
<<
!ENDIF

CHART.obj : CHART.CPP CHART.H
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCHART.obj CHART.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCHART.obj CHART.CPP
<<
!ENDIF

CHART.sbr : CHART.CPP CHART.H
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCHART.sbr CHART.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCHART.sbr CHART.CPP
<<
!ENDIF


$(PROJ).bsc : $(SBRS)
	$(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(OBJS)
	-$(NMAKEBSC1) MAKEFLAGS=
	-$(NMAKEBSC2) $(NMFLAGS) -f $(PROJFILE) $(PROJ).bsc
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
	$(LINKER) @$(PROJ).lrf


.c.sbr :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FR$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FR$@ $<
<<
!ENDIF

.cpp.sbr :
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FR$@ $<
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FR$@ $<
<<
!ENDIF

.c.obj :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo$@ $<
<<
!ENDIF

.cpp.obj :
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /Fo$@ $<
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /Fo$@ $<
<<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
