#ifndef __GLT_H_
#define __GLT_H_

#ifdef _DOS
#include <afx.h>
#else
#include <afxwin.h>
#endif
#include <afxcoll.h>
#include "mmdd.h"
#include "acct.h"
#include "amt.h"
#include "desc.h"


///////////////////////////////////////////////////////////////////////
// class CGlTran:	General Ledger Transaction Record
// mmdd,XXX,XXX.XX[,XXXX...X]
// [Cmmdd m_mmdd],[Cacct m_CrAcct],[CAmt m_CrAmt],[CDesc m_Desc]


class CGlTran : public CObject
{
    DECLARE_DYNAMIC( CGlTran );
public:
// Construction
    CGlTran() {};
    ~CGlTran() {};
    CGlTran( const CGlTran& a );
    CGlTran( const char* pszMMDD, const char* pszAcct, const char* pszAmt, const char* pszDesc="" );

// Attributes
    BOOL SetMmdd( const char* pszMMDD );
    BOOL SetCrAcct( const char* pszCrAcct );
    BOOL SetCrAmt( const char* pszCrAmt );
    BOOL SetCrAmt( const long lAmt );
    BOOL SetDesc( const char* pszDesc );

    const Cmmdd& GetMmdd() const;
    const CAcct& GetCrAcct() const;
    const CAmt&  GetCrAmt() const;
    const CDesc& GetDesc() const;


// Operations
    CGlTran& operator=( const CGlTran& b );
    BOOL Convert( const char* pszGlTranInputRecord );
    operator CString() const;

// Implementation
protected:
    Cmmdd m_mmdd;
    CAcct m_CrAcct;
    CAmt m_CrAmt;
    CDesc m_Desc;

public:
    #if _DEBUG
	virtual void Dump( CDumpContext& dc ) const;
	virtual void AssertValid() const;
	BOOL Test();
    #endif

};



/////////////////////////////////////////////////////////////////////
// class CGltArray:
// Array of CGlTran records. Kept in array to support qsort'ing


class CGltArray : public CObArray
{
    DECLARE_DYNAMIC( CGltArray );
public:
// Construction
    CGltArray();
    ~CGltArray();
    CGltArray( const CGltArray& glt );
    //CGltArray( const CJEList& je )

// Operators
    //CGltArray& operator=( const CJEList& je );
    CGltArray& operator=( const CGltArray& glt );
    CGlTran* GetAtGlt( int nIndex ) const ;

    BOOL Open( const char* pszGltFileName = "" );
    BOOL Save( const char* pszGltFileName = "" );
    void Close();

    //void Convert( const CJEList& je );
    void SortbyAcctMmdd();

public:
    #ifdef _DEBUG
	static BOOL CGltArray::Test();
	//virtual void AssertValid() const;
    #endif

// Implementation
protected:
    CString m_FileName;
};
    extern "C" int CmpAcctMmdd(CGlTran** a1, CGlTran** a2);

//////////////////////////////////////////////////////////////////////////////////
// GltAllMonths
// This class gives a sorted view of all General Ledger Transaction
// files from 00.sgl thru 12.sgl.  To save storage, this class views
// by account then month, by merging these files together one record
// at a time, potentially openning 13 files at once.
//
class GltAllMonths : public CObject
{
    DECLARE_DYNAMIC( GltAllMonths );
	enum eSortKey {SortByAcctMonth, SortByMonthAcct };

public:
// Construction
    GltAllMonths( eSortKey SortKey = SortByAcctMonth );
    ~GltAllMonths();

// Operation
    BOOL Open();
    CGlTran GetNextGlt();
    void Close();

// Implementation
protected:
    struct GltFileDesc {
		CStdioFile fd;
	CString FileName;
	CGlTran glt;
    };
    void AddToSortedGltList( GltFileDesc* fdp );
    struct GltFileDesc* GetNextGltFd( POSITION& rpos ) const;
    struct GltFileDesc* GetAtGltFd( POSITION rpos );

    eSortKey m_SortKey;
    CPtrList m_GltFdList;

public:
#ifdef _DEBUG
    static BOOL Test();
    virtual void Dump( CDumpContext& dc ) const;
    virtual void AssertValid() const;
#endif

};

const int MONTHS = 13;
const int SZGLTLINE = 256;
const static char *months[MONTHS] = { "00", "01", "02", "03",
			"04", "05", "06", "07",
			"08", "09", "10", "11", "12"
		      };

#endif // __GLT_H_
