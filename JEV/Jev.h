// jev.h : main header file for the JEV application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "env.h"       // main symbols 
#include "chart.h"
#include "jevdoc.h"


/////////////////////////////////////////////////////////////////////////////
// CJevApp:
// See jev.cpp for the implementation of this class
//

class CJevApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pTemplate1;
	CJevApp();
	CEnv m_env;
	CChartList m_chart;
	BOOL m_bRawView;
	CJevDoc* m_pActiveJevDoc;
	
	BOOL bGetRawView() const;
	void SetRawView( BOOL bRawView );

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	//{{AFX_MSG(CJevApp)
	afx_msg void OnAppAbout();
	afx_msg void OnTestRawview();
	afx_msg void OnUpdateTestRawview(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
}; 

extern CJevApp NEAR theApp; 
extern UINT nFindMsg; 


/////////////////////////////////////////////////////////////////////////////
// VB-Event extern declarations

//{{AFX_VBX_REGISTER()
//}}AFX_VBX_REGISTER

/////////////////////////////////////////////////////////////////////////////
