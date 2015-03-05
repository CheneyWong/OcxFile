#if !defined(AFX_OCXFILECTL_H__F97B54A9_4A2A_4445_914A_A31B28938948__INCLUDED_)
#define AFX_OCXFILECTL_H__F97B54A9_4A2A_4445_914A_A31B28938948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MSG_FIRE (WM_USER+100)
// OcxFileCtl.h : Declaration of the COcxFileCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl : See OcxFileCtl.cpp for implementation.

class COcxFileCtrl : public COleControl
{
	DECLARE_DYNCREATE(COcxFileCtrl)

// Constructor
public:
	COcxFileCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COcxFileCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~COcxFileCtrl();

	DECLARE_OLECREATE_EX(COcxFileCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(COcxFileCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(COcxFileCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(COcxFileCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(COcxFileCtrl)
	//}}AFX_MSG
	afx_msg LRESULT OnMsgFire(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(COcxFileCtrl)
	afx_msg BSTR create(LPCTSTR path);
	afx_msg BSTR read(LPCTSTR file);
	afx_msg BSTR write(LPCTSTR file, LPCTSTR data);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();
	
	

// Event maps
	//{{AFX_EVENT(COcxFileCtrl)
	void FireOptDone(LPCTSTR msg)
		{FireEvent(eventidOptdone,EVENT_PARAM(VTS_BSTR), msg);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Ïß³Ìº¯Êý
	static UINT ReadThreadFunction(LPVOID pParam);
	static UINT WriteThreadFunction(LPVOID pParam);

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(COcxFileCtrl)
	dispidCreate = 1L,
	dispidRead = 2L,
	dispidWrite = 3L,
	eventidOptdone = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXFILECTL_H__F97B54A9_4A2A_4445_914A_A31B28938948__INCLUDED)
