#if !defined(AFX_OCXFILEPPG_H__30E60D4E_ADD2_4096_A04A_417516E1DDE1__INCLUDED_)
#define AFX_OCXFILEPPG_H__30E60D4E_ADD2_4096_A04A_417516E1DDE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OcxFilePpg.h : Declaration of the COcxFilePropPage property page class.

////////////////////////////////////////////////////////////////////////////
// COcxFilePropPage : See OcxFilePpg.cpp.cpp for implementation.

class COcxFilePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(COcxFilePropPage)
	DECLARE_OLECREATE_EX(COcxFilePropPage)

// Constructor
public:
	COcxFilePropPage();

// Dialog Data
	//{{AFX_DATA(COcxFilePropPage)
	enum { IDD = IDD_PROPPAGE_OCXFILE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(COcxFilePropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXFILEPPG_H__30E60D4E_ADD2_4096_A04A_417516E1DDE1__INCLUDED)
