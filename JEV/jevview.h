// jevview.h : interface of the CJevView class
//
/////////////////////////////////////////////////////////////////////////////
 
#define JE_VIEW_WIDTH 80

class CJevView : public CScrollView
{
protected: // create from serialization only
	void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView );
	CJevView();
	DECLARE_DYNCREATE(CJevView)

// Attributes
public:
	CJevDoc* GetDocument(); 
	
protected:
	BOOL bMouseDown;
	int m_njePrevRecordCount;
	int m_njePrevActiveRecord,m_njePrevLastSelectedRecord;
	int m_cyChar, m_cxChar, m_cxClient, m_cyClient;
	  	

// Operations
public: 
	virtual void OnInitialUpdate();  
	virtual void OnUpdate( CView* pSender, LPARAM lHint = 0l,
		CObject* pHint = NULL );

// Implementation
public:
	virtual ~CJevView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL );
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	void UpdateScrollSizes();
	void InvalidateRecord(CDC* pDC, int njeIndex, int nSubAcctOverRide = 0);
	void JETextOut( CDC* pDC, CJournalEntry* pJE, int yStart, 
					int yBottom, BOOL bActiveRecord );

	void JETextOut( CDC* pDC, CJournalEntry* pJE, CRect& Rect,
					   BOOL bActiveRecord );

	BOOL bIsReplaceDialog;
	CFindReplaceDialog* pFindReplaceDialog;
	LONG FindReplaceHelper( UINT wParam, LONG lParam ); 
	CString sFindString;


	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CJevView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnEditChange();
	afx_msg void OnUpdateEditChange(CCmdUI* pCmdUI);
	afx_msg void OnEditInsert();
	afx_msg void OnEditAppend();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in jevview.cpp
inline CJevDoc* CJevView::GetDocument()
   { return (CJevDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
#define NX_MMDD	0
#define NX_ACCT 6
#define NX_CHDESC 10
#define NX_AMT	49
#define NX_DESC	50

#define CX_MMDD 4
#define CX_DD 2
#define CX_ACCT 3
#define CX_CHDESC 20
#define CX_AMT 10
#define CX_DESC 30			
