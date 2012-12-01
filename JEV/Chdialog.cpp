// chdialog.cpp : implementation file
//

#include "stdafx.h"
#include "mainfrm.h"
#include "jev.h"
#include "chdialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCHDialog dialog


CCHDialog::CCHDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCHDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCHDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT 
	
	Create( CCHDialog::IDD, pParent );
}

void CCHDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCHDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCHDialog, CDialog)
	//{{AFX_MSG_MAP(CCHDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCHDialog message handlers

void CCHDialog::OnSelchangeList1()
{
	TRACE( "CCHDialog::OnSelchangeList1 Entered\n");
	int nSel, nTab;
	CString sAcctDesc, sAcct;
	
	CListBox* pLB = (CListBox*) GetDlgItem(IDC_LIST1);	
	nSel = pLB->GetCurSel();
	if( nSel == LB_ERR ) return;
	pLB->GetText( nSel, sAcctDesc );
	TRACE( "CCHDialog::OnSelchangeList1: sAcctDesc='%s'\n", sAcctDesc);
	
	nTab = sAcctDesc.Find('\t');
	if( nTab == -1 ) return;
	
	sAcct = sAcctDesc.Left( nTab );
	TRACE( "CCHDialog::OnSelchangeList1: sAcct='%s'\n", sAcct );
	
	m_hFocus->SetWindowText(sAcct);	
	ShowWindow( SW_HIDE );
}

BOOL CCHDialog::OnInitDialog()
{
	
	
	// TODO: Add extra initialization here 
	TRACE( "CCHDialog::OnInitDialog Entered\n" );	
	CListBox* pLB = (CListBox*) GetDlgItem(IDC_LIST1);
	pLB->SetTabStops( 16 );

	CRect rectDial, rectMainClient;
	int cyHeight,cxWidth;

	CMainFrame* pMainWnd;
	pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->GetClientRect( rectMainClient );
	pMainWnd->ClientToScreen( rectMainClient );

	GetWindowRect( rectDial );
	cxWidth = rectDial.Width();
	rectDial.right = rectMainClient.right - 2;
	rectDial.left = rectDial.right - cxWidth;

	cyHeight = rectDial.Height();
	rectDial.top = rectMainClient.top + pMainWnd->cyGetToolBarHeight()+2;
	rectDial.bottom = rectDial.top + cyHeight;
	MoveWindow( rectDial );
	

	return CDialog::OnInitDialog();  // return TRUE  unless you set the focus to a control
}

void CCHDialog::SetAcct( CString sAcct )
{
	
	TRACE( "CCHDialog::SetAcct: sAcct='%s'\n", sAcct );
	CListBox* pLB;
	int nLen;




	WPARAM idControl;                    
    CString sAcctFocus;
	
	m_hFocus = GetFocus();
	if( m_hFocus != NULL ) {
		idControl = m_hFocus->GetDlgCtrlID();
		m_hFocus->GetWindowText(sAcctFocus);
	}	
	TRACE("CCHDialog::SetAcct: idControl=%d, sAcctFocus='%s'\n", idControl, sAcctFocus );





	
	pLB = (CListBox*) GetDlgItem( IDC_LIST1 );
	pLB -> ResetContent();

	nLen = sAcct.GetLength();


    
    CChart* pNext = NULL;
    CString schDesc, schAcct, schAcct2;

    POSITION pos = pChartList->GetHeadPosition();
    while( pos != NULL )
    {
	pNext = (CChart *) pChartList->GetNext( pos );
	schAcct = pNext->GetChartAcct();
 
 	schAcct2 = schAcct + "   ";
	schDesc = pNext->GetDesc();	
	switch( nLen ) {
		case 0:
		   if (schAcct.GetLength() == 1) {
				pLB -> AddString( schAcct + "\t" + schDesc );
		   }
		   break;
		case 1:
		   if (sAcct == schAcct[0] && schAcct.GetLength() < 3) {
				pLB -> AddString( schAcct + "\t" + schDesc );
		   }
		   break;
		case 2:
		case 3:
		   if ( sAcct.Left(2) == schAcct2.Left(2) ) {
				pLB -> AddString( schAcct + "\t" + schDesc );
		   }
		   break;
		default:
			break;
		}
     } //while	

}    
void CCHDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);


	

	
	TRACE("CCHDialog::OnShowWindow: bShow=%d, nStatus=%d\n", bShow, nStatus );
	
}

void CCHDialog::OnPaint()
{

	TRACE( "CCHDialog::OnPaint: Entering.\n");

	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here


	CRect rectJEDialog, rectDial;
	
    if( m_pJEDialog != NULL )
		m_pJEDialog->GetWindowRect( rectJEDialog ); 
		
	GetWindowRect( rectDial );
	rectDial.bottom += rectJEDialog.top-rectDial.top; 
	rectDial.top = rectJEDialog.top;
	MoveWindow( rectDial );


	TRACE( "CCHDialog::OnPaint: Leaving.\n");
	
	// Do not call CDialog::OnPaint() for painting messages
}
