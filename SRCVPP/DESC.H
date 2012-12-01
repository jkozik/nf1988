#ifndef __DESC_H_
#define __DESC_H_

#ifdef _DOS
#include <afx.h>
#else
#include <afxwin.h>
#endif
#include <afxcoll.h>

const int SZDESC = 30;

///////////////////////////////////////////////////////////////////////
// class CDesc:
// Represents a the DEscription field in Chart of Account and
// Journal Entry records
// Format - zero or more characters required

class CDesc : public CString
{

public:
// Construction
    CDesc();
    ~CDesc();
    CDesc( const char* pszDesc );

// Attributes
    BOOL Set( const char* pszDesc );
    BOOL Valid() const;
    const CString& Get();

};  // CDesc
#endif // __DESC_H_
