#include "desc.h"
#include "ctype.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__ ;
#endif

// desc.cpp - Defines the class member functions for CDesc, a member
// class of CString base class


/////////////////////////////////////////////////////////////////////////
// CDesc::CDesc
// Default and Single argument constructors
//
CDesc::CDesc() {};
CDesc::~CDesc() {};

CDesc::CDesc( const char* pszDesc ) : CString( pszDesc )  {};

////////////////////////////////////////////////////////////////////////////
// CDesc::Set
// If Account is valid, return TRUE
//
BOOL CDesc::Set( const char* pszDesc )
{
    *this = pszDesc;
    if( Valid() ) return TRUE;

    m_pchData = "";
    return FALSE;

}


///////////////////////////////////////////////////////////////////////
// CDesc::Valid
// Validate a Description Field - always TRUE
//
BOOL CDesc::Valid() const
{
    if( GetLength() > SZDESC*2 ) return FALSE;
    else return TRUE;

}

////////////////////////////////////////////////////////////////////////
// CDesc::Get
// Return String for Description
//
const CString& CDesc::Get()
{
    return   m_pchData;

}
