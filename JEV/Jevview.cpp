// jevview.cpp : implementation of the CJevView class
//

#include "stdafx.h"
#include "jev.h"
#include "mainfrm.h"
//#include "jevdoc.h"
#include "jevview.h"

  

#include <afxdlgs.h>
#include "jedialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#define INVALIDATERANGE(beg,end) {for( int i = beg; i<=end; i++) InvalidateRecord( &dc, i);}

/////////////////////////////////////////////////////////////////////////////
// CJevView

IMPLEMENT_DYNCREATE(CJevView, CScrollView)

BEGIN_MESSAGE_MAP(CJevView, CScrollView)
	//{{AFX_MSG_MAP(CJevView)
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	ON_COMMAND(ID_EDIT_CHANGE, OnEditChange)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CHANGE, OnUpdateEditChange)
	ON_COMMAND(ID_EDIT_INSERT, OnEditInsert)
	ON_COMMAND(ID_EDIT_APPEND, OnEditAppend)
	ON_WM_MOUSEMOVE()
	ON_REGISTERED_MESSAGE(nFindMsg, FindReplaceHelper)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJevView construction/destruction

CJevView::CJevView()
{
	// TODO: add construction code here 
	TRACE( "Entering CJevView()\n" );
	m_njePrevActiveRecord = NULL;
	bMouseDown = FALSE;
	m_njePrevActiveRecord = 0; 
	m_njePrevLastSelectedRecord = 0;
	pFindReplaceDialog = NULL;   
	sFindString = "";
	TRACE( "Leaving CJevView()\n" );
}

CJevView::~CJevView()
{    
	if( pFindReplaceDialog != NULL ) {
		delete pFindReplaceDialog;
		pFindReplaceDialog = NULL;    
	}	

}

/////////////////////////////////////////////////////////////////////////////
// CJevView drawing

void CJevView::OnDraw(CDC* pDC)
{
	CJevDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    
	// TODO: add draw code for native data here   
	TRACE( "Entering OnDraw()\n");
	
	if( pDoc->m_JEArray.GetSize() == 0 ) return;
	
	int nyFirstLogicalDisplayLine, njeIndex, nSubAcct;

	CJournalEntry* pJE;

	
	CRect rectClip;
	pDC->GetClipBox( &rectClip );
	nyFirstLogicalDisplayLine = rectClip.top / m_cyChar;
	CRect rectDisplay = rectClip;
	pDoc->MapDispLineToNJE( nyFirstLogicalDisplayLine, njeIndex, nSubAcct );
	rectDisplay.top = (nyFirstLogicalDisplayLine - nSubAcct ) * m_cyChar;

	TRACE( "FirstDispLine=%d\n", nyFirstLogicalDisplayLine );					
	TRACE( "top=%d, bottom=%d, tmHeight=%d\n", rectClip.top, rectClip.bottom,
				m_cyChar );
	TRACE( "rectDisplay.top=%d\n", rectDisplay.top );			

	//CBrush brHighLite;
	//brHighLite.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT)); 
	
	int ar,lsr;
	BOOL bHighLite;
	ar = pDoc->njeGetActiveRecord();
	lsr = pDoc->njeGetLastSelectedRecord();

	while( njeIndex>=0 && rectDisplay.top < rectDisplay.bottom &&
				njeIndex<=pDoc->m_JEArray.GetUpperBound() ) {
	
		if( ar == njeIndex ) {
			bHighLite = TRUE;
		} else if( njeIndex > ar && njeIndex <= lsr ) {
			bHighLite = TRUE;
		} else if( njeIndex < ar && njeIndex >= lsr ) {
			bHighLite = TRUE;
		} else {
			bHighLite = FALSE;
		}

		pJE = pDoc->m_JEArray.GetAtJe( njeIndex );
		JETextOut( pDC, pJE, rectDisplay,  bHighLite );		
		njeIndex++;
	}						
	
	TRACE( "Leaving OnDraw()\n" );
} 
                                   
                                   
//////////////////////////////////////////////////////////////
// CJevView Draw One Journal Entry
//  Rect.top - the starting top for display, returns pointing to
//         the bottom of the journal entry, possibly several lines
//         down
//  Rect.bottom - bottom of the Invalid or Client Rect.  Stop when
//                top == bottom
//  bActiveRecord - TRUE if the background should be highlited                                   
//
void
CJevView::JETextOut( CDC* pDC, CJournalEntry* pJE, CRect& Rect,
					   BOOL bActiveRecord )
{ 
	//TRACE( "Entering JETextOut()\n" );
	const BOOL bRawView = theApp.bGetRawView();
	COLORREF crOldText = 0;
	COLORREF crOldBackground = 0;

	int nJEDisplayLines;
	CString sText, sText2;
	
	if( bRawView ) {
		nJEDisplayLines = 1;
	} else {
		nJEDisplayLines = pJE->GetSize() + 1;
	}
			
	
	if( bActiveRecord ) {
		CRect brushRect = Rect;
		brushRect.bottom = brushRect.top + m_cyChar * nJEDisplayLines; 
		TRACE( "brushRect.top=%d, brushRect.bottom=%d\n", brushRect.top, 
				brushRect.bottom);

		CBrush brHighLite;
		brHighLite.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT)); 
				
		crOldBackground = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		crOldText = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));

		pDC->FillRect( &brushRect , &brHighLite );	
	}	
	
	if( bRawView ) {
		sText = (CString) *pJE;
		pDC->TextOut( 0, Rect.top, sText );
		Rect.top += m_cyChar;
	}	 else { 
		CChart* pCH;
		sText = pJE->GetMmdd();
		sText2 = sText.Left(2) + "/" + sText.Right(2);
		pDC->TextOut( NX_MMDD*m_cxChar, Rect.top, sText2 );
	
		for( int i=0; i<pJE->GetSize() && Rect.top < Rect.bottom; i++ ){
			sText = pJE->GetAtAcct(i);
			pDC->TextOut( NX_ACCT*m_cxChar, Rect.top, sText );
			
			//sText = "Account Description"; 
			pCH = pChartList->FindChartAcct( sText ); 
			//afxDump << pCH;
			if( pCH == NULL ) sText2 = "** Invalid Description **";
			else sText2 = pCH->GetDesc()  +  "";
			pDC->TextOut( NX_CHDESC*m_cxChar, Rect.top, sText2 );
			
			sText = pJE->GetAtAmt(i).Get();
			pDC->SetTextAlign( TA_RIGHT );
			pDC->TextOut( NX_AMT*m_cxChar, Rect.top, sText);
			pDC->SetTextAlign( TA_LEFT );
			
			Rect.top += m_cyChar;
		} // for

		if( Rect.top < Rect.bottom ) { 
			sText = pJE->GetCrAcct();
			pDC->TextOut( NX_ACCT*m_cxChar, Rect.top, sText );

			pCH = pChartList->FindChartAcct( sText );
			if( pCH == NULL ) sText2 = "** Invalid Description **";
			else sText2 = pCH->GetDesc()  +  "";
			pDC->TextOut( NX_CHDESC*m_cxChar, Rect.top, sText2 );

			
			pDC->TextOut( NX_DESC*m_cxChar, Rect.top, pJE->GetDesc() );			
			Rect.top += m_cyChar;
			
		}
		
	} // else
				
	
			
	if( bActiveRecord ) {
		pDC->SetBkColor( crOldBackground );
		pDC->SetTextColor( crOldText );
	}	 
	
	//TRACE( "Leaving JETextOut()\n" );
}	
//////////////////////////////////////////////////////////////
// CJevView OnPrepareDC
void CJevView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo )
{
	CScrollView::OnPrepareDC( pDC, pInfo );
}	


/////////////////////////////////////////////////////////////////////////////
// CJevView printing

BOOL CJevView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CScrollView preparation
	return CScrollView::OnPreparePrinting(pInfo);
}

void CJevView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CScrollView begin printing.
	CScrollView::OnBeginPrinting(pDC, pInfo);
}

void CJevView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CScrollView end printing
	CScrollView::OnEndPrinting(pDC, pInfo);
}  


void CJevView::OnInitialUpdate()
{
	TRACE( "Entering OnInitialUpdate()\n" );

	CJevDoc* pDoc = GetDocument();                  
	UpdateScrollSizes();
	InvalidateRect( NULL );

	TRACE( "Leaving OnInitialUpdate()\n" );
}

void CJevView::UpdateScrollSizes()
{
	TRACE( "Entering UpdateScrollSizes()\n" );
	CJevDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc ); 
	
	TRACE( "m_cyChar=%d m_cyClient=%d\n", m_cyChar, m_cyClient );
	
	m_njePrevRecordCount = pDoc->m_JEArray.GetSize(); 
	m_njePrevActiveRecord = pDoc->njeGetActiveRecord();
	m_njePrevLastSelectedRecord = pDoc->njeGetLastSelectedRecord();
	
	CSize sizeTotal( m_cxChar * JE_VIEW_WIDTH,
					 m_cyChar * pDoc->GetTotalDisplayLines() );
	
	CSize sizePage( m_cxChar * JE_VIEW_WIDTH / 5,
					max( m_cyChar, ((m_cyClient/m_cyChar)-1)*m_cyChar));

	CSize sizeLine( m_cxChar * JE_VIEW_WIDTH / 20, m_cyChar );
					
	SetScrollSizes( MM_TEXT, sizeTotal, sizePage, sizeLine );									
	
	TRACE( "Leaving UpdateScrollSizes()\n" );
}	 
	   
void CJevView::OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint )
{
	TRACE( "Entering OnUpdate\n" ); 
	int lsr, plsr, par, ar;
	CJevDoc* pDoc = GetDocument();        

	CClientDC dc( this );
	OnPrepareDC( &dc );                         
	if( pHint != 0 && pHint->IsKindOf(RUNTIME_CLASS(CUpdateHint)) ) {
		CUpdateHint* pCUpdateHint = (CUpdateHint*) pHint;
		switch( lHint )
		{
			TRACE("OnUpdate: lHint-'%d'\n", (int)lHint );
			case HINT_DELETE_ACTIVE_RECORD:
				UpdateScrollSizes();
				InvalidateRecord( &dc, pDoc->njeGetActiveRecord(), 
					pCUpdateHint->iHint1);
				break;
				
			case HINT_INSERT_ACTIVE_RECORD:
				//InvalidateRecord( &dc, m_posPrevActiveRecord );
				UpdateScrollSizes();
				//InvalidateRecord( &dc, pDoc->posGetActiveRecord() );
				m_njePrevLastSelectedRecord = pDoc -> njeGetLastSelectedRecord();
				
				Invalidate();
				break;

			case HINT_CHANGE_ACTIVE_RECORD:
				UpdateScrollSizes();				
				InvalidateRecord( &dc, pDoc->njeGetActiveRecord() );
				break;
				
			case HINT_NAVIGATION_KEY:
				lsr = pDoc -> njeGetLastSelectedRecord();
				par = m_njePrevActiveRecord;
				ar = pDoc -> njeGetActiveRecord();
				TRACE("lsr=%d, par=%d\n", lsr,par);
				if( lsr < par ) {
					INVALIDATERANGE( lsr, par-1 );
				} else if( lsr > par ) {
					INVALIDATERANGE( par+1, lsr);
				}	


				if( ar != par ) {
					// Previous
        			InvalidateRecord( &dc, par ); 
        
        			// Newly actived
        			InvalidateRecord( &dc, ar );
        
					m_njePrevActiveRecord = ar;
				}

        		break;
			
			case HINT_LAST_SELECTED_RECORD:
				plsr = m_njePrevLastSelectedRecord;
				lsr = pDoc -> njeGetLastSelectedRecord();
				ar = pDoc -> njeGetActiveRecord();
				
				if( plsr > ar ) {
					if( lsr > plsr ) { INVALIDATERANGE( plsr+1, lsr);
					} else if( lsr >= ar && lsr < plsr ) { INVALIDATERANGE( lsr+1, plsr );
					} else if( lsr < ar ) { INVALIDATERANGE( lsr+1, plsr );
					} else TRACE( "plsr>ar:  no Invalidate Records selected!\n");

				} else if( plsr < ar ) {
					if( lsr < plsr ) { INVALIDATERANGE( lsr, plsr-1 );
					} else if( lsr > plsr && lsr <= ar ) { INVALIDATERANGE( plsr, lsr-1 );
					} else if( lsr > ar ) { INVALIDATERANGE( plsr, lsr );
					} else TRACE( "plsr<ar:  no Invalidate Records selected!\n");
				} else if( plsr == ar) {
					if( lsr < ar ) { INVALIDATERANGE( lsr, ar-1 );
					} else if( lsr > ar ) { INVALIDATERANGE( ar+1, lsr );
					} else TRACE(" plsr == ar: no Invalidate Records Selectec!\n");
				}



				m_njePrevLastSelectedRecord = pDoc -> njeGetLastSelectedRecord();
				
				break;
	
			default:
				TRACE("OnUpdate:  Unexpected Hint-'%d'\n", (int)lHint );
				break;
		}
		//return;
	}
	
	
	// Get the first and last record index displayed inthe Client area
	//
	int nyFirstLogicalDisplayLine, nyLastLogicalDisplayLine;
	CRect rectClient;
	GetClientRect( &rectClient );
	dc.DPtoLP( &rectClient );
	
	nyFirstLogicalDisplayLine = rectClient.top / m_cyChar;
	nyLastLogicalDisplayLine  = (rectClient.bottom-1) / m_cyChar;
 
	TRACE( "FirstRec=%d, LastRec=%d\n", nyFirstLogicalDisplayLine,
					nyLastLogicalDisplayLine );					
    TRACE( "top=%d, bottom=%d\n", rectClient.top, rectClient.bottom);
    
    // Scroll, if necessary, so that the selected row is visible
    POINT pt;
    pt.x = 0;
    pt.y = 0;
    BOOL bNeedToScroll = TRUE; 
    
    int nyActiveRecordDispLine, njelActiveRecord, nSubAcct;
    int NJE = pDoc->njeGetActiveRecord();
    pDoc->MapNJEToDispLine( NJE, nyActiveRecordDispLine, 
    					 nSubAcct );
    TRACE( "nyActiveRecordDispLine=%d, njelActiveRecord=%d, m_njelPrevActiveRecord=%d\n", nyActiveRecordDispLine,
    		njelActiveRecord, m_njePrevActiveRecord );
    			
    if( njelActiveRecord < 0 ) {
    	bNeedToScroll = FALSE;
    } else if( nyActiveRecordDispLine < nyFirstLogicalDisplayLine ) {
    	pt.y = nyActiveRecordDispLine * m_cyChar;
    } else if( nyActiveRecordDispLine > nyLastLogicalDisplayLine ) {
    	pt.y = max( 0, (nyActiveRecordDispLine+1)*m_cyChar - rectClient.Height() );
    } else { 
    	bNeedToScroll = FALSE;
    }
    	                
    TRACE( "bNeedToScroll=%d, pt.y=%d\n", bNeedToScroll, pt.y );
    	                
    if( bNeedToScroll ) { 
    	TRACE( "OnUpdate: Scrolling\n");
    	ScrollToDevicePosition( pt );
    	OnPrepareDC( &dc );
    } 
    
	TRACE( "Leaving OnUpdate\n" );
}
		   
void
CJevView::InvalidateRecord(CDC* pDC, int NJE, int nSubAcctOverRide )
{
		int nyLine, nSubAcct;
		if( NJE < 0 ) return;
        GetDocument()->MapNJEToDispLine( NJE, nyLine, nSubAcct);
        if( nSubAcctOverRide != 0) nSubAcct += nSubAcctOverRide;
        CRect rectInvalid( 0, nyLine * m_cyChar,
        					pDC->GetDeviceCaps( HORZRES ),
        					(nyLine+nSubAcct) * m_cyChar);
        pDC->LPtoDP( &rectInvalid );
        InvalidateRect( &rectInvalid );
}	
/////////////////////////////////////////////////////////////////////////////
// CJevView diagnostics

#ifdef _DEBUG
void CJevView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CJevView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CJevDoc* CJevView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJevDoc)));
	return (CJevDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJevView message handlers

void CJevView::OnSize(UINT nType, int cx, int cy)
{
	TRACE( "Entering OnSize()\n" );
	
	
	// TODO: Add your message handler code here 
	
	m_cxClient = cx;
	m_cyClient = cy;
	TRACE( "cxClient=%d, cyClient=%d\n", cx, cy );
	
	CClientDC dc( this );
	
    char szFaceName[30];
    dc.GetTextFace( sizeof szFaceName, szFaceName );
    TRACE("OnSize: FaceName='%s'\n", szFaceName );
                     

	TEXTMETRIC tm;
	dc.GetTextMetrics( &tm );
    m_cyChar = tm.tmHeight; 
    m_cxChar = tm.tmAveCharWidth; 
    TRACE("OnSize: tmHeight=%d, tmAveCharWidth=%d",
    	tm.tmHeight, tm.tmAveCharWidth);
    
    
    
	UpdateScrollSizes();
	CScrollView::OnSize(nType, cx, cy);
	
	CRect rectClient;
	GetClientRect( rectClient );
	TRACE( "OnSize: rectClient.left=%d, .right=%d, top=%d, bottom=%d\n",
			rectClient.left,rectClient.right, rectClient.top, rectClient.bottom );
	ClientToScreen( rectClient );
	TRACE( "OnSize: Screen rectClient.left=%d, .right=%d, top=%d, bottom=%d\n",
			rectClient.left,rectClient.right, rectClient.top, rectClient.bottom );
			
	TRACE( "Leaving OnSize()\n" );
	
}

void CJevView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CJevDoc* pDoc = GetDocument();
	switch( nChar )
	{
		case VK_HOME:
			pDoc->SetActiveHomeRecord();
			SendMessage( WM_VSCROLL, SB_TOP );
			break;
		case VK_END:
			pDoc->SetActiveEndRecord();
			SendMessage( WM_VSCROLL, SB_BOTTOM );
			break;
		case VK_PRIOR:
			SendMessage( WM_VSCROLL, SB_PAGEUP );
			break;
		case VK_NEXT:
			SendMessage( WM_VSCROLL, SB_PAGEDOWN );
			break;
		case VK_UP:
			pDoc->SetActivePrevRecord();
			break;
		case VK_DOWN:
			pDoc->SetActiveNextRecord();
			break;
		case VK_DELETE:
			pDoc->DeleteActiveRecord();
			break;				
		default:
			CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
	}		
}

void CJevView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	TRACE( "Entering OnLButtonDown()\n" );
	CJevDoc* pDoc = GetDocument();
	CClientDC dc( this );
	OnPrepareDC( &dc );
	dc.DPtoLP( &point );
	CRect rect( point, CSize( 1,1 ));
	
	int nyNewActiveDispLine, njeNewActiveRecord, nSubAcct;

	bMouseDown = TRUE;
	
	nyNewActiveDispLine = rect.top / m_cyChar; 
	TRACE( "top=%d, nyNewActiveDispLine=%d\n", rect.top, nyNewActiveDispLine );
	
	pDoc->MapDispLineToNJE( nyNewActiveDispLine, njeNewActiveRecord, nSubAcct );
	if( njeNewActiveRecord < pDoc->m_JEArray.GetSize() && njeNewActiveRecord >=0 ) {
		pDoc->SetActiveRecord( njeNewActiveRecord );
		pDoc->SetLastSelectedRecord( njeNewActiveRecord );

	}  
	
	CScrollView::OnLButtonDown(nFlags, point);
	TRACE( "Leaving OnLButtonDown()\n" );
}


void CJevView::OnEditCopy()
{
	
	TRACE( "Entering OnEditCopy()\n" );
	
	CJournalEntry* pJE;
	CJevDoc* pDoc;
	CString sText;
	
	pDoc = GetDocument();
	int NJE, ar, lsr, njeBegin, njeEnd, i;
	NJE = pDoc->njeGetActiveRecord();
	lsr = pDoc -> njeGetLastSelectedRecord();
	ar = pDoc -> njeGetActiveRecord();
	TRACE("lsr=%d, ar=%d\n", lsr, ar);
	if( lsr <= ar ) {
		njeBegin = lsr;
		njeEnd = ar;
	} else if( lsr > ar ) {
		njeBegin = ar;
		njeEnd = lsr;
	}	

	sText = "";
	for( i=njeBegin; i<=njeEnd; i++ ) {
		pJE = pDoc->m_JEArray.GetAtJe( i ); 
		sText += (CString) *pJE + "\r\n";
	}
	TRACE( "OnEditCopy: \n%s\n", sText );
	
	HGLOBAL hGlobalMemory = GlobalAlloc( GHND, (DWORD) sText.GetLength() + 1 );
	char FAR* lpGlobalMemory = (char FAR*) GlobalLock( hGlobalMemory );
	for( int n=0; n<sText.GetLength(); n++ ) {
		*lpGlobalMemory++ = sText[n];
	}	
	GlobalUnlock( hGlobalMemory );
	
	OpenClipboard();
	EmptyClipboard();
	SetClipboardData( CF_TEXT, hGlobalMemory );
	CloseClipboard();
			
	TRACE( "Leaving OnEditCopy()\n" );
	
}

void CJevView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	//TRACE( "Entering OnUpdateEditCopy\n" );
	
	if( GetDocument()->njeGetActiveRecord() >= 0) {
		pCmdUI->Enable( TRUE );
	} else {
		pCmdUI->Enable( FALSE );
	}	
		
	//TRACE( "Leaving OnUpdateEditCopy\n" );
	
}

 void CJevView::OnEditCut()
{                                    
	TRACE( "Entering OnEditCut()\n" );
	
	OnEditCopy();
	GetDocument()->DeleteSelectedRecords();
	
	TRACE( "Leaving OnEditCut()\n" );
	
}

void CJevView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	if( GetDocument()->njeGetActiveRecord() >= 0 ) {
		pCmdUI->Enable( TRUE );
	} else {
		pCmdUI->Enable( FALSE );
	}	
	
	
}

void CJevView::OnEditPaste()
{
	// TODO: Add your command handler code here
	TRACE( "Entering OnEditPaste()\n" );
	
	CJournalEntry JE;
	CJevDoc* pDoc;
	CString sText;

	
	pDoc = GetDocument();
	
	OpenClipboard();
	HGLOBAL hClipMemory = GetClipboardData( CF_TEXT );
	if( hClipMemory == NULL ) {
		TRACE( "OnEditPaste: GetClipboardData == NULL, Clip board empty\n" );
		CloseClipboard();
		return;
	}	
	
	HGLOBAL hGlobalMemory = GlobalAlloc( GHND, GlobalSize( hClipMemory ) );
	if( hGlobalMemory == NULL ) {
		TRACE( "OnEditPaste: GlobalAlloc on Clipboard Data Failed\n" );
		CloseClipboard();
		return;
	}	
		
	LPSTR lpClipMemory = (LPSTR) GlobalLock( hClipMemory );
	LPSTR lpGlobalMemory = (LPSTR) GlobalLock( hGlobalMemory );
	lstrcpy( lpGlobalMemory, lpClipMemory );
	GlobalUnlock( hClipMemory );	
	CloseClipboard();
	
/*	if( JE.Convert( lpGlobalMemory ) ) {
		pDoc->InsertAfterActiveRecord( JE );
	} else {
		TRACE( "OnEditPaste(): Paste failed.  Invalid Journal Entry Record\n");
	}
*/
	CString sClip, jeRecord;
	int retcode, i;

	sClip = lpGlobalMemory;
	while( (i = sClip.Find( "\r\n" ) ) >= 0 ) {
		jeRecord = sClip.Left( i );
		TRACE("OnEditPaste: jeRecord='%s'\n", jeRecord );
		retcode = JE.Convert( jeRecord );
		TRACE("OnEditPaste: JE.Convert() retcode=%d\n", retcode);
		if(retcode == 0) {
			TRACE( "OnEditPaste(): Paste failed.  Invalide Journal Entry Record\n");
			break;
		} else {
			pDoc->InsertAfterActiveRecord( JE );
		}
		sClip = sClip.Mid( i+2 );
	}
	
	GlobalUnlock( hGlobalMemory ); 
	
    CUpdateHint hint;
	pDoc->UpdateAllViews( NULL, HINT_INSERT_ACTIVE_RECORD, &hint );

			
	TRACE( "Leaving OnEditPaste()\n" );
	
}

void CJevView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( ::IsClipboardFormatAvailable( CF_TEXT ) );	
}

void CJevView::OnEditFind()
{
	if( pFindReplaceDialog ) return;
	
	pFindReplaceDialog = new CFindReplaceDialog();
	bIsReplaceDialog = FALSE;
	pFindReplaceDialog->Create( TRUE, sFindString, NULL, FR_DOWN | FR_HIDEWHOLEWORD, this );
	pFindReplaceDialog->SendMessage( WM_INITDIALOG );

}
LONG CJevView::FindReplaceHelper( UINT wParam, LONG lParam )
{
	BOOL bFindResult;
	CMainFrame* pMainFrame;
	pMainFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;


	
	CFindReplaceDialog* pDialogBox = CFindReplaceDialog::GetNotifier(lParam);
	
	if( pDialogBox->IsTerminating() ) { 
		sFindString = pDialogBox->GetFindString();
		delete pFindReplaceDialog;
		pFindReplaceDialog = NULL; 
		pMainFrame->SetStatusBarText( "Ready" );
		return 0;
	}
	CJevDoc* pDoc = GetDocument();
	

	if( pDialogBox->FindNext() ) {
		TRACE("FindReplaceHelper: FindString='%s'\n", pDialogBox->GetFindString() );
	}

	bFindResult = pDoc->Find( pDialogBox->GetFindString(), pDialogBox->MatchCase(), 
					pDialogBox->MatchWholeWord(), pDialogBox->SearchDown() );
    if( bFindResult == FALSE ) MessageBeep(-1);
	return (LONG) bFindResult;
}			
void CJevView::OnUpdateEditFind(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(pFindReplaceDialog == NULL );
	
}

void CJevView::OnEditChange()
{
	TRACE("OnEditChange(): Entering\n");
	CJEDialog jedlg( this );

	CJournalEntry* pJE;
	CJevDoc* pDoc; 

	pDoc = GetDocument();
	int NJE = pDoc->njeGetActiveRecord();
	pJE = pDoc->m_JEArray.GetAtJe( NJE );
    jedlg.m_pJE = pJE;
    
	int nResult = jedlg.DoModal();   
	
	if( nResult == IDOK ) {
		TRACE( "OnEditChange(): jedlg returned IDOK\n");
	    CUpdateHint hint;
		pDoc->UpdateAllViews( NULL, HINT_CHANGE_ACTIVE_RECORD, &hint );

	} else if( nResult == IDCANCEL ) {
		TRACE( "OnEditChange(): jedlg returned IDCANCEL\n");
	}	
	
	
	TRACE("OnEditChange(): Leaving\n");
	
}

void CJevView::OnUpdateEditChange(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if( GetDocument()->njeGetActiveRecord() >= 0 ) {
		pCmdUI->Enable( TRUE );
	} else {
		pCmdUI->Enable( FALSE );
	}	
	
}

void CJevView::OnEditAppend()
{
	TRACE("OnEditAppend(): Entering\n");
	CJEDialog jedlg( this );
	CJevDoc* pDoc; 

	pDoc = GetDocument();
    jedlg.m_pJE = NULL;
    jedlg.m_mm = pDoc->GetTitle();
	int nResult = jedlg.DoModal();   
	
	if( nResult == IDOK ) {
		TRACE( "OnEditInsert(): jedlg returned IDOK\n");
		
		pDoc->InsertAfterActiveRecord( *jedlg.m_pJE );
		delete jedlg.m_pJE;
		
	} else if( nResult == IDCANCEL ) {
		TRACE( "OnEditAppend(): jedlg returned IDCANCEL\n");
	}	
	
	
	TRACE("OnEditAppend(): Leaving\n");

	
}

void CJevView::OnEditInsert()
{
	TRACE("OnEditInsert(): Entering\n");
	CJEDialog jedlg( this );
	
	CJevDoc* pDoc; 

	pDoc = GetDocument();
    jedlg.m_pJE = NULL;
    jedlg.m_mm = pDoc->GetTitle();
	int nResult = jedlg.DoModal();   
	
	if( nResult == IDOK ) {
		TRACE( "OnEditInsert(): jedlg returned IDOK\n");
		
		pDoc->InsertBeforeActiveRecord( *jedlg.m_pJE );
		delete jedlg.m_pJE;
		
		
	} else if( nResult == IDCANCEL ) {
		TRACE( "OnEditInsert(): jedlg returned IDCANCEL\n");
	}	
	
	
	TRACE("OnEditInsert(): Leaving\n");

}

void CJevView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( bMouseDown == FALSE ) return;

	TRACE( "Entering OnMouseMove()\n" );

	
	CJevDoc* pDoc = GetDocument();
	CClientDC dc( this );
	OnPrepareDC( &dc );
	dc.DPtoLP( &point );
	CRect rect( point, CSize( 1,1 ));
	
	int nyNewActiveDispLine, njeLastSelectedRecord, nSubAcct;
	
	nyNewActiveDispLine = rect.top / m_cyChar; 
	TRACE( "top=%d, nyNewActiveDispLine=%d\n", rect.top, nyNewActiveDispLine );
	
	pDoc->MapDispLineToNJE( nyNewActiveDispLine, njeLastSelectedRecord, nSubAcct );
	if( njeLastSelectedRecord < pDoc->m_JEArray.GetSize() && njeLastSelectedRecord >=0 ) {
		TRACE("LastSelectedRecord=%d\n" ,njeLastSelectedRecord);
		if( m_njePrevLastSelectedRecord != njeLastSelectedRecord) {
			pDoc->SetLastSelectedRecord( njeLastSelectedRecord );
			m_njePrevLastSelectedRecord = njeLastSelectedRecord;
		}
	}  
	

	
	CScrollView::OnMouseMove(nFlags, point);
	TRACE( "Leaving OnMouseMove()\n" );
}

void CJevView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	TRACE("OnLButtonUp() Entered\n");
	bMouseDown = FALSE;
	CScrollView::OnLButtonUp(nFlags, point);
	TRACE("OnLButtonUp() Exited\n");
}

void CJevView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView )
{
	TRACE("CJevView::OnActivateView: Entered\n");
	CJevApp* pJevApp =  ((CJevApp*) AfxGetApp());
	pJevApp -> m_pActiveJevDoc = GetDocument();
}
