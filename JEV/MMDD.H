#ifndef __MMDD_H_
#define __MMDD_H_

#ifdef _DOS
#include <afx.h>
#else
#include <afxwin.h>
#endif
#include <afxcoll.h>

const int SZMMDD = 4;

///////////////////////////////////////////////////////////////////////
// class Cmmdd:
// mmdd - Month(mm) 00-12  00 is beginning balance month
//

class Cmmdd : public	CString
{

public:
// Construction
    Cmmdd();
    ~Cmmdd();
    Cmmdd( const char* pszmmdd );

// Attributes
    BOOL Set( const char* pszmmdd );
    BOOL Valid() const;
    const CString& Get();

};  // CmmddAcct
#endif // __MMDD_H_
