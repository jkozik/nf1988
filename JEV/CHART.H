#ifndef __CHART_H_
#define __CHART_H_

#include <afxwin.h>

#include <afxcoll.h>
#include "acct.h"
#include "desc.h"

/////////////////////////////////////////////////////////////////////////////
// class CChart:
// Represents one account in the chart of accounts for the current year.

class CChart : public CObject
{
    DECLARE_DYNAMIC( CChart );
public:
//Construction
    CChart(){};
    CChart(const CChart& a);
    //CChart( const char* pszChartFileRecord );
    CChart(const char* pszChartAcct,
	    const char* pszDesc,
	    const char* pszOldAcct = "",
	    const BOOL SummaryAcct = FALSE);

//Attributes
    BOOL SetChartAcct( const char* pszChartAcct)
    {
	ASSERT_VALID( this );
	return m_ChartAcct.Set( pszChartAcct );
    }

    BOOL OldAcctValid()  const
    {
	if( m_OldAcct == "" ) return TRUE;
	return TRUE;
    }
    const CAcct& GetChartAcct() const
    {
	ASSERT_VALID( this );
	return( m_ChartAcct );
    }

    BOOL SetDesc( const char* pszDesc)
    {
	ASSERT_VALID( this );
	return m_Desc.Set( pszDesc );
    }

    const CString& GetDesc() const
    {
	ASSERT_VALID( this );
	return( m_Desc );
    }

    BOOL SetOldAcct( const char* pszOldAcct)
    {
	ASSERT_VALID( this );
	m_OldAcct = pszOldAcct;
	return TRUE;
    }

    const CString& GetOldAcct() const
    {
	ASSERT_VALID( this );
	return( m_OldAcct );
    }

    BOOL SetSummaryAcct( const CString& sum )
    {
	ASSERT_VALID( this );
	if ( sum == "s" ) m_SummaryAcct = TRUE;
	else if ( sum == "" ) m_SummaryAcct = FALSE;
	else return FALSE;
	return TRUE;
    }

    BOOL GetSummaryAcct() const
    {
	ASSERT_VALID( this );
	return( m_SummaryAcct );
    }

//Operations
    CChart& operator=( const CChart& b);
    BOOL    Convert( const char* pszChartInputRecord );

//Implementations
protected:

    CDesc m_Desc;
    BOOL m_SummaryAcct;
    CAcct m_ChartAcct;
    CString m_OldAcct;
public:

#if _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
    virtual void AssertValid() const;

#endif
};



/////////////////////////////////////////////////////////////////////////////
// class CChartList:
// Represents list of chart of account records read from file YY\chart.

class CChartList : public CObList
{
    DECLARE_DYNAMIC( CChartList );

public:
//Construction

    CChartList() {};

    BOOL Open(const char* pszChartFileName);

    CChart* FindChartAcct( const char* ChartAcct );

    void Close();
#ifdef _DEBUG
    BOOL Test();
    void CChartList::AssertValid() const;
#endif
};

extern CChartList* pChartList;
extern "C" const char* CHlookup( char* acct );
extern "C" const char* CHvaild( char* acct );

#endif // __CHART_H_
