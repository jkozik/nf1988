// jedialog.h : header file
// 
#include "je.h" 
#include "chdialog.h"


/////////////////////////////////////////////////////////////////////////////
// CDDEdit control

class CDDEdit : public CEdit
{
// Construction
public:
	CDDEdit();

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CDDEdit();

protected:
	// Generated message map functions
	//{{AFX_MSG(CDDEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CAmtEdit control

class CAmtEdit : public CEdit
{
// Construction
public:
	CAmtEdit();

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CAmtEdit();

protected:
	// Generated message map functions
	//{{AFX_MSG(CAmtEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CJEDialog dialog 
static    const int nControlCount = 5;
static    UINT idAcctControl[nControlCount] = {IDC_EDIT1_ACCT0, IDC_EDIT1_ACCT1, IDC_EDIT1_ACCT2, IDC_EDIT1_ACCT3, IDC_EDIT1_ACCT4};
static    UINT idAmtControl[nControlCount] = {IDC_EDIT3_AMT0, IDC_EDIT3_AMT1, IDC_EDIT3_AMT2, IDC_EDIT3_AMT3, IDC_EDIT3_AMT4};
static    UINT idDescControl[nControlCount] = {IDC_STATIC_DESC0, IDC_STATIC_DESC1, IDC_STATIC_DESC2, IDC_STATIC_DESC3, IDC_STATIC_DESC4};
static    UINT idJedescControl[nControlCount] = {IDC_EDIT2_JE_DESC0, IDC_EDIT2_JE_DESC1, IDC_EDIT2_JE_DESC2, IDC_EDIT2_JE_DESC3, IDC_EDIT2_JE_DESC4};

class CJEDialog : public CDialog
{
// Construction
public:
	CJEDialog(CWnd* pParent = NULL);	// standard constructor
    int m_LineCount;
    CRect m_rectScreenActive;
    CFont *hFont;
    virtual void OnSetFont( CFont* hFont );
    void CJEDialog::OnOK();
    void CJEDialog::OnCancel(); 
    int  CJEDialog::nDeciDigitCount( CString sAmt );  
    int m_nDeciDigitCount, m_nAcctLen;
    CString m_OldItemValue;
    CDDEdit m_ddEdit;
    CAmtEdit m_AmtEdit[nControlCount]; 
    BOOL m_bActive, m_bCancelPressed;
    
    CJournalEntry* m_pJE;
    
    CCHDialog	m_chDlg;
    
    CString m_acct[nControlCount], m_amt[nControlCount], m_desc[nControlCount];
    CString m_jedesc[nControlCount];
    
// Dialog Data
	//{{AFX_DATA(CJEDialog)
	enum { IDD = IDD_JE_DIALOG };
	CString	m_dd;
	CString	m_mm;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CJEDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit3DD();
	afx_msg void OnChangeEdit1Acct();
	afx_msg void OnChangeEdit1Acct2();
	afx_msg void OnChangeEdit1Acct3();
	afx_msg void OnSetfocusEdit1Acct();
	afx_msg void OnKillfocusEdit1Acct();
	afx_msg void OnChangeEdit3Amt();
	afx_msg void OnSetfocusEdit3Amt();
	afx_msg void OnKillfocusEdit3Amt();
	afx_msg void OnSetfocusEdit3Dd();
	afx_msg void OnKillfocusEdit3Dd();
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnSetfocusEdit2JeDesc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
