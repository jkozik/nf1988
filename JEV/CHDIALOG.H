// chdialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCHDialog dialog

class CCHDialog : public CDialog
{
// Construction
public:
	CCHDialog(CWnd* pParent = NULL);	// standard constructor
	void CCHDialog::SetAcct( CString sAcct ); 
	CWnd* m_hFocus; 
	CWnd* m_pJEDialog;
	
// Dialog Data
	//{{AFX_DATA(CCHDialog)
	enum { IDD = IDD_CH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CCHDialog)
	afx_msg void OnSelchangeList1();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
