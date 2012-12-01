#ifndef __JE_H_
#define __JE_H_

#ifdef _DOS
#include <afx.h>
#else
#include <afxwin.h>
#endif
#include <afxcoll.h>
#include "glt.h"



///////////////////////////////////////////////////////////////////////
// class CJournalEntry:	Journal Entry Record
// mmdd,-XXX,XXX.XX[;XXX,XXX.XX...];XXX-[,XXXX...X]
// [Cmmdd m_mmdd],-[CAcct m_Acct[0]],[CAmt m_Amt[0]]
//		   {;[CAcct m_Acct[]],[CAmt m_Amt[]]...};
//		   [CAcct m_CrAcct],[CAmt m_CrAmt]-{,[CDesc m_Desc]}


class CJournalEntry : public CGlTran
{
    DECLARE_DYNAMIC( CJournalEntry );

public:
// Construction
    CJournalEntry() ;
    ~CJournalEntry();
    //CJournalEntry( const CGlTran& a ): CGlTran( a );
    CJournalEntry( const CJournalEntry& a );

// Attributes
    int AddAcct( const CAcct& Acct );
    int AddAmt( const CAmt& Amt );
    const CAcct& GetAtAcct( int nIndex ) const;
    const CAmt& GetAtAmt( int nIndex ) const;
    int GetSize() const;
    void SetAccumSize( int );
    int  GetAccumSize() const;
    


// Operations
    CJournalEntry& operator=( const CJournalEntry& b );
    BOOL Convert( const char* pszJournalEntryInputRecord );
    operator CString() const;
    void DeleteAll();
    void DelAcctAmt();
    
// Implementation
protected:
    CPtrArray m_Acct, m_Amt;
    int m_AccumSize;   //Sigma( GetSize( 1..currentRecord )


public:
    #if _DEBUG
	BOOL Test();
	virtual void Dump( CDumpContext& dc ) const;
	virtual void AssertValid() const;
    #endif

};



/////////////////////////////////////////////////////////////////////
// class CJEList:
// List of CJournalEntry records.

class CJEList : public CObList
{
    DECLARE_DYNAMIC( CJEList );

public:
// Construction
    CJEList() {};
    ~CJEList();
// Operators
    CJEList& operator=( const CJEList& je );
    CJournalEntry* GetNextJe( POSITION& rPosition )const;

    operator CGltArray*() const;

    BOOL Open( const char* pszJEFileName = "" ); 
    void LoadIn( CFile* file );
    BOOL Save( const char* pszJEFileName = "" ); 
    void WriteOut( CFile* file );
    void Close();  

	
	
public:
#if _DEBUG
    BOOL Test();
#endif
// Implementation
protected:
    CString m_FileName;
}; 



/////////////////////////////////////////////////////////////////////
// class CJEArray:
// Array of CJournalEntry records.

class CJEArray : public CObArray
{
    DECLARE_DYNAMIC( CJEArray );

public:
// Construction
    CJEArray() {};
    ~CJEArray();
// Operators
    CJEArray& operator=( const CJEArray& je );
    CJournalEntry* GetAtJe( int nIndex ) const;

    operator CGltArray*() const;

    BOOL Open( const char* pszJEFileName = "" ); 
    void LoadIn( CFile* file );
    BOOL Save( const char* pszJEFileName = "" ); 
    void WriteOut( CFile* file );
    void Close();  
	void CopyFile( const char* pszFromFile, const char* pszToFile);

	
	
public:
#if _DEBUG
    BOOL Test();
#endif
// Implementation
protected:
    CString m_FileName;
};




#endif // __JE_H_
