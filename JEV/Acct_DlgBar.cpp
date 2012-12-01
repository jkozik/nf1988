// Acct_DlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "jev.h"
#include "Acct_DlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAcct_DlgBar dialog


CAcct_DlgBar::CAcct_DlgBar()
{
	//{{AFX_DATA_INIT(CAcct_DlgBar)
	m_Acct = _T("");
	//}}AFX_DATA_INIT
}


void CAcct_DlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAcct_DlgBar)
	DDX_Text(pDX, IDC_ACCT, m_Acct);
	DDV_MaxChars(pDX, m_Acct, 3);
	//}}AFX_DATA_MAP
}

IMPLEMENT_DYNAMIC(CAcct_DlgBar, CDialogBar)

BEGIN_MESSAGE_MAP(CAcct_DlgBar, CDialogBar)
	//{{AFX_MSG_MAP(CAcct_DlgBar)
	ON_BN_CLICKED(IDOK, OnGenerateReport)
	ON_EN_CHANGE(IDC_ACCT, OnChangeAcct)
	ON_EN_KILLFOCUS(IDC_ACCT, OnKillfocusAcct)
	ON_EN_SETFOCUS(IDC_ACCT, OnSetfocusAcct)
	ON_EN_MAXTEXT(IDC_ACCT, OnMaxtextAcct)
	ON_EN_UPDATE(IDC_ACCT, OnUpdateAcct)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAcct_DlgBar message handlers

void CAcct_DlgBar::OnGenerateReport() 
{
	// TODO: Add your control notification handler code here
	
}

void CAcct_DlgBar::OnChangeAcct() 
{
	// TODO: Add your control notification handler code here
	
}

void CAcct_DlgBar::OnKillfocusAcct() 
{
	// TODO: Add your control notification handler code here
	
}

void CAcct_DlgBar::OnSetfocusAcct() 
{
	// TODO: Add your control notification handler code here
	
}

void CAcct_DlgBar::OnMaxtextAcct() 
{
	// TODO: Add your control notification handler code here
	
}

void CAcct_DlgBar::OnUpdateAcct() 
{
	// TODO: Add your control notification handler code here
	
}
