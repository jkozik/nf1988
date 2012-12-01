// jevdoc.cpp : implementation of the CJevDoc class
//

#include "stdafx.h"
#include "mainfrm.h"
#include "jev.h"

//#include "jevdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////
// CUpdateHint
//
IMPLEMENT_DYNAMIC(CUpdateHint, CObject)
CUpdateHint::CUpdateHint()
{
}

/////////////////////////////////////////////////////////////////////////////
// CJevDoc

IMPLEMENT_DYNCREATE(CJevDoc, CDocument)

BEGIN_MESSAGE_MAP(CJevDoc, CDocument)
	//{{AFX_MSG_MAP(CJevDoc)
	ON_COMMAND(ID_EDIT_CHANGE, OnEditChange)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CHANGE, OnUpdateEditChange)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJevDoc construction/destruction

CJevDoc::CJevDoc()
{
	// TODO: add one-time construction code here
	m_njeActiveRecord = -1;
}

CJevDoc::~CJevDoc()
{
}

BOOL CJevDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CJevDoc serialization

void CJevDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here 

		CFile* fp = ar.GetFile();
		CString sFile = fp->GetFileName();

		TRACE("Serialize: sFile='%s'\n",sFile);
		m_JEArray.WriteOut( ar.GetFile() );
	}
	else
	{
		// TODO: add loading code here  
		m_JEArray.LoadIn( ar.GetFile() );
		m_njeActiveRecord = 0;
		m_njeLastSelectedRecord = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CJevDoc diagnostics

#ifdef _DEBUG
void CJevDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJevDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJevDoc commands


/////////////////////////////////////////////////////////////////////
//  Get/Set Active Record Operations
//  - move the active record +/- 1 or to HOME/END
//  - set to a POSITION or an Index
//  - if any problem, POSITION is set to a reasonible default
//    such as leaving the POSITION unchanged or setting it to NULL
//
void
CJevDoc::SetActiveRecord( int njeIndex )
{
	ASSERT_VALID( this );
	m_njeActiveRecord = njeIndex ;
    CUpdateHint hint;
	UpdateAllViews( NULL, HINT_NAVIGATION_KEY, &hint );

}

int
CJevDoc::njeGetActiveRecord() const
{
	ASSERT_VALID( this ); 
	return m_njeActiveRecord;	
}
void
CJevDoc::SetLastSelectedRecord( int njeIndex )
{
	ASSERT_VALID( this );
	m_njeLastSelectedRecord = njeIndex ;
    //if( m_njeLastSelectedRecord != m_njeActiveRecord) {
		CUpdateHint hint;
		UpdateAllViews( NULL, HINT_LAST_SELECTED_RECORD, &hint );
	//}
	

}

int
CJevDoc::njeGetLastSelectedRecord() const
{
	ASSERT_VALID( this ); 
	return m_njeLastSelectedRecord;	
}

void
CJevDoc::SetActiveNextRecord()
{
	ASSERT_VALID( this );
	m_njeActiveRecord = min( m_njeActiveRecord+1, 
						m_JEArray.GetUpperBound() );
	m_njeLastSelectedRecord = m_njeActiveRecord;
    CUpdateHint hint;
	UpdateAllViews( NULL, HINT_NAVIGATION_KEY, &hint );
} 

void
CJevDoc::DeleteActiveRecord()
{
	ASSERT_VALID( this );
	int njeOld;               
	CJournalEntry* pJE;
	int nSubAcct;
	                                
	if( m_JEArray.GetSize()==0 ) return; 
	
	pJE = m_JEArray.GetAtJe( m_njeActiveRecord ); 
	nSubAcct = pJE->GetSize() + 1;
	
	njeOld = m_njeActiveRecord;	                                
	if( m_JEArray.GetSize() == 1 ) {
		m_njeActiveRecord = -1;
	} else if( m_njeActiveRecord == m_JEArray.GetUpperBound() ) { 
		m_njeActiveRecord--;
	} else {
		//m_njeActiveRecord++;
	} 
	m_njeLastSelectedRecord = m_njeActiveRecord;
	m_JEArray.RemoveAt( njeOld );
	SetModifiedFlag();
	delete pJE;
    CUpdateHint hint; 
    hint.iHint1 = nSubAcct;
	UpdateAllViews( NULL, HINT_DELETE_ACTIVE_RECORD, &hint );
}			
void
CJevDoc::DeleteSelectedRecords()
{
	ASSERT_VALID( this );
	int njeBegin,njeEnd,njeUpperBound,nSubAcct,njeIdx;               
	CJournalEntry* pJE;

	                                
	if( m_JEArray.GetSize()==0 ) return; 
	
	if( m_njeActiveRecord <= m_njeLastSelectedRecord ) {
		njeBegin = m_njeActiveRecord;
		njeEnd = m_njeLastSelectedRecord;
	} else {
		njeEnd = m_njeActiveRecord;
		njeBegin = m_njeLastSelectedRecord;
	}

	nSubAcct=0;
	for( njeIdx=njeBegin; njeIdx<=njeEnd; njeIdx++ ){
		pJE = m_JEArray.GetAtJe( njeBegin ); 
		nSubAcct += pJE->GetSize() + 1;
		m_JEArray.RemoveAt( njeBegin );
		delete pJE;
	}
	SetModifiedFlag();
	
                            
	if( m_JEArray.GetSize() == njeEnd-njeBegin+1 ) {
		m_njeActiveRecord = -1;
	} else if( njeEnd == njeUpperBound ) { 
		m_njeActiveRecord -= njeEnd - njeBegin - 1;
	} 

	m_njeLastSelectedRecord = m_njeActiveRecord;
	
    CUpdateHint hint; 
    hint.iHint1 = nSubAcct;
	UpdateAllViews( NULL, HINT_DELETE_ACTIVE_RECORD, &hint );
}			
		
void
CJevDoc::InsertAfterActiveRecord(CJournalEntry& JE)
{
	ASSERT_VALID( this );
	int NJE;

	NJE = m_njeActiveRecord;
	if( m_JEArray.GetSize()==0 ) {
		m_njeActiveRecord = m_JEArray.Add( new CJournalEntry( JE ) );
		SetModifiedFlag();
	} else {
		m_JEArray.InsertAt( NJE+1, new CJournalEntry( JE ) );
		m_njeActiveRecord = NJE+1;
	}
	m_njeLastSelectedRecord = m_njeActiveRecord;
    CUpdateHint hint;
	UpdateAllViews( NULL, HINT_INSERT_ACTIVE_RECORD, &hint );

		
} 



void
CJevDoc::InsertBeforeActiveRecord(CJournalEntry& JE)
{
	ASSERT_VALID( this );
	int NJE;

	NJE = m_njeActiveRecord;
	if( m_JEArray.GetSize()==0 ) {
		m_njeActiveRecord = m_JEArray.Add( new CJournalEntry( JE ) );
	} else {
		m_JEArray.InsertAt( NJE, new CJournalEntry( JE ) );
		m_njeActiveRecord = NJE;
	}
	SetModifiedFlag();
	m_njeLastSelectedRecord = m_njeActiveRecord;
    CUpdateHint hint;
	UpdateAllViews( NULL, HINT_INSERT_ACTIVE_RECORD, &hint );

		
}





void
CJevDoc::SetActivePrevRecord()
{
	ASSERT_VALID( this );
	m_njeActiveRecord = max( 0, m_njeActiveRecord-1 );	
	m_njeLastSelectedRecord = m_njeActiveRecord;
    CUpdateHint hint;
	UpdateAllViews( NULL, HINT_NAVIGATION_KEY, &hint );

}			

void
CJevDoc::SetActiveHomeRecord()
{
	ASSERT_VALID( this );
	m_njeActiveRecord = 0;
	m_njeLastSelectedRecord = m_njeActiveRecord;
    CUpdateHint hint;
	UpdateAllViews( NULL, HINT_NAVIGATION_KEY, &hint );
	
} 

void
CJevDoc::SetActiveEndRecord()
{
	ASSERT_VALID( this );
	m_njeActiveRecord = m_JEArray.GetUpperBound( );
	m_njeLastSelectedRecord = m_njeActiveRecord;
    CUpdateHint hint;
	UpdateAllViews( NULL, HINT_NAVIGATION_KEY, &hint );

}

/////////////////////////////////////////////////////////////
// Map a display line count to the POSITION of the 
// Corresponding JEList entry
//
void
CJevDoc::MapDispLineToNJE( int nyLine, int& njeIndex, int& nSubAcct )
{
	const int bRawView = theApp.bGetRawView();        
	nSubAcct = 0; 
	CJournalEntry* pJE;
	int accumsize, index; 
	
	nSubAcct = 0;
	njeIndex = -1; 
	if( m_JEArray.GetSize() == 0 ) return;

	
	if( nyLine < 0 ){
			njeIndex = 0;
			return;
	}
			
	
	for( index=0, accumsize=0; index <= m_JEArray.GetUpperBound(); index++ ) {
 
		if( bRawView ) {
			accumsize++;
		} else {
			pJE = m_JEArray.GetAtJe( index );
			nSubAcct = nyLine - accumsize;
			accumsize += pJE->GetSize() + 1;
		}  
		if( accumsize > nyLine ) { 
			njeIndex = index;
			TRACE( "MapDispLineToJEL: nyLine=%d, njeIndex=%d, nSubAcct=%d\n", nyLine, njeIndex, nSubAcct );
            return;
		}			
	}
	TRACE( "MapDispLineToNJE: Fell Through For-loop.  Shouldnt have!!" );
	TRACE( "MapDispLineToNJE: nyLine=%d, njeIndex=%d, nSubAcct=%d\n", nyLine, njeIndex, nSubAcct );
}

/////////////////////////////////////////////////////////////
// Map a display line count to the POSITION of the 
// Corresponding JEList entry
//
void
CJevDoc::MapNJEToDispLine( int njeIndex, int& nyLine, int& nSubAcct )
{
	const int bRawView = theApp.bGetRawView();
 
	CJournalEntry* pJE;


	
	nSubAcct = 0;	
	nyLine = -1;
	
	if( m_JEArray.GetSize() == 0 ) return;
	if( njeIndex < 0 ) return;
	
		
	int index, accumsize;
	for( index=0, accumsize=0; index <= m_JEArray.GetUpperBound(); index++ ) {
		pJE = (CJournalEntry*) m_JEArray.GetAtJe( index );
        
        if( index == njeIndex ){ 
			nyLine = accumsize;
 
			if( !bRawView ) nSubAcct = pJE->GetSize() + 1;
        	else			nSubAcct = 1;
        
        	TRACE( "Map: nyLine=%d, njeIndex=%d, nSubAcct=%d\n", nyLine, index, nSubAcct );
            return;
        }
            
		if( bRawView ) {
			accumsize++;
		} else {
			accumsize += pJE->GetSize() + 1;
		}		
	}
	TRACE( "Map: Position Not Found!!\n" );
}
/////////////////////////////////////////////////////////////
// Count the Total Number of Display Lines
//
int
CJevDoc::GetTotalDisplayLines( )
{
	const int bRawView = theApp.bGetRawView();
 
	CJournalEntry* pJE;
	int accumsize = 0;

	for( int idx=0; idx <= m_JEArray.GetUpperBound(); idx++) {
		pJE = m_JEArray.GetAtJe( idx );
        
            
		if( bRawView ) {
			accumsize++;
		} else {
			accumsize += pJE->GetSize() + 1;
		}		
	}
	return accumsize;
}	

BOOL CJevDoc::Find( CString FindString, BOOL bMatchCase, BOOL bMatchWholeWord, BOOL bSearchDown )
{

	CJournalEntry* pJE;
	CString strJE;
	CMainFrame* pMainFrame;
	pMainFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	pMainFrame->SetStatusBarText( "Searching..." );
	
	if( m_njeActiveRecord < 0 ) return FALSE;
	if( !bMatchCase ) FindString.MakeLower();
	
	int NJE = m_njeActiveRecord;
	while( TRUE ) { 
		if( bSearchDown ) {
		 	
		 	if( NJE >= m_JEArray.GetUpperBound() ) {
		 		NJE = 0;
	 		 	pMainFrame->SetStatusBarText( "Searching... Wrapped Around" );
		 	}	 
        } else {
			
			if( NJE <= 0 ) {
				NJE = m_JEArray.GetUpperBound();
			 	pMainFrame->SetStatusBarText( "Searching... Wrapped Around" );
			}	 
		}
		pJE = m_JEArray.GetAtJe( NJE );
		strJE = (CString) *pJE;
		
		// match string                                     
		if( !bMatchCase ) strJE.MakeLower();
		if( strJE.Find( FindString ) >= 0 ) {
			m_njeActiveRecord = NJE;
			pMainFrame->SetStatusBarText( "Search:  Found" ); 
			CUpdateHint hint;
			UpdateAllViews( NULL, HINT_NAVIGATION_KEY, &hint );
			return TRUE;
		} 	

		if( NJE == m_njeActiveRecord ) { 
			pMainFrame->SetStatusBarText( "Search:  Not Found" );
			return FALSE;
		}	
	}	
}		
void CJevDoc::OnEditChange()
{
	// TODO: Add your command handler code here
	
}

void CJevDoc::OnUpdateEditChange(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}    


void CJevDoc::OnFileSave() 
{
	// TODO: Add your command handler code here

		 
	CString sFYY_BCK, sFYY_BCK_YYMMDDHH, sFile;

	TRACE("OnFileSave: m_bModified=%d\n", m_bModified);
	afxDump << this;

	//char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	sFile = GetPathName();
	if(sFile != "") {

		//_makepath( path_buffer, "c", "\\sample\\crt\\", "makepath", "c" );
		//printf( "Path created with _makepath: %s\n\n", path_buffer );
		_splitpath( sFile, drive, dir, fname, ext );



		sFYY_BCK = (CString)drive + (CString)dir + "bck";

		CFileStatus status;
		if( CFile::GetStatus( sFYY_BCK, status ) == 0 ) {
			TRACE("OnFileSave: GetStatus(%s) does not exist\n", sFYY_BCK);
			_mkdir( sFYY_BCK );
		}
		
		CTime t = CTime::GetCurrentTime();
		sFYY_BCK_YYMMDDHH = sFYY_BCK + t.Format("\\%y%m%d%H");
		if( CFile::GetStatus( sFYY_BCK_YYMMDDHH, status ) == 0) {
			TRACE("OnFIleSave: GetStatus(%s) does not exist\n",sFYY_BCK_YYMMDDHH);
			_mkdir( sFYY_BCK_YYMMDDHH );
		}

			
		CString sFYY_BCK_YYMMDDHH_FILE = sFYY_BCK_YYMMDDHH + "\\" + fname + ext;
		if( CFile::GetStatus( sFYY_BCK_YYMMDDHH_FILE, status ) == 0) {
			TRACE("OnFileSave: GetStatus(%s) does not exist\n",sFYY_BCK_YYMMDDHH_FILE);
			//CFile::Rename( sFile, sFYY_BCK_YYMMDDHH_FILE );
			//CFile f( sFYY_BCK_YYMMDDHH_FILE, CFile::modeWrite | CFile::modeCreate);
			//m_JEArray.WriteOut( &f );
			//f.Close();
			//m_JEArray.Save( sFYY_BCK_YYMMDDHH_FILE );
			m_JEArray.CopyFile( sFile, sFYY_BCK_YYMMDDHH_FILE );

		}




		TRACE("OnFileSave: sFYY_BCK='%s' sFYY_BCK_YYMMDDHH='%s' sFile='%s'\n",
			sFYY_BCK,sFYY_BCK_YYMMDDHH,sFile);

	}

	CDocument::OnFileSave();
}
