#ifndef _ENV_H_
#define _ENV_H_

//#ifdef _DOS
//#include <afx.h>
//#else
//#include <afxwin.h>
//#endif


////////////////////////////////////////////////////////////////////////
//  CEnv - Global Class/Object that hold program's environment
//	   variables, directory setting, and program termination logic
//
//


class CEnv : public CObject
{
    DECLARE_DYNAMIC( CEnv );
public:
// Construction
    CEnv();
    ~CEnv();
    

// Attributes
    static void Terminate();
    void Init();

// Implementation
public:
	CString m_cwdstr, m_path, m_froot, m_year;

// Debug
#ifdef _DEBUG
public:
    virtual void Dump( CDumpContext& dc ) const;
    virtual void AssertValid() const;

#endif

};

//extern "C" void SigTerm( int ign );

#endif // _ENV_H_
