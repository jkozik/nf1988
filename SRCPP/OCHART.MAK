ORIGIN = PWB
ORIGIN_VER = 2.1.49
PROJ = chart
PROJFILE = chart.mak
DEBUG = 1

CC  = cl
CFLAGS_G  = /W2 /BATCH
CFLAGS_D  = /f /Zi /Od
CFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
CXX  = cl
CXXFLAGS_G  = /AL /W4 /D_DOS /BATCH
CXXFLAGS_D  = /f /Od /Zi /D_DEBUG
CXXFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi /Gs
MAPFILE_D  = $(PROJ).map
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /STACK:4096 /BATCH /ONERROR:NOEXE /cp:10000
LFLAGS_D  = /CO /MAP:FULL /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
LLIBS_R  = LAFXCR
LLIBS_D  = LAFXCRD

FILES  = CHART.CPP ACCT.CPP DESC.CPP MMDD.CPP AMT.CPP GLT.CPP je.cpp\
	CLSTEST.CPP env.cpp
OBJS  = CHART.obj ACCT.obj DESC.obj MMDD.obj AMT.obj GLT.obj je.obj\
	CLSTEST.obj env.obj

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .cpp

CHART.obj : CHART.CPP chart.h e:\lang\c700\include\ctype.h\
	e:\lang\c700\include\iostream.h e:\lang\c700\include\iomanip.h acct.h\
	desc.h
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

ACCT.obj : ACCT.CPP acct.h e:\lang\c700\include\ctype.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoACCT.obj ACCT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoACCT.obj ACCT.CPP
<<
!ENDIF

DESC.obj : DESC.CPP desc.h e:\lang\c700\include\ctype.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoDESC.obj DESC.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoDESC.obj DESC.CPP
<<
!ENDIF

MMDD.obj : MMDD.CPP mmdd.h e:\lang\c700\include\ctype.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMMDD.obj MMDD.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMMDD.obj MMDD.CPP
<<
!ENDIF

AMT.obj : AMT.CPP amt.h e:\lang\c700\include\ctype.h\
	e:\lang\c700\include\stdlib.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoAMT.obj AMT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoAMT.obj AMT.CPP
<<
!ENDIF

GLT.obj : GLT.CPP glt.h je.h e:\lang\c700\include\stdlib.h\
	e:\lang\c700\include\iostream.h e:\lang\c700\include\iomanip.h\
	e:\lang\c700\include\direct.h e:\lang\c700\include\search.h mmdd.h\
	acct.h amt.h desc.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoGLT.obj GLT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoGLT.obj GLT.CPP
<<
!ENDIF

je.obj : je.cpp je.h e:\lang\c700\include\stdlib.h\
	e:\lang\c700\include\iostream.h e:\lang\c700\include\malloc.h glt.h\
	mmdd.h acct.h amt.h desc.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /Foje.obj je.cpp
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /Foje.obj je.cpp
<<
!ENDIF

CLSTEST.obj : CLSTEST.CPP chart.h je.h acct.h desc.h glt.h mmdd.h amt.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCLSTEST.obj CLSTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCLSTEST.obj CLSTEST.CPP
<<
!ENDIF

env.obj : env.cpp env.h e:\lang\c700\include\direct.h\
	e:\lang\c700\include\stdlib.h e:\lang\c700\include\signal.h\
	e:\lang\c700\include\iostream.h e:\lang\c700\include\io.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /Foenv.obj env.cpp
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /Foenv.obj env.cpp
<<
!ENDIF


$(PROJ).exe : $(OBJS)
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
