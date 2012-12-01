; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CJevView
LastTemplate=CMDIChildWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "jev.h"
VbxHeaderFile=jev.h
VbxImplementationFile=jev.cpp
LastPage=3

ClassCount=11
Class1=CJevApp
Class2=CJevDoc
Class3=CJevView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDD_CH_DIALOG
Resource3=IDD_ACCT_DLGBAR
Class5=CAboutDlg
Class6=CJEDialog
Class7=CDDEdit
Resource4=IDD_JE_DIALOG
Class8=CCHDialog
Resource5=IDR_MAINFRAME
Class9=CAcctDtlView
Class10=CAcct_DlgBar
Class11=CRptFrame
Resource6=IDR_JEVTYPE

[CLS:CJevApp]
Type=0
HeaderFile=jev.h
ImplementationFile=jev.cpp
Filter=N
LastObject=ID_EDIT_FIND

[CLS:CJevDoc]
Type=0
HeaderFile=jevdoc.h
ImplementationFile=jevdoc.cpp
Filter=N
LastObject=ID_EDIT_COPY
BaseClass=CDocument
VirtualFilter=DC

[CLS:CJevView]
Type=0
HeaderFile=jevview.h
ImplementationFile=jevview.cpp
Filter=C
LastObject=CJevView
BaseClass=CScrollView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC

[CLS:CAboutDlg]
Type=0
HeaderFile=jev.cpp
ImplementationFile=jev.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_TEST_RAWVIEW
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_JEVTYPE]
Type=1
Class=CJevView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_FIND
Command16=ID_EDIT_CHANGE
Command17=ID_EDIT_INSERT
Command18=ID_EDIT_APPEND
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_REPORT_ACCTDTL
Command22=ID_TEST_RAWVIEW
Command23=ID_WINDOW_NEW
Command24=ID_WINDOW_CASCADE
Command25=ID_WINDOW_TILE_HORZ
Command26=ID_WINDOW_ARRANGE
Command27=ID_APP_ABOUT
CommandCount=27

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_APPEND
Command2=ID_EDIT_COPY
Command3=ID_EDIT_CHANGE
Command4=ID_EDIT_FIND
Command5=ID_EDIT_INSERT
Command6=ID_FILE_NEW
Command7=ID_FILE_OPEN
Command8=ID_FILE_PRINT
Command9=ID_FILE_SAVE
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_CUT
Command18=ID_EDIT_UNDO
CommandCount=18

[DLG:IDD_JE_DIALOG]
Type=1
Class=CDDEdit
ControlCount=23
Control1=IDC_STATIC_MM,static,1342177280
Control2=IDC_STATIC,static,1342308353
Control3=IDC_EDIT3_DD,edit,1342373888
Control4=IDC_EDIT1_ACCT0,edit,1476591616
Control5=IDC_STATIC_DESC0,static,1342177280
Control6=IDC_EDIT3_AMT0,edit,1476595718
Control7=IDC_EDIT1_ACCT1,edit,1476591616
Control8=IDC_STATIC_DESC1,static,1342177280
Control9=IDC_EDIT3_AMT1,edit,1476595718
Control10=IDC_EDIT1_ACCT2,edit,1208156160
Control11=IDC_STATIC_DESC2,static,1342177280
Control12=IDC_EDIT3_AMT2,edit,1208160262
Control13=IDC_EDIT1_ACCT3,edit,1208156160
Control14=IDC_STATIC_DESC3,static,1342177280
Control15=IDC_EDIT3_AMT3,edit,1208160262
Control16=IDC_EDIT1_ACCT4,edit,1208156160
Control17=IDC_STATIC_DESC4,static,1342177280
Control18=IDC_EDIT3_AMT4,edit,1208160262
Control19=IDC_EDIT2_JE_DESC0,edit,1208025088
Control20=IDC_EDIT2_JE_DESC1,edit,1476591616
Control21=IDC_EDIT2_JE_DESC2,edit,1208025088
Control22=IDC_EDIT2_JE_DESC3,edit,1208025088
Control23=IDC_EDIT2_JE_DESC4,edit,1208025088

[CLS:CJEDialog]
Type=0
HeaderFile=jedialog.h
ImplementationFile=jedialog.cpp
Filter=D
LastObject=CJEDialog

[CLS:CDDEdit]
Type=0
HeaderFile=jedialog.h
ImplementationFile=jedialog.cpp
Filter=W
LastObject=CDDEdit

[DLG:IDD_CH_DIALOG]
Type=1
Class=CCHDialog
ControlCount=1
Control1=IDC_LIST1,listbox,1352728963

[CLS:CCHDialog]
Type=0
HeaderFile=chdialog.h
ImplementationFile=chdialog.cpp
Filter=D
LastObject=CCHDialog

[CLS:CAcctDtlView]
Type=0
HeaderFile=AcctDtlView.h
ImplementationFile=AcctDtlView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC
LastObject=CAcctDtlView

[DLG:IDD_ACCT_DLGBAR]
Type=1
Class=CAcct_DlgBar
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_ACCT,edit,1350762496
Control3=IDC_STATIC,static,1342308354

[CLS:CAcct_DlgBar]
Type=0
HeaderFile=Acct_DlgBar.h
ImplementationFile=Acct_DlgBar.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_ACCT

[CLS:CRptFrame]
Type=0
HeaderFile=RptFrame.h
ImplementationFile=RptFrame.cpp
BaseClass=CMDIChildWnd
Filter=D
VirtualFilter=mfWC
LastObject=CRptFrame

