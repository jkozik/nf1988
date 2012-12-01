ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = ANALDTL
PROJFILE = ANALDTL.MAK
DEBUG = 1

CC  = cl
CFLAGS_G  = /W2 /BATCH /FR$*.sbr /Zn
CFLAGS_D  = /f /Zi /Od
CFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
CXX  = cl
CXXFLAGS_G  = /W2 /BATCH /FR$*.sbr /Zn
CXXFLAGS_D  = /f /Zi /Od
CXXFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
BRFLAGS  =  /o $(PROJ).bsc
BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
BROWSE	= 1
PACK_SBRS  = 0

FILES  = JEANALDT.C CHVALID.C GLENV.C JEVALINP.C
OBJS  = JEANALDT.obj CHVALID.obj GLENV.obj JEVALINP.obj
SBRS  = JEANALDT.sbr CHVALID.sbr GLENV.sbr JEVALINP.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .sbr .c

JEANALDT.obj : JEANALDT.C e:\lang\c700\include\io.h\
	e:\lang\c700\include\errno.h GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoJEANALDT.obj JEANALDT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoJEANALDT.obj JEANALDT.C
<<
!ENDIF

JEANALDT.sbr : JEANALDT.C e:\lang\c700\include\io.h\
	e:\lang\c700\include\errno.h GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRJEANALDT.sbr JEANALDT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRJEANALDT.sbr JEANALDT.C
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

$(PROJ).bsc : $(SBRS)
	$(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<


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


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
