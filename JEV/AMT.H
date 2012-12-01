#ifndef __AMT_H_
#define __AMT_H_

#ifdef _DOS
#include <afx.h>
#else
#include <afxwin.h>
#endif
#include <afxcoll.h>



///////////////////////////////////////////////////////////////////////
// class CAmt:
// Amt - [+-]9[9...9].99
//  or	 [+-]9[9...9].
//  or	 [+-]9[9...9]
//

class CAmt
{

public:
// Construction
    CAmt();
    ~CAmt();
    CAmt( const CAmt& Amt );
    CAmt( const char* pszAmt );
    CAmt( const long lAmt );


// Attributes
    BOOL Set( const char* pszAmt );
    BOOL Set( const long lAmt );
    BOOL Valid() const;
    const CString Get() const;
    long Value();

// Operations
    CAmt& operator=( const CAmt& b );
    CAmt& operator=( const long lAmt );
    CAmt& operator=( const char* pszAmt );
    friend CAmt operator+( const CAmt& Amt, const char* pszAmt );
    BOOL operator==( const CAmt& a );
    BOOL operator==( const long a );
    operator long() const;
    BOOL Test();
//Implementation
    long m_lAmt;

};  // CAmt
#endif // __AMT_H_
