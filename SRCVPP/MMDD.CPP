#include "mmdd.h"
#include "ctype.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__ ;
#endif

// mmdd.cpp - Defines the class member functions for Cmmdd, a member
// class of CString base class


/////////////////////////////////////////////////////////////////////////
// Cmmdd::Cmmdd
// Default and Single argument constructors
//
Cmmdd::Cmmdd() {};
Cmmdd::~Cmmdd() {};

Cmmdd::Cmmdd( const char* pszmmdd ) : CString( pszmmdd )  {};

////////////////////////////////////////////////////////////////////////////
// Cmmdd::Set
// If Account is valid, return TRUE, set m_mmdd String
//
BOOL Cmmdd::Set( const char* pszmmdd )
{
    *this = pszmmdd;
    if( Valid() ) return TRUE;

    m_pchData = "";
    return FALSE;

}


///////////////////////////////////////////////////////////////////////
// Cmmdd::mmddValid
// Validate MM - 00-12
//	and DD - 01-31
//
BOOL Cmmdd::Valid() const
{

// to be completed

    CString mm = Left(2), dd = Right(2);

    if( mm=="00" && dd=="00" ) return TRUE;

    if( !( mm>="01" && mm<="31" ) ) return FALSE;

    if( !( dd>="01" && dd<="31" ) ) return FALSE;

    return TRUE;

}

////////////////////////////////////////////////////////////////////////
// Cmmdd::Get
// Return String for mmdd
//
const CString& Cmmdd::Get()
{
    return   m_pchData;

}
