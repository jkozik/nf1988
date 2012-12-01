// Acct_DlgBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAcct_DlgBar dialog

class CAcct_DlgBar : public CDialogBar
{
// Construction
public:
	CAcct_DlgBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAcct_DlgBar)
	enum { IDD = IDD_ACCT_DLGBAR };
	CString	m_Acct;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAcct_DlgBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAcct_DlgBar)
	afx_msg void OnGenerateReport();
	afx_msg void OnChangeAcct();
	afx_msg void OnKillfocusAcct();
	afx_msg void OnSetfocusAcct();
	afx_msg void OnMaxtextAcct();
	afx_msg void OnUpdateAcct();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
