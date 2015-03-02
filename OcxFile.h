#if !defined(AFX_OCXFILE_H__91E0DC66_A387_42EF_985F_CD18A133D1B9__INCLUDED_)
#define AFX_OCXFILE_H__91E0DC66_A387_42EF_985F_CD18A133D1B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OcxFile.h : main header file for OCXFILE.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COcxFileApp : See OcxFile.cpp for implementation.

class COcxFileApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXFILE_H__91E0DC66_A387_42EF_985F_CD18A133D1B9__INCLUDED)
