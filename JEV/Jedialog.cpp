// jedialog.cpp : implementation file
//

#include "stdafx.h"
#include "mainfrm.h"
#include "jev.h"
#include "jedialog.h" 

//#include "jevdoc.h"
#include "jevview.h"
#include <ctype.h>
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const MaxStringLen = 30;

/////////////////////////////////////////////////////////////////////////////
// CJEDialog dialog


CJEDialog::CJEDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CJEDialog::IDD, pParent)
{   
	m_LineCount = 0; 
	for( int i=0; i<nControlCount; i++) {
		m_acct[i]="";
		m_amt[i]="";
		m_desc[i]="";
		m_jedesc[i]="";
	}

	//{{AFX_DATA_INIT(CJEDialog)
	m_dd = "";
	m_mm = "";
	//}}AFX_DATA_INIT
}

void CJEDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	for( int i=0; i<nControlCount; i++) {
		DDX_Text(pDX, idAcctControl[i], m_acct[i]);
		DDV_MaxChars(pDX, m_acct[i], 3);
		DDX_Text(pDX, idAmtControl[i], m_amt[i]);
		DDV_MaxChars(pDX, m_amt[i], 10);
		DDX_Text(pDX, idDescControl[i], m_desc[i]);
		//DDV_MaxChars(pDX, m_desc[i], 20);
		DDX_Text(pDX, idJedescControl[i], m_jedesc[i]);
		//DDV_MaxChars(pDX, m_jedesc[i], 30);
	}
	//{{AFX_DATA_MAP(CJEDialog)
	DDX_Text(pDX, IDC_EDIT3_DD, m_dd);
	DDV_MaxChars(pDX, m_dd, 2);
	DDX_Text(pDX, IDC_STATIC_MM, m_mm);
	DDV_MaxChars(pDX, m_mm, 2);
	//}}AFX_DATA_MAP 
	
	if( pDX->m_bSaveAndValidate ) {
		if( m_pJE == NULL ) 
			m_pJE = (CJournalEntry*) new CJournalEntry();
		m_pJE->SetDesc( "" );
		m_pJE->DelAcctAmt();
		m_pJE->SetMmdd( m_mm + m_dd );
		for( int i=0; i<m_LineCount-1; i++ ) {
			m_pJE->AddAcct( (CAcct) m_acct[i] );
			m_pJE->AddAmt ( (CAmt)  m_amt[i]  );	
		}
		m_pJE->SetCrAcct( m_acct[i] );
		m_pJE->SetDesc( m_jedesc[i] );
		TRACE("DoDataExchange: pJE='%s'\n", (CString) *m_pJE );		
	}
		
}

BEGIN_MESSAGE_MAP(CJEDialog, CDialog)
	//{{AFX_MSG_MAP(CJEDialog)
	ON_EN_CHANGE(IDC_EDIT3_DD, OnChangeEdit3DD)
	ON_EN_CHANGE(IDC_EDIT1_ACCT0, OnChangeEdit1Acct)
	ON_EN_SETFOCUS(IDC_EDIT1_ACCT0, OnSetfocusEdit1Acct)
	ON_EN_KILLFOCUS(IDC_EDIT1_ACCT0, OnKillfocusEdit1Acct)
	ON_EN_CHANGE(IDC_EDIT3_AMT0, OnChangeEdit3Amt)
	ON_EN_SETFOCUS(IDC_EDIT3_AMT0, OnSetfocusEdit3Amt)
	ON_EN_KILLFOCUS(IDC_EDIT3_AMT0, OnKillfocusEdit3Amt)
	ON_EN_SETFOCUS(IDC_EDIT3_DD, OnSetfocusEdit3Dd)
	ON_EN_KILLFOCUS(IDC_EDIT3_DD, OnKillfocusEdit3Dd)
	ON_WM_ACTIVATEAPP()
	ON_EN_CHANGE(IDC_EDIT1_ACCT1, OnChangeEdit1Acct)
	ON_EN_CHANGE(IDC_EDIT1_ACCT2, OnChangeEdit1Acct)
	ON_EN_CHANGE(IDC_EDIT1_ACCT3, OnChangeEdit1Acct)
	ON_EN_CHANGE(IDC_EDIT1_ACCT4, OnChangeEdit1Acct)
	ON_EN_SETFOCUS(IDC_EDIT1_ACCT1, OnSetfocusEdit1Acct)
	ON_EN_SETFOCUS(IDC_EDIT1_ACCT2, OnSetfocusEdit1Acct)
	ON_EN_SETFOCUS(IDC_EDIT1_ACCT3, OnSetfocusEdit1Acct)
	ON_EN_SETFOCUS(IDC_EDIT1_ACCT4, OnSetfocusEdit1Acct)
	ON_EN_KILLFOCUS(IDC_EDIT1_ACCT1, OnKillfocusEdit1Acct)
	ON_EN_KILLFOCUS(IDC_EDIT1_ACCT2, OnKillfocusEdit1Acct)
	ON_EN_KILLFOCUS(IDC_EDIT1_ACCT3, OnKillfocusEdit1Acct)
	ON_EN_KILLFOCUS(IDC_EDIT1_ACCT4, OnKillfocusEdit1Acct)
	ON_EN_CHANGE(IDC_EDIT3_AMT1, OnChangeEdit3Amt)
	ON_EN_CHANGE(IDC_EDIT3_AMT2, OnChangeEdit3Amt)
	ON_EN_CHANGE(IDC_EDIT3_AMT3, OnChangeEdit3Amt)
	ON_EN_CHANGE(IDC_EDIT3_AMT4, OnChangeEdit3Amt)
	ON_EN_SETFOCUS(IDC_EDIT3_AMT1, OnSetfocusEdit3Amt)
	ON_EN_SETFOCUS(IDC_EDIT3_AMT2, OnSetfocusEdit3Amt)
	ON_EN_SETFOCUS(IDC_EDIT3_AMT3, OnSetfocusEdit3Amt)
	ON_EN_SETFOCUS(IDC_EDIT3_AMT4, OnSetfocusEdit3Amt)
	ON_EN_KILLFOCUS(IDC_EDIT3_AMT1, OnKillfocusEdit3Amt)
	ON_EN_KILLFOCUS(IDC_EDIT3_AMT2, OnKillfocusEdit3Amt)
	ON_EN_KILLFOCUS(IDC_EDIT3_AMT3, OnKillfocusEdit3Amt)
	ON_EN_KILLFOCUS(IDC_EDIT3_AMT4, OnKillfocusEdit3Amt)
	ON_WM_CHAR()
	ON_EN_SETFOCUS(IDC_EDIT2_JE_DESC0, OnSetfocusEdit2JeDesc)
	ON_EN_SETFOCUS(IDC_EDIT2_JE_DESC1, OnSetfocusEdit2JeDesc)
	ON_EN_SETFOCUS(IDC_EDIT2_JE_DESC2, OnSetfocusEdit2JeDesc)
	ON_EN_SETFOCUS(IDC_EDIT2_JE_DESC3, OnSetfocusEdit2JeDesc)
	ON_EN_SETFOCUS(IDC_EDIT2_JE_DESC4, OnSetfocusEdit2JeDesc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
/////////////////////////////////////////////////////////////////////////////
// CJEDialog message handlers 
BOOL CJEDialog::OnInitDialog()
{
	
	
	TRACE( "CJEDialog::OnInitDialog() Entered\n");
	
	CString sText,acct;
   	CChart* pCH;

	int i;
	
	
	m_chDlg.m_pJEDialog = this;	   
	
	
	m_bActive = TRUE;
	m_bCancelPressed = FALSE;
	
	m_ddEdit.SubclassDlgItem( IDC_EDIT3_DD, this );
	for(i=0; i<nControlCount; i++ ) {
		m_AmtEdit[i].SubclassDlgItem( idAmtControl[i], this );
	}	
    

	GetDlgItem( IDC_EDIT3_DD)->SetFocus( );
	GetDlgItem( IDC_EDIT3_DD)->EnableWindow();
	GetDlgItem( IDC_EDIT3_DD)->ShowWindow( SW_SHOWNA );
	
	
	if( m_pJE == NULL ) {  
		m_LineCount = 2; 
	} else {
		m_LineCount = m_pJE->GetSize() + 1;
	}	

	CRect rectDial; 
	CWindowDC dc( this );
	TEXTMETRIC tm;
	dc.GetTextMetrics( &tm );
    TRACE("OnInitDialog: tmHeight=%d, tmAveCharWidth=%d\n",
    	tm.tmHeight, tm.tmAveCharWidth);


	CRect rectWin, rectClient;
	int cyBorder;
	GetWindowRect( rectWin );
	GetClientRect( rectClient );
	cyBorder = rectWin.bottom-rectWin.top - ( rectClient.bottom-rectClient.top);
    TRACE( "OnInitDialog: cyBorder=%d\n", cyBorder );                     
    
    DWORD lDlgBaseUnits;                             
    int cyHeight;
    lDlgBaseUnits = GetDialogBaseUnits();
    cyHeight = HIWORD( lDlgBaseUnits );
    TRACE( "OnInitDialog: cyHeight=%d\n", cyHeight );

	
	CMainFrame* pMainWnd;
	CRect rectMainClient, rectToolBar;
	pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->GetClientRect( rectMainClient);
	pMainWnd->ClientToScreen( rectMainClient );
	TRACE( "OnInitDialog: pMainWnd->GetClientRect rectMainClient.left=%d, .right=%d, top=%d, bottom=%d\n",
		rectMainClient.left,rectMainClient.right, rectMainClient.top, rectMainClient.bottom );
	
	GetWindowRect( rectDial );
	TRACE( "OnInitDialog: GetWindowRect rectDial.left=%d, .right=%d, top=%d, bottom=%d\n",
			rectDial.left,rectDial.right, rectDial.top, rectDial.bottom );
			
    rectDial.left = rectMainClient.left+2;
    rectDial.top  = rectMainClient.top + pMainWnd->cyGetToolBarHeight()+2;
    rectDial.bottom = m_LineCount*tm.tmHeight+rectDial.top + cyBorder;
    MoveWindow( rectDial ); 
    
	TRACE( "OnInitDialog: MoveWindow() rectDial.left=%d, .right=%d, top=%d, bottom=%d\n",
			rectDial.left,rectDial.right, rectDial.top, rectDial.bottom );
    
    								
	GetClientRect( rectDial );
	TRACE( "OnInitDialog: GetClientRect rectDial.left=%d, .right=%d, top=%d, bottom=%d\n",
			rectDial.left,rectDial.right, rectDial.top, rectDial.bottom );

	if( m_pJE == NULL ) return CDialog::OnInitDialog();
 	sText = m_pJE->GetMmdd();
	m_mm = sText.Left( 2 );
	m_dd = sText.Right( 2 );
   
    for( i=0; i<m_LineCount; i++ ) {
		if( i==m_LineCount-1)		
			m_acct[i] = m_pJE->GetCrAcct( );
		else
			m_acct[i] = m_pJE->GetAtAcct( i );
		GetDlgItem( idAcctControl[i] ) -> EnableWindow();
		GetDlgItem( idAcctControl[i] ) -> ShowWindow(SW_SHOW);

		pCH  = pChartList->FindChartAcct( m_acct[i] );
		if( pCH == NULL ) m_desc[i] = "** Invalid Acct **";
		else m_desc[i] = pCH->GetDesc();
		GetDlgItem( idDescControl[i] ) -> EnableWindow();
		GetDlgItem( idDescControl[i] ) -> ShowWindow(SW_SHOW);
		
		if( i==m_LineCount-1)
			m_amt[i] = "";
		else			
			m_amt[i] = m_pJE->GetAtAmt( i ).Get();			
		GetDlgItem( idAmtControl[i] ) -> EnableWindow();
		GetDlgItem( idAmtControl[i] ) -> ShowWindow(SW_SHOW);
	}
	m_jedesc[i-1] = m_pJE->GetDesc();
	GetDlgItem( idJedescControl[i-1] ) -> EnableWindow();
	GetDlgItem( idJedescControl[i-1] ) -> ShowWindow(SW_SHOW);



	
	TRACE( "CJEDialog::OnInitDialog() Leaving\n");
	
	return CDialog::OnInitDialog();  // return TRUE  unless you set the focus to a control
}  

void CJEDialog::OnSetFont( CFont* pFont )
{    
	TRACE("OnSetFont: Entering\n");
              
	TRACE("OnSetFont: Leaving\n");
}



void CJEDialog::OnChangeEdit3DD()
{
   
	CString sDD;
	CWnd* pDlgItem;
	
	pDlgItem = GetDlgItem( IDC_EDIT3_DD);
	pDlgItem->GetWindowText( sDD );
	TRACE("OnChangeEdit3DD:  sDD='%s'\n", sDD );  

    if( sDD.GetLength() == CX_DD ) {
		GetDlgItem( IDC_EDIT1_ACCT0 ) -> EnableWindow();
		GetDlgItem( IDC_EDIT1_ACCT0 ) -> ShowWindow(SW_SHOW);
		GotoDlgCtrl( GetDlgItem( IDC_EDIT1_ACCT0 ) );
    }		
    		
}	


void CJEDialog::OnChangeEdit1Acct()
{
	// TODO: Add your control notification handler code here 
	TRACE("OnChangeEdit1Acct: Entering\n");
	
	const MSG* pMsg;
	WPARAM wCurrentId, idCurrentDesc, idCurrentAmt;
	CString sAcct,desc;
	CChart* pCH;
	int nControlIdx;
	
	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam); 
	for( nControlIdx=0; nControlIdx<nControlCount; nControlIdx++) {
		if( idAcctControl[ nControlIdx ] == wCurrentId ) break;
	}
	nControlIdx = min( nControlIdx, nControlCount);
	idCurrentDesc = idDescControl[ nControlIdx ];
	idCurrentAmt  = idAmtControl[ nControlIdx ];
	
	GetDlgItem( wCurrentId ) -> GetWindowText( sAcct ); 
	m_chDlg.SetAcct( sAcct );
 
	TRACE("OnChangeEdit1Acct: sAcct='%s'\n", sAcct );
	 
	pCH  = pChartList->FindChartAcct( sAcct );
	if( pCH == NULL ) desc = "** Invalid Acct **";
	else desc = pCH->GetDesc();
	GetDlgItem( idCurrentDesc ) -> SetWindowText( desc );

	if( sAcct.GetLength() == CX_ACCT && m_nAcctLen != CX_ACCT) {
		GetDlgItem( idCurrentAmt ) -> EnableWindow();
		GetDlgItem( idCurrentAmt ) -> ShowWindow(SW_SHOW);
		GotoDlgCtrl( GetDlgItem( idCurrentAmt ) );
	}	
	m_nAcctLen = sAcct.GetLength();
	TRACE("OnChangeEdit1Acct: Leaving\n");
	
} 

int  CJEDialog::nDeciDigitCount( CString sAmt )
{
	//TRACE("nDeciDigitCount: sAmt='%s'", sAmt);

	int nLen, retval;
	char cLastChar, cPrevChar, cPrevM1Char;
	cLastChar='\0'; cPrevChar='\0'; cPrevM1Char='\0'; 
	
	nLen = sAmt.GetLength();
	if( nLen<=0 ) return 0;
	if( nLen>=1 ) cLastChar = (char) sAmt[ nLen-1 ];
	if( nLen>=2 ) cPrevChar = (char) sAmt[ nLen-2 ];
	if( nLen>=3 ) cPrevM1Char = (char) sAmt[ nLen-3 ];
	
	if( cPrevM1Char=='.' && isdigit(cPrevChar) && isdigit(cLastChar) ) retval=2;
	else if( cPrevChar=='.' && isdigit(cLastChar) ) retval=1;
	else retval=0;
	
	TRACE("nDeciDigitCount: retval=%d\n", retval);
	return retval;
}	
	
	
void CJEDialog::OnChangeEdit3Amt()
{
	// TODO: Add your control notification handler code here
   
    int nNextLine, nNextIdx, idCurJedesc, idNextJedesc;
	CWnd* pDlgItem;
	const MSG* pMsg;
	WPARAM wCurrentId, idNextAcct;
	CString sAmt, sAmtBS, sDesc;
	
	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam);
	pDlgItem = GetDlgItem( wCurrentId );
	//pDlgItem = FromHandle( (HWND)(pMsg->lParam) );
	pDlgItem -> GetWindowText( sAmt );
	
	TRACE("OnChangeEdit1Amt: sAmt='%s'\n", sAmt );   



	for( int nControlIdx=0; nControlIdx<nControlCount; nControlIdx++) {
		if( idAmtControl[ nControlIdx ] == wCurrentId ) break;
	}                                                        
	if( nControlIdx >= nControlCount ) nControlIdx--;
	idCurJedesc = idJedescControl[ nControlIdx ];
	if( nControlIdx+1 >= m_LineCount ) { 
		if( sAmt == "" )
			GetDlgItem( idCurJedesc ) -> EnableWindow( TRUE ); 
		else
			GetDlgItem( idCurJedesc ) -> EnableWindow( FALSE ); 
				
	}


	
	BOOL AmtBecame2DeciPlaces = (nDeciDigitCount(sAmt)==2 && m_nDeciDigitCount!=2 );
	m_nDeciDigitCount = nDeciDigitCount( sAmt );
	
	if( !AmtBecame2DeciPlaces ) return;
	
	 
	for(nControlIdx=0; nControlIdx<nControlCount; nControlIdx++) {
		if( idAmtControl[ nControlIdx ] == wCurrentId ) break;
	}
	nNextIdx = nControlIdx + 1;
	if( nNextIdx >= nControlCount ) nNextIdx = 0;
	nNextLine = nNextIdx + 1; 
	
	
    TRACE( "OnChangeEdit1Amt: nNextLine=%d, m_LineCount=%d\n", nNextLine, m_LineCount);
    if( nNextLine > m_LineCount ) {     //Does Window Need Resizing?? 
    	m_LineCount = nNextLine;
    	
    	// move m_je_descX to m_je_descX+1
    	// disable and hide X, enable and show X+1
		idCurJedesc = idJedescControl[ nControlIdx ];
		GetDlgItem( idCurJedesc ) -> GetWindowText( sDesc );
		GetDlgItem( idCurJedesc ) -> ShowWindow( SW_HIDE );
		GetDlgItem( idCurJedesc ) -> EnableWindow(FALSE);
 
		idNextJedesc = idJedescControl[ nNextIdx ];
		GetDlgItem( idNextJedesc ) -> SetWindowText( sDesc );
		GetDlgItem( idNextJedesc ) -> EnableWindow();
		GetDlgItem( idNextJedesc ) -> ShowWindow( SW_SHOW );  
 
     	CWindowDC dc( this );
		TEXTMETRIC tm;
		dc.GetTextMetrics( &tm ); 
		CRect rectDial;
		GetWindowRect( rectDial );
		rectDial.bottom += tm.tmHeight;
		MoveWindow( rectDial );
    
    }
	idNextAcct = idAcctControl[ nNextIdx ];
	GetDlgItem( idNextAcct ) -> EnableWindow();
	GetDlgItem( idNextAcct ) -> ShowWindow(SW_SHOW);
	NextDlgCtrl();
	//GotoDlgCtrl( GetDlgItem( idNextAcct ) );
	
	
	
}

void CJEDialog::OnSetfocusEdit1Acct()
{

	CWnd* pDlgItem;
	const MSG* pMsg;
	WPARAM wCurrentId;
	CString sAcct;
	
    TRACE( "CJEDialog::OnSetfocusEdit1Acct Entered\n" );
	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam);
	pDlgItem = GetDlgItem( wCurrentId );
	//pDlgItem = FromHandle( (HWND)(pMsg->lParam) );
	pDlgItem -> GetWindowText( sAcct );
	m_nAcctLen = sAcct.GetLength(); 
	
	m_chDlg.SetAcct( sAcct );
	m_chDlg.ShowWindow( SW_SHOWNA );


	
	TRACE("OnSetfocusEdit3Acct: wCurrentId=%d, sAcct='%s'\n", wCurrentId, sAcct);
	
}

void CJEDialog::OnKillfocusEdit1Acct()
{
	CWnd* pDlgItem;
	const MSG* pMsg;
	WPARAM wCurrentId;
	CString sAcct;
	CChart* pCH;
	
	TRACE("CJEDialog::OnKillfocusEdit1Acct Entered\n");
	//m_chDlg.ShowWindow( SW_HIDE );
	if( m_bActive == FALSE || m_bCancelPressed ) {
		TRACE("OnKillfocusEdit3Acct: m_bActive=%d, m_bCancelPressed=%d, exiting...\n",
			 m_bActive,m_bCancelPressed );
		return;
	}	

	
	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam);
	pDlgItem = GetDlgItem( wCurrentId );
	//pDlgItem = FromHandle( (HWND)(pMsg->lParam) );
	pDlgItem -> GetWindowText( sAcct );
	TRACE("OnKillfocusEdit3Acct: wCurrentId=%d, sAcct='%s'\n", wCurrentId, sAcct);
	
	pCH  = pChartList->FindChartAcct( sAcct );
	if( pCH == NULL ) {
		MessageBeep( 0xFFFFFFFF );
		pDlgItem -> SetFocus();
		return;
	}
	
}


void CJEDialog::OnSetfocusEdit3Amt()
{
  

	CWnd* pDlgItem;
	const MSG* pMsg;
	WPARAM wCurrentId;
	CString sAmt;

	m_chDlg.ShowWindow( SW_HIDE );

	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam);
	pDlgItem = GetDlgItem( wCurrentId );
	//pDlgItem = FromHandle( (HWND)(pMsg->lParam) );
	pDlgItem -> GetWindowText( sAmt );
	m_nDeciDigitCount = nDeciDigitCount( sAmt );  
	
	if( sAmt == "" ) {
		for( int nControlIdx=0; nControlIdx<nControlCount; nControlIdx++) {
			if( idAmtControl[ nControlIdx ] == wCurrentId ) break;
		}                                                        
		if( nControlIdx >= nControlCount ) nControlIdx--;
		int idCurJedesc = idJedescControl[ nControlIdx ];
		if( nControlIdx+1 >= m_LineCount ) {
			GetDlgItem( idCurJedesc ) -> ShowWindow( SW_SHOW );
			GetDlgItem( idCurJedesc ) -> EnableWindow( TRUE );
		}
	}	

	
	TRACE("OnSetfocusEdit3Amt: wCurrentId=%d, sAmt='%s'\n", wCurrentId, sAmt);

	
}

void CJEDialog::OnKillfocusEdit3Amt()
{
	//TRACE( "OnKillfocusEdit3Amt: Entered\n");
	
	CAmt amt;
	CWnd* pDlgItem;
	const MSG* pMsg;
	WPARAM wCurrentId;
	CString sAmt, sAmtBS, sDesc;

	
	if( m_bActive == FALSE || m_bCancelPressed ) {
		TRACE("OnKillfocusEdit3Amt: m_bActive=%d, m_bCancelPressed=%d, exiting...\n",
			 m_bActive,m_bCancelPressed );
		return;
	}	

	
	pMsg = GetCurrentMessage();
	wCurrentId = (int) LOWORD(pMsg->wParam);
	pDlgItem = GetDlgItem( wCurrentId );
	//pDlgItem = FromHandle( (HWND)(pMsg->lParam) );
	pDlgItem -> GetWindowText( sAmt );
	TRACE("OnKillfocusEdit3Amt: wCurrentId=%d, sAmt='%s'\n", wCurrentId, sAmt);
	
	if( sAmt=="" ) return;
		
	if( amt.Set( sAmt ) == FALSE ) {
		MessageBeep( 0xFFFFFFFF );
		pDlgItem -> SetFocus();
		return;
	}
	
	sAmt = amt.Get();
	TRACE("OnKillfocusEdit3Amt: amt.Get()='%s'\n", sAmt);
	pDlgItem -> SetWindowText( sAmt );
		
	
}

void CJEDialog::OnSetfocusEdit3Dd()
{
 
	CString sDD;
	CWnd* pDlgItem;

	m_chDlg.ShowWindow( SW_HIDE );
	
	pDlgItem = GetDlgItem( IDC_EDIT3_DD);
	pDlgItem->GetWindowText( sDD );
	m_OldItemValue = sDD;
	TRACE("OnSetfocus3DD:  m_OldItemValue='%s'\n", m_OldItemValue );  
	
}

void CJEDialog::OnKillfocusEdit3Dd()
{
	TRACE("OnKillfocusEdit3Dd: Entering\n");
	CString sDD;
	CWnd* pDlgItem;
	
	if( m_bActive == FALSE || m_bCancelPressed ) {
		TRACE("OnKillfocusEdit3Dd: m_bActive=%d, m_bCancelPressed=%d, exiting...\n",
			 m_bActive,m_bCancelPressed );
		return;
	}	
	pDlgItem = GetDlgItem( IDC_EDIT3_DD );
	pDlgItem->GetWindowText( sDD );
	if( sDD < "01" || sDD > "31" ) {
		MessageBeep( 0xFFFFFFFF );
		pDlgItem -> SetFocus();
	}	
   
	TRACE("OnKillfocusEdit3Dd: Leaving\n");
	
}

void CJEDialog::OnOK()
{
	TRACE("OnOK: Entered\n");
	CWnd* hFocus;
	WPARAM idControl;                    
	CString sAmt;
	
	hFocus = GetFocus();
	if( hFocus == NULL ) return;
	idControl = hFocus->GetDlgCtrlID();
	TRACE("OnOK: idControl=%d\n", idControl );
	
    // If enter was pressed while in a IDC_EDIT2_JE_DESCX control, EndDialog()
	for( int nControlIdx=1; nControlIdx<nControlCount; nControlIdx++) {
		if( idJedescControl[ nControlIdx ] == idControl ) {
			CDialog::OnOK();
			return;
		}		
	}
	
}	
void CJEDialog::OnCancel()
{
	TRACE("OnCancel: Entered\n");
	m_bCancelPressed = TRUE;
	
	m_chDlg.ShowWindow( SW_HIDE );
	
	CDialog::OnCancel();
	
}	
/////////////////////////////////////////////////////////////////////////////
// CDDEdit

CDDEdit::CDDEdit()
{
}

CDDEdit::~CDDEdit()
{
}

BEGIN_MESSAGE_MAP(CDDEdit, CEdit)
	//{{AFX_MSG_MAP(CDDEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDEdit message handlers


void CDDEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TRACE("CDDEdit::OnChar:  nChar=%d\n", nChar);  
	
	if( !(isdigit( nChar ) || nChar==8) ) {
    	MessageBeep( 0xFFFFFFFF );
    	return;
    }		

	
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
/////////////////////////////////////////////////////////////////////////////
// CAmtEdit

CAmtEdit::CAmtEdit()
{
}

CAmtEdit::~CAmtEdit()
{
}

BEGIN_MESSAGE_MAP(CAmtEdit, CEdit)
	//{{AFX_MSG_MAP(CAmtEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmtEdit message handlers


void CAmtEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TRACE("CAmtEdit::OnChar: nChar=%d\n", nChar );
    
    UINT ControlId;
    CString sAmt;
    CJEDialog* pDlg = (CJEDialog*)GetParent();
    
    GetWindowText( sAmt );
    ControlId = GetDlgCtrlID();  
    
    
	for( int nControlIdx=0; nControlIdx<nControlCount; nControlIdx++) {
		if( idAmtControl[ nControlIdx ] == ControlId ) break;
	}                                                        
	if( nControlIdx >= nControlCount ) nControlIdx--;
	int idCurJedesc = idJedescControl[ nControlIdx ];
	
    
    TRACE("CAmtEdit: ControlId=%d, sAmt='%s'\n", ControlId, sAmt );
	if( nChar == '\r' ) {
		if( sAmt != ""  &&  sAmt.Find('.') < 0 ) {
			pDlg -> SetDlgItemText(ControlId, sAmt + ".00" );
		} else {
			pDlg -> NextDlgCtrl();
	    }
	} else if( ! (isdigit( nChar ) || nChar=='-' || nChar=='.' || nChar=='\t' || nChar==8 ) ) {
    	MessageBeep( 0xFFFFFFFF );  
    	return;
    }
    		
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
 
void CJEDialog::OnActivateApp(BOOL bActive, HTASK hTask)
{
	m_bActive = bActive;
	CDialog::OnActivateApp(bActive, hTask);
	TRACE("CDialog::OnActivateApp: bActive=%d, hTask=%04X\n", bActive, hTask);
	
}

    
void CJEDialog::OnSetfocusEdit2JeDesc()
{
	TRACE( "CJEDialog::OnSetfocusEdit2JeDesc Entered\n");
	m_chDlg.ShowWindow( SW_HIDE );	
	
}
