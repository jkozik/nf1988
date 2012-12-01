# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=Jsedit - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Jsedit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Jsedit - Win32 Release" && "$(CFG)" != "Jsedit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Jsedit32.mak" CFG="Jsedit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Jsedit - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Jsedit - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Jsedit - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Jsedit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Jsedit32.exe"

CLEAN : 
	-@erase ".\Release\Jsedit32.exe"
	-@erase ".\Release\Jsedit.obj"
	-@erase ".\Release\Chvalid.obj"
	-@erase ".\Release\Gdreport.obj"
	-@erase ".\Release\Glenv.obj"
	-@erase ".\Release\Gljefile.obj"
	-@erase ".\Release\Jeglsort.obj"
	-@erase ".\Release\Jevalinp.obj"
	-@erase ".\Release\Jmaarpt.obj"
	-@erase ".\Release\Jmacctfl.obj"
	-@erase ".\Release\Jmanaldt.obj"
	-@erase ".\Release\Jmedit.obj"
	-@erase ".\Release\Jmfile.obj"
	-@erase ".\Release\Jmfld.obj"
	-@erase ".\Release\Jmglrpt.obj"
	-@erase ".\Release\Jmlnedit.obj"
	-@erase ".\Release\Jmpregl.obj"
	-@erase ".\Release\Jmreport.obj"
	-@erase ".\Release\Jmyank.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX- /Ox /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_DOS" /FR /YX /c
# ADD CPP /nologo /W3 /GX- /Ox /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_DOS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W3 /GX- /Ox /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_DOS" /Fp"$(INTDIR)/Jsedit32.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Jsedit32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x1400 /subsystem:console /machine:IX86
# ADD LINK32 oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x1400 /subsystem:console /machine:IX86
LINK32_FLAGS=oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /stack:0x1400 /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/Jsedit32.pdb" /machine:IX86\
 /out:"$(OUTDIR)/Jsedit32.exe" 
LINK32_OBJS= \
	".\Release\Jsedit.obj" \
	".\Release\Chvalid.obj" \
	".\Release\Gdreport.obj" \
	".\Release\Glenv.obj" \
	".\Release\Gljefile.obj" \
	".\Release\Jeglsort.obj" \
	".\Release\Jevalinp.obj" \
	".\Release\Jmaarpt.obj" \
	".\Release\Jmacctfl.obj" \
	".\Release\Jmanaldt.obj" \
	".\Release\Jmedit.obj" \
	".\Release\Jmfile.obj" \
	".\Release\Jmfld.obj" \
	".\Release\Jmglrpt.obj" \
	".\Release\Jmlnedit.obj" \
	".\Release\Jmpregl.obj" \
	".\Release\Jmreport.obj" \
	".\Release\Jmyank.obj"

"$(OUTDIR)\Jsedit32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Jsedit32.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Jsedit32.exe"
	-@erase ".\Debug\Jsedit.obj"
	-@erase ".\Debug\Chvalid.obj"
	-@erase ".\Debug\Gdreport.obj"
	-@erase ".\Debug\Glenv.obj"
	-@erase ".\Debug\Gljefile.obj"
	-@erase ".\Debug\Jeglsort.obj"
	-@erase ".\Debug\Jevalinp.obj"
	-@erase ".\Debug\Jmaarpt.obj"
	-@erase ".\Debug\Jmacctfl.obj"
	-@erase ".\Debug\Jmanaldt.obj"
	-@erase ".\Debug\Jmedit.obj"
	-@erase ".\Debug\Jmfile.obj"
	-@erase ".\Debug\Jmfld.obj"
	-@erase ".\Debug\Jmglrpt.obj"
	-@erase ".\Debug\Jmlnedit.obj"
	-@erase ".\Debug\Jmpregl.obj"
	-@erase ".\Debug\Jmreport.obj"
	-@erase ".\Debug\Jmyank.obj"
	-@erase ".\Debug\Jsedit32.ilk"
	-@erase ".\Debug\Jsedit32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX- /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_DOS" /FR /YX /c
# ADD CPP /nologo /W3 /Gm /GX- /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_DOS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /Gm /GX- /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /D "_DOS" /Fp"$(INTDIR)/Jsedit32.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "c:\lib\curses" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Jsedit32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib mlcurses.lib qcprogs.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x1400 /subsystem:console /debug /machine:IX86
# ADD LINK32 oldnames.lib mlcurses.lib qcprogs.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x1400 /subsystem:console /debug /machine:IX86
LINK32_FLAGS=oldnames.lib mlcurses.lib qcprogs.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x1400\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/Jsedit32.pdb" /debug\
 /machine:IX86 /out:"$(OUTDIR)/Jsedit32.exe" 
LINK32_OBJS= \
	".\Debug\Jsedit.obj" \
	".\Debug\Chvalid.obj" \
	".\Debug\Gdreport.obj" \
	".\Debug\Glenv.obj" \
	".\Debug\Gljefile.obj" \
	".\Debug\Jeglsort.obj" \
	".\Debug\Jevalinp.obj" \
	".\Debug\Jmaarpt.obj" \
	".\Debug\Jmacctfl.obj" \
	".\Debug\Jmanaldt.obj" \
	".\Debug\Jmedit.obj" \
	".\Debug\Jmfile.obj" \
	".\Debug\Jmfld.obj" \
	".\Debug\Jmglrpt.obj" \
	".\Debug\Jmlnedit.obj" \
	".\Debug\Jmpregl.obj" \
	".\Debug\Jmreport.obj" \
	".\Debug\Jmyank.obj"

"$(OUTDIR)\Jsedit32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Jsedit - Win32 Release"
# Name "Jsedit - Win32 Debug"

!IF  "$(CFG)" == "Jsedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Jsedit.c
DEP_CPP_JSEDI=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jsedit.obj" : $(SOURCE) $(DEP_CPP_JSEDI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chvalid.c
DEP_CPP_CHVAL=\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	

"$(INTDIR)\Chvalid.obj" : $(SOURCE) $(DEP_CPP_CHVAL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gdreport.c
DEP_CPP_GDREP=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Gdreport.obj" : $(SOURCE) $(DEP_CPP_GDREP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Glenv.c
DEP_CPP_GLENV=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Glenv.obj" : $(SOURCE) $(DEP_CPP_GLENV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gljefile.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_GLJEF=\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_GLJEF=\
	".\curses.h"\
	

"$(INTDIR)\Gljefile.obj" : $(SOURCE) $(DEP_CPP_GLJEF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_GLJEF=\
	{$(INCLUDE)}"\curses.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Gljefile.obj" : $(SOURCE) $(DEP_CPP_GLJEF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jeglsort.c
DEP_CPP_JEGLS=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jeglsort.obj" : $(SOURCE) $(DEP_CPP_JEGLS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jevalinp.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JEVAL=\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JEVAL=\
	".\curses.h"\
	

"$(INTDIR)\Jevalinp.obj" : $(SOURCE) $(DEP_CPP_JEVAL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JEVAL=\
	{$(INCLUDE)}"\curses.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jevalinp.obj" : $(SOURCE) $(DEP_CPP_JEVAL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmaarpt.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMAAR=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMAAR=\
	".\curses.h"\
	

"$(INTDIR)\Jmaarpt.obj" : $(SOURCE) $(DEP_CPP_JMAAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMAAR=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmaarpt.obj" : $(SOURCE) $(DEP_CPP_JMAAR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmacctfl.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMACC=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMACC=\
	".\curses.h"\
	

"$(INTDIR)\Jmacctfl.obj" : $(SOURCE) $(DEP_CPP_JMACC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMACC=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmacctfl.obj" : $(SOURCE) $(DEP_CPP_JMACC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmanaldt.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMANA=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMANA=\
	".\curses.h"\
	

"$(INTDIR)\Jmanaldt.obj" : $(SOURCE) $(DEP_CPP_JMANA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMANA=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmanaldt.obj" : $(SOURCE) $(DEP_CPP_JMANA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmedit.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMEDI=\
	".\keys.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMEDI=\
	".\curses.h"\
	

"$(INTDIR)\Jmedit.obj" : $(SOURCE) $(DEP_CPP_JMEDI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMEDI=\
	{$(INCLUDE)}"\curses.h"\
	".\keys.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmedit.obj" : $(SOURCE) $(DEP_CPP_JMEDI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmfile.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMFIL=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMFIL=\
	".\curses.h"\
	

"$(INTDIR)\Jmfile.obj" : $(SOURCE) $(DEP_CPP_JMFIL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMFIL=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmfile.obj" : $(SOURCE) $(DEP_CPP_JMFIL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmfld.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMFLD=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMFLD=\
	".\curses.h"\
	

"$(INTDIR)\Jmfld.obj" : $(SOURCE) $(DEP_CPP_JMFLD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMFLD=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmfld.obj" : $(SOURCE) $(DEP_CPP_JMFLD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmglrpt.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMGLR=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMGLR=\
	".\curses.h"\
	

"$(INTDIR)\Jmglrpt.obj" : $(SOURCE) $(DEP_CPP_JMGLR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMGLR=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmglrpt.obj" : $(SOURCE) $(DEP_CPP_JMGLR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmlnedit.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMLNE=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMLNE=\
	".\curses.h"\
	

"$(INTDIR)\Jmlnedit.obj" : $(SOURCE) $(DEP_CPP_JMLNE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMLNE=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmlnedit.obj" : $(SOURCE) $(DEP_CPP_JMLNE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmpregl.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMPRE=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMPRE=\
	".\curses.h"\
	

"$(INTDIR)\Jmpregl.obj" : $(SOURCE) $(DEP_CPP_JMPRE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMPRE=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmpregl.obj" : $(SOURCE) $(DEP_CPP_JMPRE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmreport.c
DEP_CPP_JMREP=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\qwindow.h"\
	".\keys.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmreport.obj" : $(SOURCE) $(DEP_CPP_JMREP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jmyank.c

!IF  "$(CFG)" == "Jsedit - Win32 Release"

DEP_CPP_JMYAN=\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	
NODEP_CPP_JMYAN=\
	".\curses.h"\
	

"$(INTDIR)\Jmyank.obj" : $(SOURCE) $(DEP_CPP_JMYAN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Jsedit - Win32 Debug"

DEP_CPP_JMYAN=\
	{$(INCLUDE)}"\curses.h"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	".\GLdefs.h"\
	".\GLstruct.h"\
	".\GLextern.h"\
	".\JSdefs.h"\
	".\JSstruct.h"\
	".\JSextern.h"\
	

"$(INTDIR)\Jmyank.obj" : $(SOURCE) $(DEP_CPP_JMYAN) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
