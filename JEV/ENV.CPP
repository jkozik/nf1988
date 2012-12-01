#include "stdafx.h"
#include "jev.h"
#include "env.h"
#include "direct.h"
#include "stdlib.h"
//#include "signal.h"
//#include "iostream.h"
#include "io.h"

// env.cpp - global object that performs the following services on
//	     initialization and termination for the program -
// 1. queries the environment for key variables:  YEAR, F.
// 2. changes directory of the program to $F\$YEAR
// 3. validates that the directory exists and chart file exists
// 4. on termination, restores to the directory before the
//    program started.


IMPLEMENT_DYNAMIC( CEnv, CObject );
//////////////////////////////////////////////////////////////////////
// CEnv::CEnv  Construct/Destruct
//
CEnv::CEnv()
{    
    TRACE("Entering CEnv::~CEnv()\n");

    TRACE("Leaving CEnv::~CEnv()\n");

}

////////////////////////////////////////////////////////////////
// CEnv::Init   Initialize
void 
CEnv::Init()
{
    
#ifdef _DEBUG    
	//afxTraceEnabled = 1;
#endif
    TRACE("Entering CEnv::Init()\n");

    // Save Current Directory
    _getcwd( m_cwdstr.GetBuffer( _MAX_PATH+1 ), _MAX_PATH+1 );
    m_cwdstr.ReleaseBuffer();

    // On ^C, call the Terminate function
    //typedef void (*signalFn)(int);
    //signal( SIGINT, (signalFn)SigTerm );

    // Query the environment variables F, YEAR 
    m_froot = getenv( "F" );
    m_year  = getenv( "YEAR" );
    
    
    //TRACE( "\nF='%s'\nYEAR='%s'\n", m_froot, m_year );

    // Set Working Directory to $F\$YEAR
    m_path = "\\" + m_froot + "\\" + m_year;
    if( _chdir( m_path ) ) {
        TRACE( "Unable to change to directory - '%s'\n", m_path );
              Terminate();
    }

    // The file $F\$YEAR\chart must exist
    if( _access( "chart", 0 ) ) {
        TRACE( "The file 'chart' does not exist\n");
	Terminate();
    }

    TRACE("Leaving CEnv::Init()\n");
}
CEnv::~CEnv()
{
    TRACE("Entering CEnv::~CEnv()\n");
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

    TRACE("CEnv::Terminate:  About to exit program...\n");
    exit( 1 );
}
#ifdef _DEBUG
////////////////////////////////////////////////////////////////////////
// CEnv::AssertValid
//
void
CEnv::AssertValid() const
{
    CObject::AssertValid();
    ASSERT( this->IsKindOf( RUNTIME_CLASS( CEnv ) ) );

}

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
