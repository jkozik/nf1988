// RptFrame.cpp : implementation file
//

#include "stdafx.h"
#include "jev.h"
#include "glt.h"
//#include "jevdoc.h"
//#include "Acct_DlgBar.h"
#include "RptFrame.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRptFrame

IMPLEMENT_DYNCREATE(CRptFrame, CMDIChildWnd)

CRptFrame::CRptFrame()
{
}

CRptFrame::~CRptFrame()
{
}


BEGIN_MESSAGE_MAP(CRptFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRptFrame)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, OnGenerateReport)
	ON_EN_CHANGE(IDC_ACCT, OnChangeAcct)
	ON_EN_KILLFOCUS(IDC_ACCT, OnKillfocusAcct)
	ON_EN_SETFOCUS(IDC_ACCT, OnSetfocusAcct)
	ON_EN_MAXTEXT(IDC_ACCT, OnMaxtextAcct)
	ON_EN_UPDATE(IDC_ACCT, OnUpdateAcct)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRptFrame message handlers

int CRptFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if( !m_Acct_DlgBar.Create( this, IDD_ACCT_DLGBAR, CBRS_TOP, 1)  ) {
		TRACE("CRptFrame: Failed to create dialog bar\n");
		return -1;
	}

	CWnd* pAcct = m_Acct_DlgBar.GetDlgItem( IDC_ACCT );
	pAcct->SetFocus( );
	CWinApp* pApp = AfxGetApp( );
	//CFrameWnd* pMainFrame = (CFrameWnd*) (AfxGetApp()->m_pMainWnd);
	//CJevDoc* pDoc = (CJevDoc*) pMainFrame->GetActiveDocument();
	//ASSERT_VALID(pDoc);
	CJevApp* pJevApp =  ((CJevApp*) AfxGetApp());
	CJevDoc* pDoc = pJevApp -> m_pActiveJevDoc;
	int ar = pDoc->njeGetActiveRecord();
	CJournalEntry* pJE = pDoc->m_JEArray.GetAtJe( ar );
	m_sAcct = pJE->GetCrAcct();
	m_Acct_DlgBar.SetDlgItemText( IDC_ACCT, m_sAcct);



	//GotoDlgCtrl( pAcct );
	return 0;
}

BOOL CRptFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CMDIChildWnd::OnCommand(wParam, lParam);
}


/////////////////////////////////////////////////////////////////////////////
// CAcct_DlgBar message handlers

void CRptFrame::OnGenerateReport() 
{
	// TODO: Add your control notification handler code here
	const MSG* pMsg;
	WPARAM wCurrentId;

	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam); 
	TRACE("CRptFrame::OnGenerateReport:  wCurrentId=%d\n",wCurrentId);




	CJevApp* pJevApp =  ((CJevApp*) AfxGetApp());
	CJevDoc* pDoc = pJevApp -> m_pActiveJevDoc;


	CString  sAnalOutFileName = pJevApp->m_env.m_path + "\\"
		+ "anal" + m_sAcct + ".out";
	
	CStdioFile RptFile( sAnalOutFileName, CFile::modeWrite | CFile::modeCreate );



	GltAllMonths GltAll( GltAllMonths::SortByMonthAcct );
	CGlTran glt;

	GltAll.Open();
	while( (glt=GltAll.GetNextGlt()).GetCrAcct() != "" ) {
		if( glt.GetCrAcct() == m_sAcct ) RptFile.WriteString( (CString) glt + "\r" +  "\n" );
	}
	GltAll.Close();
			
	
}

void CRptFrame::OnChangeAcct() 
{
	// TODO: Add your control notification handler code here
	const MSG* pMsg;
	WPARAM wCurrentId;

	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam); 
	TRACE("CRptFrame::OnChangeAcct:  wCurrentId=%d\n",wCurrentId);
	
}

void CRptFrame::OnKillfocusAcct() 
{
	// TODO: Add your control notification handler code here
	const MSG* pMsg;
	WPARAM wCurrentId;

	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam); 
	TRACE("CRptFrame::OnKillfocusAcct:  wCurrentId=%d\n",wCurrentId);
	
}

void CRptFrame::OnSetfocusAcct() 
{
	// TODO: Add your control notification handler code here
	const MSG* pMsg;
	WPARAM wCurrentId;

	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam); 
	TRACE("CRptFrame::OnSetfocusAcct:  wCurrentId=%d\n",wCurrentId);
	
}

void CRptFrame::OnMaxtextAcct() 
{
	// TODO: Add your control notification handler code here
	const MSG* pMsg;
	WPARAM wCurrentId;

	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam); 
	TRACE("CRptFrame::OnMaxtextAcct:  wCurrentId=%d\n",wCurrentId);
	
}

void CRptFrame::OnUpdateAcct() 
{
	// TODO: Add your control notification handler code here
	const MSG* pMsg;
	WPARAM wCurrentId;

	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam); 
	TRACE("CRptFrame::OnUpdateAcct:  wCurrentId=%d\n",wCurrentId);
	
}

