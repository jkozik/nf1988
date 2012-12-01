// AcctDtlView.cpp : implementation file
//

/*
#include "stdafx.h"
#include "jev.h"
#include "mainfrm.h"
#include "jevdoc.h"
#include "jevview.h"


*/

#include "stdafx.h"
#include "jev.h"
#include "AcctDtlView.h"
#include "Acct_DlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAcctDtlView

IMPLEMENT_DYNCREATE(CAcctDtlView, CScrollView)

CAcctDtlView::CAcctDtlView()
{
}

CAcctDtlView::~CAcctDtlView()
{
}


BEGIN_MESSAGE_MAP(CAcctDtlView, CScrollView)
	//{{AFX_MSG_MAP(CAcctDtlView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAcctDtlView drawing

void CAcctDtlView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();



	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CAcctDtlView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here


	CFont font;
    font.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
                    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    FIXED_PITCH | FF_MODERN, "");
    CFont* pOldFont = (CFont*) pDC->SelectObject(&font);


	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	CString sFile, sANAL_OUT;

	sFile = pDoc->GetPathName();
	if(sFile == "") return;

	_splitpath( sFile, drive, dir, fname, ext );


	sANAL_OUT = (CString)drive + (CString)dir + "anal.out";
	TRACE("OnDraw: sANAL_OUT='%s'\n", sANAL_OUT);
	

	SetWindowText("Account Detail");

	CFileStatus status;
	if( CFile::GetStatus( sANAL_OUT, status ) == 0 ) {
		TRACE("OnDraw: GetStatus(%s) does not exist\n", sANAL_OUT);
		return;
	}

	TEXTMETRIC tm;
	int cyChar, cxChar, cyClient, cyTop,nRecords;
	CString sLine;
	pDC->GetTextMetrics( &tm );
	cyChar = tm.tmHeight;
	cxChar = tm.tmAveCharWidth;
	cyTop = 0;
	nRecords = 0;

	CStdioFile cf( sANAL_OUT, CFile::modeRead );
	while( cf.ReadString( sLine ) ) {
		pDC->TextOut( 0, cyTop, sLine );
		cyTop += cyChar;
		nRecords++;
	}
	cf.Close();
	CRect rectClient;
	GetClientRect( rectClient );
	cyClient = rectClient.Height();
	CSize sizeTotal( cxChar*VIEW_WIDTH, cyChar*nRecords );
	CSize sizePage( cxChar*VIEW_WIDTH / 5,
				max( cyChar, ((cyClient/cyChar)-1)*cyChar));
	CSize sizeLine( cxChar*VIEW_WIDTH/20, cyChar );
	SetScrollSizes( MM_TEXT, sizeTotal, sizePage, sizeLine );
	pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CAcctDtlView diagnostics

#ifdef _DEBUG
void CAcctDtlView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAcctDtlView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAcctDtlView message handlers

BOOL CAcctDtlView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if( CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext) )
		return -1;


	return 0;
}

int CAcctDtlView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here



	return 0;
}
