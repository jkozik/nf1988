// RptFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRptFrame frame

class CRptFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRptFrame)
protected:
	CRptFrame();           // protected constructor used by dynamic creation
	CDialogBar m_Acct_DlgBar;
	CString m_sAcct;


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRptFrame)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRptFrame();

	// Generated message map functions
	//{{AFX_MSG(CRptFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGenerateReport();
	afx_msg void OnChangeAcct();
	afx_msg void OnKillfocusAcct();
	afx_msg void OnSetfocusAcct();
	afx_msg void OnMaxtextAcct();
	afx_msg void OnUpdateAcct();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
