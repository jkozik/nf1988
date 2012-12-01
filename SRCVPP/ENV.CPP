#include "env.h"
#include "direct.h"
#include "stdlib.h"
#include "signal.h"
#include "iostream.h"
#include "io.h"

// env.cpp - global object that performs the following services on
//	     initialization and termination for the program -
// 1. queries the environment for key variables:  YEAR, F.
// 2. changes directory of the program to $F\$YEAR
// 3. validates that the directory exists and chart file exists
// 4. on termination, restores to the directory before the
//    program started.


IMPLEMENT_DYNAMIC( CEnv, CObject );
CString CEnv::m_cwdstr, CEnv::m_path, CEnv::m_froot, CEnv::m_year;
//////////////////////////////////////////////////////////////////////
// CEnv::CEnv  Construct/Destruct
//
CEnv::CEnv()
{

    TRACE("Entering CEnv::CEnv()\n");

    // Save Current Directory
    _getcwd( m_cwdstr.GetBuffer( _MAX_PATH+1 ), _MAX_PATH+1 );
    m_cwdstr.ReleaseBuffer();

    // On ^C, call the Terminate function
    typedef void (*signalFn)(int);
    signal( SIGINT, (signalFn)SigTerm );

    // Query the environment variables F, YEAR
    if( (m_froot = getenv( "F" ))    == NULL ) m_froot = "";
    if( (m_year  = getenv( "YEAR" )) == NULL ) m_year	= "";
    cerr << "\nF='"  << m_froot << "'\n";
    cerr << "YEAR='" << m_year	<< "'\n";

    // Set Working Directory to $F\$YEAR
    m_path = "\\" + m_froot + "\\" + m_year;
    if( _chdir( m_path ) ) {
	cerr << "Unable to change to directory - '" << m_path << "'\n";
	Terminate();
    }

    // The file $F\$YEAR\chart must exist
    if( _access( "chart", 0 ) ) {
	cerr << "The file 'chart' does not exist\n";
	Terminate();
    }

    TRACE("Leaving CEnv::CEnv()\n");
}
CEnv::~CEnv()
{
    TRACE("Entering CEnv::~CEnv()\n");
#ifdef PC_CURSES
    end_win();
#endif
    _chdir( m_cwdstr );
    TRACE("Leaving CEnv::~CEnv()\n");
}
//////////////////////////////////////////////////////////////////////
// CEnv::Terminate()
// Restore directory, call exit(1)
//
void
CEnv::Terminate()
{
    cerr << "Terminating Program.\n";
    TRACE("CEnv::Terminate:  About to exit program...\n");
    exit( 1 );
}
extern "C" {
void
SigTerm(int ign)
{
    ign = ign;
    CEnv::Terminate();
}
}
////////////////////////////////////////////////////////////////////////
// CEnv::AssertValid
//
void
CEnv::AssertValid() const
{
    CObject::AssertValid();
    ASSERT( this->IsKindOf( RUNTIME_CLASS( CEnv ) ) );

}
#ifdef _DEBUG
//////////////////////////////////////////////////////////////////
// CEnv::Dump()
//
void
CEnv::Dump( CDumpContext& dc ) const
{
    ASSERT_VALID( this );

    CObject::Dump( dc );

    afxDump << "\n"
	<< "F='" << m_froot << "'\n"
	<< "YEAR='" << m_year << "'\n"
	<< "Start Up Directory='" << m_cwdstr <<"'\n"
	<< "Journal Entry Directory='" << m_path << "'\n";

}
#endif
