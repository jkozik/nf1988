#include "stdafx.h"
#include "je.h"
#include "stdlib.h"
//#include "iostream.h"
#include "malloc.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__ ;
#endif

// je.cpp : Defines the class behaviors for CJournalEntry, CGltList

IMPLEMENT_DYNAMIC( CJournalEntry, CGlTran );
IMPLEMENT_DYNAMIC( CJEList, CObList );
IMPLEMENT_DYNAMIC( CJEArray, CObArray );

/////////////////////////////////////////////////////////////////
// CJournalEntry::CJournalEntry
//  Construct/Destruct
//
CJournalEntry::CJournalEntry() : CGlTran()
{
	m_AccumSize = 0;
}
CJournalEntry::~CJournalEntry()
{
    DelAcctAmt();
}
void
CJournalEntry::DelAcctAmt()
{

    for( int i=m_Acct.GetSize()-1; i>=0; i--) {
	((CAcct*)m_Acct[i])->CAcct::~CAcct();
	delete m_Acct.GetAt( i );
    }
    m_Acct.RemoveAll();

    for( i=m_Amt.GetSize()-1; i>=0; i--) {
	delete m_Amt.GetAt( i );
    }
    m_Amt.RemoveAll();

}
//////////////////////////////////////////////////////////////////
// CJournalEntry::CJournalEntry
// Copy Constructor for CJournalEntry class
//
CJournalEntry::CJournalEntry( const CJournalEntry& a ) : CGlTran( a )
{
    ASSERT_VALID( this );
    ASSERT_VALID( &a );
    m_mmdd = a.m_mmdd;
    m_CrAcct = a.m_CrAcct;
    m_CrAmt = a.m_CrAmt;
    m_Desc = a.m_Desc;
    for( int i=a.m_Acct.GetSize()-1; i >= 0; i-- ) {
	m_Acct.SetAtGrow(i, new CAcct( * (CAcct*) a.m_Acct[i] ) );	// needs to be fixed
	m_Amt.SetAtGrow(i, new CAmt( * (CAmt*) a.m_Amt[i] ) );
    }
}
////////////////////////////////////////////////////////////////////////////
// CJournalEntry::AddAcct/AddAmt
// Add an account/amount pair to the journal entry
//
int
CJournalEntry::AddAcct( const CAcct& Acct )
{
    ASSERT_VALID( this );
    return m_Acct.Add( new CAcct( Acct ) );
}
int
CJournalEntry::AddAmt(const CAmt& Amt )
{
    ASSERT_VALID( this );
    return m_Amt.Add( new CAmt( Amt ) );
}
///////////////////////////////////////////////////////////////////////////
// Get operators for m_Acct[] and m_Amt[]
//
const CAcct&
CJournalEntry::GetAtAcct(int nIndex) const
{
    ASSERT_VALID( this );
    return *(CAcct*)m_Acct[nIndex];
}

const CAmt&
CJournalEntry::GetAtAmt(int nIndex) const
{
    ASSERT_VALID( this );
    return *(CAmt*)m_Amt[nIndex];
}

int
CJournalEntry::GetSize() const
{
    ASSERT_VALID( this );
    int size = m_Acct.GetSize();
    ASSERT( size == m_Amt.GetSize() );
    return size;
}                   

void
CJournalEntry::SetAccumSize( int size )
{
	ASSERT_VALID( this );
	m_AccumSize = size;
}

int
CJournalEntry::GetAccumSize( ) const
{
	ASSERT_VALID( this );
	return m_AccumSize;
}
		

////////////////////////////////////////////////////////////////////
// CJournalEntry::operator=
// Overloaded operator= to perform assignments
//
CJournalEntry& CJournalEntry::operator=( const CJournalEntry& b )
{
    ASSERT_VALID( this );
    ASSERT_VALID( &b );

    m_mmdd = b.m_mmdd;
    m_CrAcct = b.m_CrAcct;
    m_CrAmt = b.m_CrAmt;
    m_Desc = b.m_Desc;
    for( int i=b.m_Acct.GetSize(); i >= 0; i-- ) {
	m_Acct.SetAtGrow(i, new CAcct( * (CAcct*)b.m_Acct[i] ) );	// needs to be fixed
	m_Amt.SetAtGrow(i, new CAmt( * (CAmt*)b.m_Amt[i] ) );
    }
    return( *this );
}

/////////////////////////////////////////////////////////////////////////////
// CJournalEntry::operator CString() const
// Convert GlTran record to following format
// MMDD,XXX,999.99[,XXX...X]
//
CJournalEntry::operator CString() const
{
    CString s;
    s = GetMmdd()+",-";
    for( int i=0; i<m_Acct.GetSize(); i++ ) {
	s = s + (CString) GetAtAcct(i) + "," + (CString) GetAtAmt(i).Get() + ";" ;
    }
    s = s + (CString) GetCrAcct() + "-" ;

    if( GetDesc().GetLength() != 0 ) {
	s = s + ","+GetDesc() ;
    }
    return s;
}

///////////////////////////////////////////////////////////////////////
// CJournalEntry::Dump
// Write the contents of the object
//
#ifdef _DEBUG
void CJournalEntry::Dump( CDumpContext& dc ) const
{
    ASSERT_VALID( this );

    CObject::Dump( dc );

    afxDump << "\n"
	<< "Date: " << GetMmdd()
	<< " Cr Account: " << GetCrAcct()
	<< " Cr Amount: " << GetCrAmt().Get()
	<< " Description: \""  << GetDesc() << "\""
	<< "\n" ;
    for( int i=0; i<m_Acct.GetSize(); i++) {
	afxDump << "Acct[" << i << "]: " << *(CAcct*) m_Acct.GetAt(i) ;
	afxDump << " Amt[" << i << "]: " << (*(CAmt*) m_Amt.GetAt(i)).Get() ;
	afxDump << "\n";
    }
}


////////////////////////////////////////////////////////////////////////////////
// CJournalEntry::AssertValid
// Asserts if invalid CJournalEntry fields detected
//
void CJournalEntry::AssertValid() const
{
    CGlTran::AssertValid();
    CAcct* acctp;
    for( int i=0; i<m_Acct.GetSize(); i++) {
	acctp = (CAcct*) m_Acct.GetAt(i);
	if( *acctp != "" ) ASSERT( acctp->Valid() );
    }
}
/////////////////////////////////////////////////////////////////////////
// Test Class CJournalEntry
//
BOOL
CJournalEntry::Test()
{
    TRACE( "\nEntering CJournalEntry::Test()\n");

    CMemoryState point, endpoint, diff;
    point.Checkpoint();

    {
    CString test;
    CJournalEntry je;

    test = "0101,-101,99.99;104-,XXX...X";
    je.Convert( test );

    ASSERT( je.GetMmdd() == "0101" );
    ASSERT( je.GetCrAcct() == "104" );
    ASSERT( je.GetAtAmt(0) == 9999 );
    ASSERT( je.GetAtAmt(0).Get() == "99.99" );
    ASSERT( je.GetDesc() == "XXX...X" );
    ASSERT( (CString) je == test );
    //afxDump << "\n" << je << (CString) je << "\n";

    test = "0101,-101,99.99;302,-100.00;104-,XXX...X";
    je.Convert(test);

    //afxDump << "\n" << je << (CString) je << "\n";
    ASSERT( (CString) je == test );

    test = "0101,-302,-100.00;104-";
    je.Convert(test);
    //afxDump << "\n" << je << (CString) je << "\n";
    ASSERT( (CString) je == test );

    CJournalEntry je2(je);
    //afxDump << "\n" << je2 << (CString) je2 << "\n";
    ASSERT( (CString) je == (CString) je2 );
    TRACE( "\nLeaving CJournalEntry::Test()\n");
    }
    endpoint.Checkpoint();
    if( diff.Difference( point, endpoint ) ) {
	afxDump << "\n";
	diff.DumpStatistics();
	diff.DumpAllObjectsSince();
    }

    return TRUE;
}
#endif

///////////////////////////////////////////////////////////////////
// CJEList
//
////////////////////////////////////////////////////////////////////
// CJEList::~CJEList
// Destructor
//
CJEList::~CJEList()
{
    CJEList::Close();
}

////////////////////////////////////////////////////////////////////
// CJEList::Close
// This will delete the objects in the list
//
void CJEList::Close()
{
    ASSERT_VALID( this );

    POSITION pos = GetHeadPosition();
    while( pos != NULL )
    {
	delete GetNext(pos);
    }
    RemoveAll();
}

///////////////////////////////////////////////////////////////////
// CJEList::Open
// This reads in records from the file YY\??.pgl
//
BOOL CJEList::Open(const char* pszFileName)
{  

    if( pszFileName ) {
	m_FileName = pszFileName;
    }

    CFile f( m_FileName, CFile::modeRead ); 
    LoadIn( &f );
    f.Close();

    return TRUE;
 
#if FALSE
    const int SZLINE = 255;
    char InputRecord[SZLINE+1];
    CJournalEntry c;
    BOOL bGOOD_INPUT;


    if( pszFileName ) {
	m_FileName = pszFileName;
    }

    CStdioFile f( m_FileName, CFile::modeRead );

    while ( f.ReadString( InputRecord, SZLINE ) )
    {
	bGOOD_INPUT = c.Convert( InputRecord );
	if( bGOOD_INPUT  ) {
	    AddTail( new CJournalEntry( c ) );
	}
    }
    f.Close();

    return TRUE;
#endif
}

/////////////////////////////////////////////////////////////////////
// CJEList::LoadIn
// This reads in journal entry records from CFile* file.
// This file is assumed to be already opened, and may
// be called from Archive::Serialize()
//
void CJEList::LoadIn( CFile* file)
{
	const int SZREADBUF = 512;
	const int SZLINE = 255;
	BOOL pGOOD_INPUT;
	CJournalEntry c;
	char InputRecord[SZLINE + 1], ReadBuf[SZREADBUF];
	char *pIR, *pRB;
	int i, nBytes;   
	
	TRACE( "Entering LoadIn()\n" );
	pIR = InputRecord;
	// Read from file until ReadBuf is does not get filled
	do {    
		nBytes = file->Read( ReadBuf, SZREADBUF );
		pRB = ReadBuf; 
		
		// Copy a line of text from ReadBuf into InputRecord
		for( i=0; i<nBytes; i++ ) {
			if( *pRB=='\r' && *(pRB+1)=='\n' ) { // End of Line?
				*pIR++ = '\n';
				*pIR = '\0';   
				//TRACE( "LoadIn(): InputRecord='%s'\n", InputRecord );
				//afxDump.Flush();
				pGOOD_INPUT = c.Convert( InputRecord );
				if( pGOOD_INPUT ) AddTail( new CJournalEntry( c ) );
				
				// Reset InputRecord and keep reading from ReadBuf
				pIR = InputRecord;
				pRB++; pRB++;
				i++; i++;
			} // if
			*pIR++ = *pRB++;
		} // for
	} while ( nBytes == SZREADBUF );
	TRACE( "Leaving LoadIn()\n" );
}
				

///////////////////////////////////////////////////////////////////////
// CJournalEntry::Convert
// Create CJournalEntry with input record string; Return NULL if invalid
//
BOOL CJournalEntry::Convert( const char* pszJEFileRecord )
{
    ASSERT_VALID( this );
    BOOL match, done;
    int field, sidx, slen;

    CString s = CString( pszJEFileRecord );
    CAcct acct;
    CAmt amt;
    slen = s.GetLength();
    done = FALSE;
    sidx = 0;
    SetDesc( "" );
    DelAcctAmt();

    for( field=0; done == FALSE; field++ )
    {
	match = FALSE;
	switch( field )
	{
	case 0: /* date - MMDD,   */
	    match = SetMmdd( (s.Mid( sidx )).SpanExcluding(","));
	    sidx += GetMmdd().GetLength() + 1;
	    break;

	case 1: /* look for '-' */
	    match = s[sidx] == '-' ;
	    sidx++;
	    break;

	case 2: /* account no. -  XXX, */
	    match = acct.Set( (s.Mid( sidx )).SpanExcluding(",-"));
	    if( s[sidx+SZACCT] == '-' ) {
		SetCrAcct( acct );
		sidx += acct.GetLength() + 1;
		field++;
	    } else {
		AddAcct( acct );
		sidx += acct.GetLength() + 1;
	    }
	    break;

	case 3: /*Amount - 999.99 followed by , or \n */
	    match = amt.Set( (s.Mid( sidx )).SpanExcluding(";") );
	    AddAmt( amt );
	    sidx += amt.Get().GetLength() + 1;
	    field = field - 2;
	    break;

	case 4: /* ',' - description follows; \n - done */
	    if( sidx >= slen || s[sidx] == '\n' ) {
		match = TRUE;
		done = TRUE;
	    } else if( s[sidx] == ',' ) {
		match = TRUE;
		sidx++;
	    }
	    break;

	case 5: /* description - XX...X, or XX...X\n */
	    match = SetDesc( (s.Mid( sidx )).SpanExcluding("\n") );
	    done = TRUE;
	    break;

	} // switch
	if( match == FALSE ) {  
		TRACE("Convert: Invalid Journal Entry Input Record:\n%s", 
			pszJEFileRecord );
	    done = TRUE;
	}
    } // for
    return match;
} // function


///////////////////////////////////////////////////////////////////////////
// CJEList::Save
// Write CJEList to file
//
BOOL
CJEList::Save( const char* pszFileName )
{

    if( pszFileName ) m_FileName = pszFileName;
   
    CFile f( m_FileName, CFile::modeWrite | CFile::modeCreate);
    WriteOut( &f ); 
    f.Close();
    return TRUE;

#if FALSE
    if( pszFileName ) m_FileName = pszFileName;
    CStdioFile f( m_FileName, CFile::modeWrite | CFile::modeCreate |
			      CFile::typeText);

    CJournalEntry* jep;
    POSITION pos = GetHeadPosition();
    while( pos != NULL )
    {
	//jep = (CJournalEntry*) GetNext(pos);
	jep = GetNextJe( pos );
	f.WriteString( ((CString) *jep) + "\n" );
    }
    f.Close();
    return TRUE;
#endif
}                                                    

////////////////////////////////////////////////////////////////////
// CJEList::WriteOut
// Write JEList Out to file.  May be called from Archive::Serialize
//
void CJEList::WriteOut( CFile* file )
{
	const int SZWRITEBUF = 512;
	char WriteBuf[SZWRITEBUF];
	CJournalEntry* jep;
	
	POSITION pos = GetHeadPosition();
	while( pos != NULL ) {
		jep = GetNextJe( pos );
		strcpy( WriteBuf, ((CString) *jep) + "\r" + "\n" );
		file->Write( WriteBuf, strlen( WriteBuf ) );
	} // while
}
		

////////////////////////////////////////////////////////////////////////////////////
// CJEList::operator=
// Assignment operator
//
CJEList& CJEList::operator=( const CJEList& je )
{
    m_FileName = je.m_FileName;
    POSITION pos = je.GetHeadPosition();
    while( pos != NULL) {
	//AddTail( new CJournalEntry( * (CJournalEntry*) je.GetNext( pos ) ) );
	AddTail( new CJournalEntry( * GetNextJe( pos ) ) );
    }
    return *this;
}
//////////////////////////////////////////////////////////////////////
// CJEList::GetNextJe
// Returns CJournalEntry* pointer to the next JE record in JEList
// Type safe!!
CJournalEntry*
CJEList::GetNextJe( POSITION& rPosition) const
{
    return (CJournalEntry*) GetNext( rPosition );
}


//////////////////////////////////////////////////////////////////////////
// CJEList::operator CGltArray() const
// Convert a list of Journal Entries into a list of General
// Ledger transactions
//
CJEList::operator CGltArray*() const
{
    CGltArray *gltarp = new CGltArray();
    CJournalEntry *jep;
    CGlTran glt;
    CAmt totamt;
    int GltArrayRecCnt = 0;

    gltarp->SetSize( GetCount() * 3 );

    POSITION pos = GetHeadPosition();
    while( pos != NULL) {
	//jep = (CJournalEntry*) GetNext( pos );
	jep = GetNextJe( pos );
	glt.SetMmdd( jep->GetMmdd() );
	glt.SetDesc( jep->GetDesc() );
	totamt = 0L;
	for( int i=0; i< jep->GetSize(); i++ ) {
	    glt.SetCrAcct( jep->GetAtAcct(i) );
	    glt.SetCrAmt( jep->GetAtAmt(i) );
	    totamt = totamt + glt.GetCrAmt();
	    gltarp->SetAtGrow( GltArrayRecCnt++, new CGlTran( glt ) );
	}
	glt.SetCrAmt ( -totamt );
	glt.SetCrAcct( jep->GetCrAcct() );
	gltarp->SetAtGrow( GltArrayRecCnt++, new CGlTran( glt ) );
    }
    gltarp->SetSize( GltArrayRecCnt );
    return gltarp;
}

#if _DEBUG
/////////////////////////////////////////////////////////////////////////
// Test Class CJEList
//
BOOL
CJEList::Test()
{
    TRACE( "\nEntering CJEList::Test()\n");

    CMemoryState point, endpoint, diff;
    point.Checkpoint();

    {
    CJEList jear,jear2,jear3;
    CString test;
    CJournalEntry je;
    CGltArray *gltarp;

    test = "0101,-101,99.99;302,-100.00;104-,XXX...X";
    je.Convert( test );

    jear.AddTail( new CJournalEntry( je ) );

    test = "0101,-302,-100.00;104-";
    je.Convert( test );
    jear.AddTail( new CJournalEntry( je ) );

    test = "0102,-302,-100.00;323,-0.34;104-";
    je.Convert( test );
    jear.AddTail( new CJournalEntry( je ) );

    afxDump.SetDepth( 1 );
    //TRACE("jear\n");

    //afxDump << "\n" << jear;


    jear2 = jear;
    //afxDump << "\n" << jear2;
    //TRACE("jear2 = jear\n");

    ASSERT( jear.GetCount() ==3 && jear2.GetCount() == 3 );
    jear.Close();
    //TRACE("jear.Close\n");

    jear2.Close();
    //TRACE("jear2.Close\n");

    //TRACE( "Open()\n" );
    jear3.Open( "c:\\nf\\92\\01" );
    //TRACE("jear3.Open\n");

    //afxDump << "\n" << jear3;

    //TRACE( "Save()\n" );
    jear3.Save( "c:\\nf\\92\\01.dup" );

    //TRACE ( "Copy je to glt\n" );
    gltarp = jear3;
    //TRACE( "glt.Save()\n" );
    gltarp->Save("c:\\nf\\92\\01.gje" );
    //TRACE( "Close()\n" );
    gltarp->Close();
    delete gltarp;
    jear3.Close();
    goto endTest;
endTest: ;
    TRACE( "\nLeaving CJEList::Test()\n");
    }
    endpoint.Checkpoint();
    if( diff.Difference( point, endpoint ) ) {
	afxDump << "\n";
	diff.DumpStatistics();
	diff.DumpAllObjectsSince();
    }

    return TRUE;
}
#endif



///////////////////////////////////////////////////////////////////
// CJEArray
//
////////////////////////////////////////////////////////////////////
// CJEArray::~CJEArray
// Destructor
//
CJEArray::~CJEArray()
{
    CJEArray::Close();
}

////////////////////////////////////////////////////////////////////
// CJEArray::Close
// This will delete the objects in the list
//
void CJEArray::Close()
{
    ASSERT_VALID( this );

	for( int idx=GetSize()-1; idx>=0; idx-- ) 
    {
	delete GetAt( idx );
    }
    RemoveAll();
}

///////////////////////////////////////////////////////////////////
// CJEArray::Open
// This reads in records from the file YY\??.pgl
//
BOOL CJEArray::Open(const char* pszFileName)
{  

    if( pszFileName ) {
	m_FileName = pszFileName;
    }

    CFile f( m_FileName, CFile::modeRead ); 
    LoadIn( &f );
    f.Close();

    return TRUE;
 
}

/////////////////////////////////////////////////////////////////////
// CJEArray::LoadIn
// This reads in journal entry records from CFile* file.
// This file is assumed to be already opened, and may
// be called from Archive::Serialize()
//
void CJEArray::LoadIn( CFile* file)
{
	const int SZREADBUF = 512;
	const int SZLINE = 255;
	BOOL pGOOD_INPUT;
	CJournalEntry c;
	char InputRecord[SZLINE + 1], ReadBuf[SZREADBUF];
	char *pIR, *pRB;
	int i, nBytes, njeIndex;   
	
	TRACE( "Entering LoadIn()\n" );
	pIR = InputRecord;
	SetSize( 140 );        
	njeIndex = 0;
	// Read from file until ReadBuf is does not get filled
	do {    
		nBytes = file->Read( ReadBuf, SZREADBUF );
		pRB = ReadBuf; 
		
		// Copy a line of text from ReadBuf into InputRecord
		for( i=0; i<nBytes; i++ ) {
			if( *pRB=='\r' && *(pRB+1)=='\n' ) { // End of Line?
				*pIR++ = '\n';
				*pIR = '\0';   
				//TRACE( "LoadIn(): InputRecord='%s'\n", InputRecord );
				//afxDump.Flush();
				pGOOD_INPUT = c.Convert( InputRecord );
				if( pGOOD_INPUT ) SetAtGrow( njeIndex++, new CJournalEntry( c ) );
				
				// Reset InputRecord and keep reading from ReadBuf
				pIR = InputRecord;
				pRB++; pRB++;
				i++; i++;
			} // if
			*pIR++ = *pRB++;
		} // for
	} while ( nBytes == SZREADBUF ); 
	SetSize( njeIndex );
	TRACE( "Leaving LoadIn()\n" );
}
				


///////////////////////////////////////////////////////////////////////////
// CJEArray::Save
// Write CJEArray to file
//
BOOL
CJEArray::Save( const char* pszFileName )
{

    if( pszFileName ) m_FileName = pszFileName;
   
    CFile f( m_FileName, CFile::modeWrite | CFile::modeCreate);
    WriteOut( &f ); 
    f.Close();
    return TRUE;

}                                                    

////////////////////////////////////////////////////////////////////
// CJEArray::WriteOut
// Write JEList Out to file.  May be called from Archive::Serialize
//
void CJEArray::WriteOut( CFile* file )
{
	const int SZWRITEBUF = 512;
	char WriteBuf[SZWRITEBUF];
	CJournalEntry* jep;
	
	for( int idx=0; idx<GetSize(); idx++ ) {
		jep = GetAtJe( idx );
		strcpy( WriteBuf, ((CString) *jep) + "\r" + "\n" );
		file->Write( WriteBuf, strlen( WriteBuf ) );
	} // while
}
////////////////////////////////////////////////////////////////////////////////////
// CJEArray::CopyFile
// Helper Function
//
void
CJEArray::CopyFile( const char* pszFromFile, const char* pszToFile)
{

	CFileStatus status;
	if( CFile::GetStatus( pszFromFile, status ) == 0 ) {
		TRACE("CopyFile: GetStatus(%s) does not exist\n", pszFromFile);
		return;
	}

	CFile fromFile( pszFromFile, CFile::modeRead);
	CFile toFile( pszToFile, CFile::modeWrite | CFile::modeCreate );
	const int SZBUF = 512;
	char Buf[SZBUF];
	int nBytes;

	do {    
		nBytes = fromFile.Read( Buf, SZBUF );
		toFile.Write( Buf, strlen( Buf ) );
	} while ( nBytes == SZBUF ); 

}


////////////////////////////////////////////////////////////////////////////////////
// CJEArray::operator=
// Assignment operator
//
CJEArray& CJEArray::operator=( const CJEArray& je )
{
    m_FileName = je.m_FileName;
	for( int idx=0; idx<GetSize(); idx++ ) {
		Add( new CJournalEntry( * GetAtJe( idx ) ) );
    }
    return *this;
}
//////////////////////////////////////////////////////////////////////
// CJEArray::GetNextJe
// Returns CJournalEntry* pointer to the next JE record in JEList
// Type safe!!
CJournalEntry*
CJEArray::GetAtJe( int nIndex ) const
{
    return (CJournalEntry*) GetAt( nIndex );
}


//////////////////////////////////////////////////////////////////////////
// CJEArray::operator CGltArray() const
// Convert a list of Journal Entries into a list of General
// Ledger transactions
//
CJEArray::operator CGltArray*() const
{
    CGltArray *gltarp = new CGltArray();
    CJournalEntry *jep;
    CGlTran glt;
    CAmt totamt;
    int GltArrayRecCnt = 0;

    gltarp->SetSize( GetSize() * 3 );

	for( int idx=0; idx<GetSize(); idx++ ) {
	jep = GetAtJe( idx );
	glt.SetMmdd( jep->GetMmdd() );
	glt.SetDesc( jep->GetDesc() );
	totamt = 0L;
	for( int i=0; i< jep->GetSize(); i++ ) {
	    glt.SetCrAcct( jep->GetAtAcct(i) );
	    glt.SetCrAmt( jep->GetAtAmt(i) );
	    totamt = totamt + glt.GetCrAmt();
	    gltarp->SetAtGrow( GltArrayRecCnt++, new CGlTran( glt ) );
	}
	glt.SetCrAmt ( -totamt );
	glt.SetCrAcct( jep->GetCrAcct() );
	gltarp->SetAtGrow( GltArrayRecCnt++, new CGlTran( glt ) );
    }
    gltarp->SetSize( GltArrayRecCnt );
    return gltarp;
}

#if _DEBUG
/////////////////////////////////////////////////////////////////////////
// Test Class CJEArray
//
BOOL
CJEArray::Test()
{
    TRACE( "\nEntering CJEArray::Test()\n");

    CMemoryState point, endpoint, diff;
    point.Checkpoint();

    {
    CJEArray jear,jear2,jear3;
    CString test;
    CJournalEntry je;
    CGltArray *gltarp;

    test = "0101,-101,99.99;302,-100.00;104-,XXX...X";
    je.Convert( test );

    jear.Add( new CJournalEntry( je ) );

    test = "0101,-302,-100.00;104-";
    je.Convert( test );
    jear.Add( new CJournalEntry( je ) );

    test = "0102,-302,-100.00;323,-0.34;104-";
    je.Convert( test );
    jear.Add( new CJournalEntry( je ) );

    afxDump.SetDepth( 1 );
    //TRACE("jear\n");

    //afxDump << "\n" << jear;


    jear2 = jear;
    //afxDump << "\n" << jear2;
    //TRACE("jear2 = jear\n");

    ASSERT( jear.GetSize() ==3 && jear2.GetSize() == 3 );
    jear.Close();
    //TRACE("jear.Close\n");

    jear2.Close();
    //TRACE("jear2.Close\n");

    //TRACE( "Open()\n" );
    jear3.Open( "c:\\nf\\92\\01" );
    //TRACE("jear3.Open\n");

    //afxDump << "\n" << jear3;

    //TRACE( "Save()\n" );
    jear3.Save( "c:\\nf\\92\\01.dup" );

    //TRACE ( "Copy je to glt\n" );
    gltarp = jear3;
    //TRACE( "glt.Save()\n" );
    gltarp->Save("c:\\nf\\92\\01.gje" );
    //TRACE( "Close()\n" );
    gltarp->Close();
    delete gltarp;
    jear3.Close();
    goto endTest;
endTest: ;
    TRACE( "\nLeaving CJEArray::Test()\n");
    }
    endpoint.Checkpoint();
    if( diff.Difference( point, endpoint ) ) {
	afxDump << "\n";
	diff.DumpStatistics();
	diff.DumpAllObjectsSince();
    }

    return TRUE;
}
#endif

