# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Jev - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Jev - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Jev - Win32 Release" && "$(CFG)" != "Jev - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "jev32.mak" CFG="Jev - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Jev - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Jev - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Jev - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Jev - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\jev32.exe" "$(OUTDIR)\jev32.bsc"

CLEAN : 
	-@erase ".\Release\jev32.bsc"
	-@erase ".\Release\Je.sbr"
	-@erase ".\Release\jev32.pch"
	-@erase ".\Release\Glt.sbr"
	-@erase ".\Release\Mmdd.sbr"
	-@erase ".\Release\Jev.sbr"
	-@erase ".\Release\Jedialog.sbr"
	-@erase ".\Release\RptFrame.sbr"
	-@erase ".\Release\Env.sbr"
	-@erase ".\Release\Chart.sbr"
	-@erase ".\Release\Desc.sbr"
	-@erase ".\Release\Chdialog.sbr"
	-@erase ".\Release\Mainfrm.sbr"
	-@erase ".\Release\Acct.sbr"
	-@erase ".\Release\Amt.sbr"
	-@erase ".\Release\Stdafx.sbr"
	-@erase ".\Release\Jevdoc.sbr"
	-@erase ".\Release\AcctDtlView.sbr"
	-@erase ".\Release\Jevview.sbr"
	-@erase ".\Release\jev32.exe"
	-@erase ".\Release\Amt.obj"
	-@erase ".\Release\Stdafx.obj"
	-@erase ".\Release\Jevdoc.obj"
	-@erase ".\Release\AcctDtlView.obj"
	-@erase ".\Release\Jevview.obj"
	-@erase ".\Release\Je.obj"
	-@erase ".\Release\Glt.obj"
	-@erase ".\Release\Mmdd.obj"
	-@erase ".\Release\Jev.obj"
	-@erase ".\Release\Jedialog.obj"
	-@erase ".\Release\RptFrame.obj"
	-@erase ".\Release\Env.obj"
	-@erase ".\Release\Chart.obj"
	-@erase ".\Release\Desc.obj"
	-@erase ".\Release\Chdialog.obj"
	-@erase ".\Release\Mainfrm.obj"
	-@erase ".\Release\Acct.obj"
	-@erase ".\Release\Jev.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/jev32.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Jev.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/jev32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/Je.sbr" \
	"$(INTDIR)/Glt.sbr" \
	"$(INTDIR)/Mmdd.sbr" \
	"$(INTDIR)/Jev.sbr" \
	"$(INTDIR)/Jedialog.sbr" \
	"$(INTDIR)/RptFrame.sbr" \
	"$(INTDIR)/Env.sbr" \
	"$(INTDIR)/Chart.sbr" \
	"$(INTDIR)/Desc.sbr" \
	"$(INTDIR)/Chdialog.sbr" \
	"$(INTDIR)/Mainfrm.sbr" \
	"$(INTDIR)/Acct.sbr" \
	"$(INTDIR)/Amt.sbr" \
	"$(INTDIR)/Stdafx.sbr" \
	"$(INTDIR)/Jevdoc.sbr" \
	"$(INTDIR)/AcctDtlView.sbr" \
	"$(INTDIR)/Jevview.sbr"

"$(OUTDIR)\jev32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x5000 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x5000 /subsystem:windows /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x5000 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/jev32.pdb" /machine:IX86 /def:".\Jev.def"\
 /out:"$(OUTDIR)/jev32.exe" 
DEF_FILE= \
	".\Jev.def"
LINK32_OBJS= \
	"$(INTDIR)/Amt.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Jevdoc.obj" \
	"$(INTDIR)/AcctDtlView.obj" \
	"$(INTDIR)/Jevview.obj" \
	"$(INTDIR)/Je.obj" \
	"$(INTDIR)/Glt.obj" \
	"$(INTDIR)/Mmdd.obj" \
	"$(INTDIR)/Jev.obj" \
	"$(INTDIR)/Jedialog.obj" \
	"$(INTDIR)/RptFrame.obj" \
	"$(INTDIR)/Env.obj" \
	"$(INTDIR)/Chart.obj" \
	"$(INTDIR)/Desc.obj" \
	"$(INTDIR)/Chdialog.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Acct.obj" \
	"$(INTDIR)/Jev.res"

"$(OUTDIR)\jev32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\jev32.exe" "$(OUTDIR)\jev32.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\jev32.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\jev32.bsc"
	-@erase ".\Debug\RptFrame.sbr"
	-@erase ".\Debug\Mainfrm.sbr"
	-@erase ".\Debug\Desc.sbr"
	-@erase ".\Debug\Stdafx.sbr"
	-@erase ".\Debug\Env.sbr"
	-@erase ".\Debug\Jevdoc.sbr"
	-@erase ".\Debug\Acct.sbr"
	-@erase ".\Debug\Chdialog.sbr"
	-@erase ".\Debug\AcctDtlView.sbr"
	-@erase ".\Debug\Mmdd.sbr"
	-@erase ".\Debug\Glt.sbr"
	-@erase ".\Debug\Je.sbr"
	-@erase ".\Debug\Jevview.sbr"
	-@erase ".\Debug\Amt.sbr"
	-@erase ".\Debug\Jev.sbr"
	-@erase ".\Debug\Chart.sbr"
	-@erase ".\Debug\Jedialog.sbr"
	-@erase ".\Debug\jev32.exe"
	-@erase ".\Debug\Jevview.obj"
	-@erase ".\Debug\Amt.obj"
	-@erase ".\Debug\Jev.obj"
	-@erase ".\Debug\Chart.obj"
	-@erase ".\Debug\Jedialog.obj"
	-@erase ".\Debug\RptFrame.obj"
	-@erase ".\Debug\Mainfrm.obj"
	-@erase ".\Debug\Desc.obj"
	-@erase ".\Debug\Stdafx.obj"
	-@erase ".\Debug\Env.obj"
	-@erase ".\Debug\Jevdoc.obj"
	-@erase ".\Debug\Acct.obj"
	-@erase ".\Debug\Chdialog.obj"
	-@erase ".\Debug\AcctDtlView.obj"
	-@erase ".\Debug\Mmdd.obj"
	-@erase ".\Debug\Glt.obj"
	-@erase ".\Debug\Je.obj"
	-@erase ".\Debug\Jev.res"
	-@erase ".\Debug\jev32.ilk"
	-@erase ".\Debug\jev32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/jev32.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Jev.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/jev32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/RptFrame.sbr" \
	"$(INTDIR)/Mainfrm.sbr" \
	"$(INTDIR)/Desc.sbr" \
	"$(INTDIR)/Stdafx.sbr" \
	"$(INTDIR)/Env.sbr" \
	"$(INTDIR)/Jevdoc.sbr" \
	"$(INTDIR)/Acct.sbr" \
	"$(INTDIR)/Chdialog.sbr" \
	"$(INTDIR)/AcctDtlView.sbr" \
	"$(INTDIR)/Mmdd.sbr" \
	"$(INTDIR)/Glt.sbr" \
	"$(INTDIR)/Je.sbr" \
	"$(INTDIR)/Jevview.sbr" \
	"$(INTDIR)/Amt.sbr" \
	"$(INTDIR)/Jev.sbr" \
	"$(INTDIR)/Chart.sbr" \
	"$(INTDIR)/Jedialog.sbr"

"$(OUTDIR)\jev32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x5000 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x5000 /subsystem:windows /debug /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x5000 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/jev32.pdb" /debug /machine:IX86\
 /def:".\Jev.def" /out:"$(OUTDIR)/jev32.exe" 
DEF_FILE= \
	".\Jev.def"
LINK32_OBJS= \
	"$(INTDIR)/Jevview.obj" \
	"$(INTDIR)/Amt.obj" \
	"$(INTDIR)/Jev.obj" \
	"$(INTDIR)/Chart.obj" \
	"$(INTDIR)/Jedialog.obj" \
	"$(INTDIR)/RptFrame.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Desc.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Env.obj" \
	"$(INTDIR)/Jevdoc.obj" \
	"$(INTDIR)/Acct.obj" \
	"$(INTDIR)/Chdialog.obj" \
	"$(INTDIR)/AcctDtlView.obj" \
	"$(INTDIR)/Mmdd.obj" \
	"$(INTDIR)/Glt.obj" \
	"$(INTDIR)/Je.obj" \
	"$(INTDIR)/Jev.res"

"$(OUTDIR)\jev32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Jev - Win32 Release"
# Name "Jev - Win32 Debug"

!IF  "$(CFG)" == "Jev - Win32 Release"

!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Jev.rc
DEP_RSC_JEV_R=\
	".\Res\Jev.ico"\
	".\Res\Jevdoc.ico"\
	".\Res\Toolbar.bmp"\
	".\Res\Jev.rc2"\
	

"$(INTDIR)\Jev.res" : $(SOURCE) $(DEP_RSC_JEV_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Jev - Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/jev32.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\jev32.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/jev32.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\jev32.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jev.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_JEV_C=\
	".\stdafx.h"\
	".\Jev.h"\
	".\mainfrm.h"\
	".\Jevdoc.h"\
	".\jevview.h"\
	".\AcctDtlView.h"\
	".\RptFrame.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

"$(INTDIR)\Jev.obj" : $(SOURCE) $(DEP_CPP_JEV_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Jev.sbr" : $(SOURCE) $(DEP_CPP_JEV_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_JEV_C=\
	".\stdafx.h"\
	".\Jev.h"\
	".\mainfrm.h"\
	".\jevview.h"\
	".\AcctDtlView.h"\
	".\RptFrame.h"\
	

"$(INTDIR)\Jev.obj" : $(SOURCE) $(DEP_CPP_JEV_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Jev.sbr" : $(SOURCE) $(DEP_CPP_JEV_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mainfrm.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_MAINF=\
	".\stdafx.h"\
	".\Jev.h"\
	".\RptFrame.h"\
	".\mainfrm.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Jevdoc.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_MAINF=\
	".\stdafx.h"\
	".\Jev.h"\
	".\RptFrame.h"\
	".\mainfrm.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jevdoc.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_JEVDO=\
	".\stdafx.h"\
	".\mainfrm.h"\
	".\Jev.h"\
	".\Jevdoc.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

"$(INTDIR)\Jevdoc.obj" : $(SOURCE) $(DEP_CPP_JEVDO) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Jevdoc.sbr" : $(SOURCE) $(DEP_CPP_JEVDO) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_JEVDO=\
	".\stdafx.h"\
	".\mainfrm.h"\
	".\Jev.h"\
	

"$(INTDIR)\Jevdoc.obj" : $(SOURCE) $(DEP_CPP_JEVDO) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Jevdoc.sbr" : $(SOURCE) $(DEP_CPP_JEVDO) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jevview.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_JEVVI=\
	".\stdafx.h"\
	".\Jev.h"\
	".\mainfrm.h"\
	".\Jevdoc.h"\
	".\jevview.h"\
	".\Jedialog.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	".\Chdialog.h"\
	

"$(INTDIR)\Jevview.obj" : $(SOURCE) $(DEP_CPP_JEVVI) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Jevview.sbr" : $(SOURCE) $(DEP_CPP_JEVVI) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_JEVVI=\
	".\stdafx.h"\
	".\Jev.h"\
	".\mainfrm.h"\
	".\jevview.h"\
	".\Jedialog.h"\
	

"$(INTDIR)\Jevview.obj" : $(SOURCE) $(DEP_CPP_JEVVI) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Jevview.sbr" : $(SOURCE) $(DEP_CPP_JEVVI) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Env.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_ENV_C=\
	".\stdafx.h"\
	".\Jev.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Jevdoc.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

"$(INTDIR)\Env.obj" : $(SOURCE) $(DEP_CPP_ENV_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Env.sbr" : $(SOURCE) $(DEP_CPP_ENV_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_ENV_C=\
	".\stdafx.h"\
	".\Jev.h"\
	".\Env.h"\
	

"$(INTDIR)\Env.obj" : $(SOURCE) $(DEP_CPP_ENV_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Env.sbr" : $(SOURCE) $(DEP_CPP_ENV_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chart.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_CHART=\
	".\stdafx.h"\
	".\Chart.h"\
	".\Acct.h"\
	".\Desc.h"\
	

"$(INTDIR)\Chart.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Chart.sbr" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_CHART=\
	".\stdafx.h"\
	".\Chart.h"\
	

"$(INTDIR)\Chart.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Chart.sbr" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Acct.cpp
DEP_CPP_ACCT_=\
	".\stdafx.h"\
	".\Acct.h"\
	

"$(INTDIR)\Acct.obj" : $(SOURCE) $(DEP_CPP_ACCT_) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Acct.sbr" : $(SOURCE) $(DEP_CPP_ACCT_) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Desc.cpp
DEP_CPP_DESC_=\
	".\stdafx.h"\
	".\Desc.h"\
	

"$(INTDIR)\Desc.obj" : $(SOURCE) $(DEP_CPP_DESC_) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Desc.sbr" : $(SOURCE) $(DEP_CPP_DESC_) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Glt.cpp
DEP_CPP_GLT_C=\
	".\stdafx.h"\
	".\Glt.h"\
	".\Je.h"\
	".\Mmdd.h"\
	".\Acct.h"\
	".\Amt.h"\
	".\Desc.h"\
	

"$(INTDIR)\Glt.obj" : $(SOURCE) $(DEP_CPP_GLT_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Glt.sbr" : $(SOURCE) $(DEP_CPP_GLT_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Je.cpp
DEP_CPP_JE_CP=\
	".\stdafx.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Acct.h"\
	".\Amt.h"\
	".\Desc.h"\
	

"$(INTDIR)\Je.obj" : $(SOURCE) $(DEP_CPP_JE_CP) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Je.sbr" : $(SOURCE) $(DEP_CPP_JE_CP) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Amt.cpp
DEP_CPP_AMT_C=\
	".\stdafx.h"\
	".\Amt.h"\
	

"$(INTDIR)\Amt.obj" : $(SOURCE) $(DEP_CPP_AMT_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Amt.sbr" : $(SOURCE) $(DEP_CPP_AMT_C) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mmdd.cpp
DEP_CPP_MMDD_=\
	".\stdafx.h"\
	".\Mmdd.h"\
	

"$(INTDIR)\Mmdd.obj" : $(SOURCE) $(DEP_CPP_MMDD_) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Mmdd.sbr" : $(SOURCE) $(DEP_CPP_MMDD_) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jedialog.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_JEDIA=\
	".\stdafx.h"\
	".\mainfrm.h"\
	".\Jev.h"\
	".\Jedialog.h"\
	".\Jevdoc.h"\
	".\jevview.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Chdialog.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

"$(INTDIR)\Jedialog.obj" : $(SOURCE) $(DEP_CPP_JEDIA) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Jedialog.sbr" : $(SOURCE) $(DEP_CPP_JEDIA) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_JEDIA=\
	".\stdafx.h"\
	".\mainfrm.h"\
	".\Jev.h"\
	".\Jedialog.h"\
	".\jevview.h"\
	

"$(INTDIR)\Jedialog.obj" : $(SOURCE) $(DEP_CPP_JEDIA) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Jedialog.sbr" : $(SOURCE) $(DEP_CPP_JEDIA) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chdialog.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_CHDIA=\
	".\stdafx.h"\
	".\mainfrm.h"\
	".\Jev.h"\
	".\Chdialog.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Jevdoc.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

"$(INTDIR)\Chdialog.obj" : $(SOURCE) $(DEP_CPP_CHDIA) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Chdialog.sbr" : $(SOURCE) $(DEP_CPP_CHDIA) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_CHDIA=\
	".\stdafx.h"\
	".\mainfrm.h"\
	".\Jev.h"\
	".\Chdialog.h"\
	

"$(INTDIR)\Chdialog.obj" : $(SOURCE) $(DEP_CPP_CHDIA) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\Chdialog.sbr" : $(SOURCE) $(DEP_CPP_CHDIA) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jev.def

!IF  "$(CFG)" == "Jev - Win32 Release"

!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AcctDtlView.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_ACCTD=\
	".\stdafx.h"\
	".\Jev.h"\
	".\AcctDtlView.h"\
	".\Acct_DlgBar.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Jevdoc.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

"$(INTDIR)\AcctDtlView.obj" : $(SOURCE) $(DEP_CPP_ACCTD) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\AcctDtlView.sbr" : $(SOURCE) $(DEP_CPP_ACCTD) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_ACCTD=\
	".\stdafx.h"\
	".\Jev.h"\
	".\AcctDtlView.h"\
	".\Acct_DlgBar.h"\
	

"$(INTDIR)\AcctDtlView.obj" : $(SOURCE) $(DEP_CPP_ACCTD) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\AcctDtlView.sbr" : $(SOURCE) $(DEP_CPP_ACCTD) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Acct_DlgBar.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

# PROP Exclude_From_Build 1
DEP_CPP_ACCT_D=\
	".\stdafx.h"\
	".\Jev.h"\
	".\Acct_DlgBar.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Jevdoc.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

# PROP Exclude_From_Build 1
DEP_CPP_ACCT_D=\
	".\stdafx.h"\
	".\Jev.h"\
	".\Acct_DlgBar.h"\
	

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RptFrame.cpp

!IF  "$(CFG)" == "Jev - Win32 Release"

DEP_CPP_RPTFR=\
	".\stdafx.h"\
	".\Jev.h"\
	".\Jevdoc.h"\
	".\RptFrame.h"\
	".\Env.h"\
	".\Chart.h"\
	".\Acct.h"\
	".\Desc.h"\
	".\Je.h"\
	".\Glt.h"\
	".\Mmdd.h"\
	".\Amt.h"\
	

"$(INTDIR)\RptFrame.obj" : $(SOURCE) $(DEP_CPP_RPTFR) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\RptFrame.sbr" : $(SOURCE) $(DEP_CPP_RPTFR) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ELSEIF  "$(CFG)" == "Jev - Win32 Debug"

DEP_CPP_RPTFR=\
	".\stdafx.h"\
	".\Jev.h"\
	".\Glt.h"\
	".\RptFrame.h"\
	".\Mmdd.h"\
	".\Acct.h"\
	".\Amt.h"\
	".\Desc.h"\
	

"$(INTDIR)\RptFrame.obj" : $(SOURCE) $(DEP_CPP_RPTFR) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"

"$(INTDIR)\RptFrame.sbr" : $(SOURCE) $(DEP_CPP_RPTFR) "$(INTDIR)"\
 "$(INTDIR)\jev32.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
