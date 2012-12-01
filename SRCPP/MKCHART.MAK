ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = mkchart
PROJFILE = mkchart.mak
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /BATCH /FR$*.sbr
CFLAGS_D  = /qc /Gi$(PROJ).mdt /Zr /Zi /Od
CFLAGS_R  = /Ot
ASM  = masm
AFLAGS_G  = /Mx /T
AFLAGS_D  = /Zi
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
BIND  = bind
RC  = rc
IMPLIB	= implib
LFLAGS_G  = /NOI /BATCH
LFLAGS_D  = /CO /INC /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
MAPFILE_D  = NUL
MAPFILE_R  = NUL
BRFLAGS  =  /o $(PROJ).bsc
CXXFLAGS_G  =  /FR$*.sbr
BSCMAKE  = bscmake
SBRPACK  = sbrpack
BROWSE	= 1
PACK_SBRS  = 1

FILES  = GLMKCHAR.C CHVALID.C GLENV.C
OBJS  = GLMKCHAR.obj CHVALID.obj GLENV.obj
SBRS  = GLMKCHAR.sbr CHVALID.sbr GLENV.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .sbr .c

GLMKCHAR.obj : GLMKCHAR.C e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\string.h e:\lang\c700\include\ctype.h\
	e:\lang\c700\include\search.h e:\lang\c700\include\direct.h\
	e:\lang\c700\include\sys\types.h e:\lang\c700\include\stdlib.h\
	e:\lang\c700\include\time.h e:\lang\c700\include\io.h\
	e:\lang\c700\include\errno.h e:\lang\c700\include\sys\stat.h GLdefs.h\
	GLstruct.h GLextern.h
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /FoGLMKCHAR.obj GLMKCHAR.C
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /FoGLMKCHAR.obj GLMKCHAR.C
!ENDIF

GLMKCHAR.sbr : GLMKCHAR.C e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\string.h e:\lang\c700\include\ctype.h\
	e:\lang\c700\include\search.h e:\lang\c700\include\direct.h\
	e:\lang\c700\include\sys\types.h e:\lang\c700\include\stdlib.h\
	e:\lang\c700\include\time.h e:\lang\c700\include\io.h\
	e:\lang\c700\include\errno.h e:\lang\c700\include\sys\stat.h GLdefs.h\
	GLstruct.h GLextern.h
!IF $(DEBUG)
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FRGLMKCHAR.sbr GLMKCHAR.C
!ELSE
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FRGLMKCHAR.sbr GLMKCHAR.C
!ENDIF

CHVALID.obj : CHVALID.C e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\search.h e:\lang\c700\include\direct.h\
	e:\lang\c700\include\stdlib.h GLextern.h GLdefs.h GLstruct.h
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /FoCHVALID.obj CHVALID.C
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /FoCHVALID.obj CHVALID.C
!ENDIF

CHVALID.sbr : CHVALID.C e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\search.h e:\lang\c700\include\direct.h\
	e:\lang\c700\include\stdlib.h GLextern.h GLdefs.h GLstruct.h
!IF $(DEBUG)
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FRCHVALID.sbr CHVALID.C
!ELSE
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FRCHVALID.sbr CHVALID.C
!ENDIF

GLENV.obj : GLENV.C e:\lang\c700\include\signal.h e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\direct.h e:\lang\c700\include\sys\types.h\
	e:\lang\c700\include\stdlib.h e:\lang\c700\include\sys\stat.h\
	e:\lang\c700\include\io.h e:\lang\c700\include\errno.h GLdefs.h\
	GLstruct.h GLextern.h
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /FoGLENV.obj GLENV.C
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /FoGLENV.obj GLENV.C
!ENDIF

GLENV.sbr : GLENV.C e:\lang\c700\include\signal.h e:\lang\c700\include\stdio.h\
	e:\lang\c700\include\ctype.h e:\lang\c700\include\string.h\
	e:\lang\c700\include\direct.h e:\lang\c700\include\sys\types.h\
	e:\lang\c700\include\stdlib.h e:\lang\c700\include\sys\stat.h\
	e:\lang\c700\include\io.h e:\lang\c700\include\errno.h GLdefs.h\
	GLstruct.h GLextern.h
!IF $(DEBUG)
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FRGLENV.sbr GLENV.C
!ELSE
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FRGLENV.sbr GLENV.C
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
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
) +
$(LIBS: = +^
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
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
!IF $(DEBUG)
	$(ILINK) -a -e "$(LINKER) @$(PROJ).lrf" $@
!ELSE
	$(LINKER) @$(PROJ).lrf
!ENDIF


.c.obj :
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /Fo$@ $<
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /Fo$@ $<
!ENDIF

.c.sbr :
!IF $(DEBUG)
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FR$@ $<
!ELSE
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FR$@ $<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
