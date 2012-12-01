// jevdoc.h : interface of the CJevDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "je.h"
#include 	<direct.h>

#define HINT_DELETE_ACTIVE_RECORD	1
#define HINT_INSERT_ACTIVE_RECORD	2 
#define HINT_NAVIGATION_KEY		3
#define HINT_CHANGE_ACTIVE_RECORD	4
#define HINT_LAST_SELECTED_RECORD	5

class CUpdateHint : public CObject
{
	DECLARE_DYNAMIC( CUpdateHint );
	CUpdateHint();
	int iHint1, iHint2;
};
	
class CJevDoc : public CDocument
{
protected: // create from serialization only
	CJevDoc();
	DECLARE_DYNCREATE(CJevDoc)

// Attributes
public: 

	CJEArray m_JEArray;
    int m_njeActiveRecord,m_njeLastSelectedRecord;
	
// Operations
public:

//	Operators for Active Record Indicator
	void SetActiveRecord( int njeIndex );
	int njeGetActiveRecord() const; 
	void SetLastSelectedRecord( int njeIndex );
	int njeGetLastSelectedRecord() const; 

	void MapDispLineToNJE( int nyLine, int& njeIndex, int& nSubAcct );
	void MapNJEToDispLine( int njeIndex, int& nyLine, int& nSubAcct );
	
	void SetActiveNextRecord();
	void SetActivePrevRecord();
	void SetActiveHomeRecord();
	void SetActiveEndRecord(); 
	int  GetTotalDisplayLines();
		
	void DeleteActiveRecord();
	void DeleteSelectedRecords();
	void InsertAfterActiveRecord(CJournalEntry& JE);  
	void InsertBeforeActiveRecord(CJournalEntry& JE); 
	
	BOOL Find( CString FindString, BOOL bMatchCase, BOOL bMatchWholeWord, BOOL bSearchDown );


	

// Implementation
public:
	virtual ~CJevDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();


// Generated message map functions
protected:
	//{{AFX_MSG(CJevDoc)
	afx_msg void OnEditChange();
	afx_msg void OnUpdateEditChange(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
