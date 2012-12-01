// jev.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "jev.h" 
//#include "env.h"

#include "mainfrm.h"
//#include "jevdoc.h"
#include "jevview.h"
#include "acctdtlview.h"
#include "rptframe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJevApp

BEGIN_MESSAGE_MAP(CJevApp, CWinApp)
	//{{AFX_MSG_MAP(CJevApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TEST_RAWVIEW, OnTestRawview)
	ON_UPDATE_COMMAND_UI(ID_TEST_RAWVIEW, OnUpdateTestRawview)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJevApp construction

CJevApp::CJevApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CJevApp object

CJevApp NEAR theApp;  
CChartList* pChartList; 
UINT nFindMsg;

/////////////////////////////////////////////////////////////////////////////
// CJevApp initialization

BOOL CJevApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	SetDialogBkColor();        // Set dialog background color to gray
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	//EnableVBX();               // Initialize VBX support 
#ifdef _DEBUG	
    afxTraceEnabled = 1;
#endif
    TRACE( "F='%s'\n", getenv( "F" ) );
    m_env.Init(); 
#ifdef _DEBUG
    afxDump << m_env; 
#endif 
    
    nFindMsg = ::RegisterWindowMessage( FINDMSGSTRING );
    pChartList = &m_chart;
    m_chart.Open( m_env.m_path + "\\chart" ); 
    SetRawView( FALSE );
	m_pActiveJevDoc = NULL;
    //SetRawView( TRUE );
	//m_chart.Test();
	//CJEList jel;
	//jel.Test();
    
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_JEVTYPE,
		RUNTIME_CLASS(CJevDoc),
		RUNTIME_CLASS(CMDIChildWnd),        // standard MDI child frame
		RUNTIME_CLASS(CJevView));
	AddDocTemplate(pDocTemplate);

	m_pTemplate1 = new CMultiDocTemplate(IDR_JEVTYPE,
			RUNTIME_CLASS(CJevDoc),
			RUNTIME_CLASS(CRptFrame),	
			RUNTIME_CLASS(CAcctDtlView));

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// create a new (empty) document
	//OnFileNew();

	if (m_lpCmdLine[0] != '\0')
	{
		// TODO: add command line processing here
	}

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CJevApp Exit

int
CJevApp::ExitInstance()
{
 	TRACE( "Entering CJevApp::ExitInstance()\n" );
	delete m_pTemplate1;
 	m_chart.Close();
 	TRACE( "Leaving CJevApp::ExitInstance()\n" );
 	return( 0 );
}
 	
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CJevApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// VB-Event registration
// (calls to AfxRegisterVBEvent will be placed here by ClassWizard)

//{{AFX_VBX_REGISTER_MAP()
//}}AFX_VBX_REGISTER_MAP

/////////////////////////////////////////////////////////////////////////////
// CJevApp commands
//////////////////////////////////////////////////////////////////////////////
// Get/Set RawView BOOL parameter
// - If TRUE, the "raw" journal entry detail records are displayed
// - If FALSE, the "normal" multiline journal entry detail is shown
void
CJevApp::SetRawView( BOOL bRawView )
{
	m_bRawView = bRawView;
}
BOOL
CJevApp::bGetRawView( ) const
{
	return m_bRawView;
}		
void CJevApp::OnTestRawview()
{
	
	if( bGetRawView() == FALSE ) SetRawView( TRUE );
	else SetRawView( FALSE );  
	CFrameWnd* pFrameWnd = (CFrameWnd*) (AfxGetApp()->m_pMainWnd);
	CView* pCView = pFrameWnd->GetActiveView();
	if( pCView != NULL ) {
		 pCView->OnInitialUpdate();
	}	 

	
}

void CJevApp::OnUpdateTestRawview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( bGetRawView() );
	
}
