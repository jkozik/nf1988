ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = GLRPT
PROJFILE = GLRPT.MAK
DEBUG = 1

NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W2 /BATCH /FR$*.sbr
CFLAGS_D  = /f /Zi /Od
CFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
CXX  = cl
CXXFLAGS_G  = /W2 /BATCH /FR$*.sbr
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
BROWSE	= 1
PACK_SBRS  = 1

FILES  = GLRPT.C CHVALID.C GLENV.C GLJEFILE.C
OBJS  = GLRPT.obj CHVALID.obj GLENV.obj GLJEFILE.obj
SBRS  = GLRPT.sbr CHVALID.sbr GLENV.sbr GLJEFILE.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .sbr .c

GLRPT.obj : GLRPT.C e:\lang\c700\include\stdio.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\search.h\
	e:\lang\c700\include\direct.h e:\lang\c700\include\sys\types.h\
	e:\lang\c700\include\stdlib.h e:\lang\c700\include\time.h\
	e:\lang\c700\include\sys\stat.h GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoGLRPT.obj GLRPT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoGLRPT.obj GLRPT.C
<<
!ENDIF

GLRPT.sbr : GLRPT.C e:\lang\c700\include\stdio.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\search.h\
	e:\lang\c700\include\direct.h e:\lang\c700\include\sys\types.h\
	e:\lang\c700\include\stdlib.h e:\lang\c700\include\time.h\
	e:\lang\c700\include\sys\stat.h GLdefs.h GLstruct.h GLextern.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRGLRPT.sbr GLRPT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRGLRPT.sbr GLRPT.C
<<
!ENDIF

CHVALID.obj : CHVALID.C e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\search.h e:\lang\c700\include\direct.h\
	e:\lang\c700\include\stdlib.h GLextern.h GLdefs.h GLstruct.h
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

CHVALID.sbr : CHVALID.C e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\search.h e:\lang\c700\include\direct.h\
	e:\lang\c700\include\stdlib.h GLextern.h GLdefs.h GLstruct.h
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

GLENV.obj : GLENV.C e:\lang\c700\include\signal.h e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\direct.h e:\lang\c700\include\sys\types.h\
	e:\lang\c700\include\stdlib.h e:\lang\c700\include\sys\stat.h\
	e:\lang\c700\include\io.h e:\lang\c700\include\errno.h GLdefs.h\
	GLstruct.h GLextern.h
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

GLENV.sbr : GLENV.C e:\lang\c700\include\signal.h e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\direct.h e:\lang\c700\include\sys\types.h\
	e:\lang\c700\include\stdlib.h e:\lang\c700\include\sys\stat.h\
	e:\lang\c700\include\io.h e:\lang\c700\include\errno.h GLdefs.h\
	GLstruct.h GLextern.h
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

GLJEFILE.obj : GLJEFILE.C e:\lang\c700\include\direct.h\
	e:\lang\c700\include\stdio.h e:\lang\c700\include\ctype.h\
	e:\lang\c700\include\string.h e:\lang\c700\include\stdlib.h GLextern.h\
	GLdefs.h GLstruct.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoGLJEFILE.obj GLJEFILE.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoGLJEFILE.obj GLJEFILE.C
<<
!ENDIF

GLJEFILE.sbr : GLJEFILE.C e:\lang\c700\include\direct.h\
	e:\lang\c700\include\stdio.h e:\lang\c700\include\ctype.h\
	e:\lang\c700\include\string.h e:\lang\c700\include\stdlib.h GLextern.h\
	GLdefs.h GLstruct.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRGLJEFILE.sbr GLJEFILE.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRGLJEFILE.sbr GLJEFILE.C
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
