// OcxFileCtl.cpp : Implementation of the COcxFileCtrl ActiveX Control class.

#include "stdafx.h"
#include "OcxFile.h"
#include "OcxFileCtl.h"
#include "OcxFilePpg.h"
#include "RetMsg.h"
#include "windows.h"
#include "Winuser.h"

#include "string.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(COcxFileCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(COcxFileCtrl, COleControl)
	//{{AFX_MSG_MAP(COcxFileCtrl)
	ON_WM_HELPINFO()
	ON_WM_QUERYENDSESSION()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(MSG_FIRE,OnMsgFire)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(COcxFileCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(COcxFileCtrl)
	DISP_FUNCTION(COcxFileCtrl, "create", create, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(COcxFileCtrl, "read", read, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(COcxFileCtrl, "write", write, VT_BSTR, VTS_BSTR VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(COcxFileCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(COcxFileCtrl, COleControl)
	//{{AFX_EVENT_MAP(COcxFileCtrl)
	EVENT_CUSTOM("optdone", FireOptDone, VTS_BSTR)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(COcxFileCtrl, 1)
	PROPPAGEID(COcxFilePropPage::guid)
END_PROPPAGEIDS(COcxFileCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(COcxFileCtrl, "OCXFILE.OcxFileCtrl.1",
	0x3f08c971, 0x449f, 0x4588, 0x85, 0x3f, 0x9e, 0x25, 0xdd, 0x73, 0x87, 0x9b)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(COcxFileCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DOcxFile =
		{ 0xb29222ea, 0x7db7, 0x4f0a, { 0xaf, 0x18, 0x79, 0x3f, 0xcc, 0xf, 0x23, 0x9 } };
const IID BASED_CODE IID_DOcxFileEvents =
		{ 0xf0b787d0, 0x2d92, 0x4fe1, { 0x9d, 0xf3, 0xce, 0x7d, 0xd3, 0xd, 0xf1, 0x8f } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwOcxFileOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(COcxFileCtrl, IDS_OCXFILE, _dwOcxFileOleMisc)



class CWinThread * gthid = NULL;

// 通用函数

// 调试
void logForPrj ( char *desc )
{
	HANDLE hFile;
	int writeLen, len;
	SYSTEMTIME st;
	char buf[256];

	GetLocalTime ( &st );
	sprintf ( buf, "c:\\LOG\\%04d%02d%02d.log", 
			  st.wYear, st.wMonth, st.wDay );
	hFile = CreateFile(buf, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	
	SetFilePointer(hFile, 0, NULL, FILE_END);

	sprintf ( buf, "[%04d-%02d-%02d %02d:%02d:%02d] ", 
			  st.wYear, st.wMonth, st.wDay, 
			  st.wHour, st.wMinute, st.wSecond );
	DWORD ret = WriteFile(hFile, buf, strlen ( buf ), (LPDWORD)&writeLen, NULL);

	len = strlen ( desc );
	WriteFile(hFile, desc, len, (LPDWORD)&writeLen, NULL);
	WriteFile(hFile, "\r\n", 2, (LPDWORD)&writeLen, NULL);
	CloseHandle(hFile);
}

void logForPrjEx ( char *format, ... )
{
	char buf[512];
	va_list args;

	va_start ( args, format );
	vsprintf ( buf, format, args );
	va_end ( args );

	logForPrj ( buf );
}

// 将数据转成十六进制字符串
// buff - 数据
// len - 数据个数
// 字符串
CString Array2HexString (char * buff, DWORD len )
{
	DWORD strlen = len*2;
	char str[3];
	CString ret="";
	for(DWORD i=0; i< len; i++)
	{
		sprintf(str,"%02X",buff[i]);
		ret += str;
	}
	return ret;
}

// 将十六进制字符串转成数据
// 输出的数据
// 输入的字符串
// 成功转换的个数
int HexString2Array(char *buff,char *str)
{
	int i;
	int len = strlen(str);
	char slice[3];
	if( len % 2 )
	{
		return -1;
	}
	for( i=0 ; i<len ; i+=2 )
	{
		memcpy(slice,str+i,2);
		slice[2] = 0;
		buff[i/2] = 0xFF & strtol(slice, NULL, 16);
	}
	return i/2;
}



/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl::COcxFileCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for COcxFileCtrl

BOOL COcxFileCtrl::COcxFileCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_OCXFILE,
			IDB_OCXFILE,
			afxRegApartmentThreading,
			_dwOcxFileOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl::COcxFileCtrl - Constructor

COcxFileCtrl::COcxFileCtrl()
{
	InitializeIIDs(&IID_DOcxFile, &IID_DOcxFileEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl::~COcxFileCtrl - Destructor

COcxFileCtrl::~COcxFileCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl::OnDraw - Drawing function

void COcxFileCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl::DoPropExchange - Persistence support

void COcxFileCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl::OnResetState - Reset control to default state

void COcxFileCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl::AboutBox - Display an "About" box to the user

void COcxFileCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_OCXFILE);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// COcxFileCtrl message handlers
LRESULT COcxFileCtrl::OnMsgFire(WPARAM wParam, LPARAM lParam)
{
	logForPrjEx("%d,fire !",__LINE__);
	FireOptDone("287");
	return 0;
}

// 创建文件
BSTR COcxFileCtrl::create(LPCTSTR path) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	//FireOptDone("296");

	//this->FireOptDone("233");
	gthid = AfxGetThread();
	int i = gthid->PostThreadMessage(MSG_FIRE, 0, 0);

	//logForPrjEx("postmsg:%d",i);
	//logForPrjEx("gthid:%d",(int)gthid);

	// 测试线程和事件触发
	CWinThread* thread = AfxBeginThread(WorkThreadFunction,this);
	logForPrjEx("CWinThread:%d",(int)thread);
	//thread = AfxBeginThread(WorkThreadFunction,this,THREAD_PRIORITY_NORMAL,0,0,NULL); 
	


	HANDLE hFile;
	CRetMsg ret;
	logForPrjEx("path:%s", path);
	hFile = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ret.retcode = GetLastError();
		ret.retmsg = "fail";
	}
	CloseHandle(hFile);
	ret.retcode = 0;
	ret.retmsg = "success";
	strResult = ret.toJson();
	return strResult.AllocSysString();
}

// 文件内容读取
BSTR COcxFileCtrl::read(LPCTSTR file) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
    HANDLE pfile;
	CRetMsg ret;
	logForPrjEx("read file:%s", file);
    pfile = ::CreateFile(file, GENERIC_READ, 0, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if(pfile == INVALID_HANDLE_VALUE)
    {
		ret.retcode = GetLastError();
		ret.retmsg = "fail";
    }
	else
	{	 
		// 文件内容读取
		DWORD filesize = GetFileSize(pfile, NULL);
		char *buffer = new char[filesize+1];
		DWORD readsize;
		ReadFile(pfile, buffer, filesize, &readsize, NULL);
		buffer[filesize] = 0;
		logForPrjEx("内容读取完成");

		// 字符转义
		ret.retmsg = Array2HexString (buffer,filesize);
		ret.retcode = 0;
		logForPrjEx("内容转义完成");

		delete[] buffer;
	}
    
	// 释放资源
	CloseHandle(pfile);

	strResult = ret.toJson();
	return strResult.AllocSysString();
}

UINT COcxFileCtrl::WorkThreadFunction(LPVOID pParam)
{

	Sleep(1000);
	 ::PostMessage(((COcxFileCtrl*)pParam)->m_hWnd,MSG_FIRE,0,0);
	// 并发 log 有问题
	//SendMessage(MSG_FIRE, 0, 0);
	logForPrjEx("%d:%d",__LINE__,(int)gthid);
	logForPrjEx("%d:%d",__LINE__,(int)AfxGetThread());
	return 0;
} 


BSTR COcxFileCtrl::write(LPCTSTR file, LPCTSTR data) 
{
	CString strResult;
	HANDLE hFile;
	CRetMsg ret;
	int writeLen;
	

	hFile = CreateFile(file, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ret.retcode = GetLastError();
		ret.retmsg = "fail";
	}
	else
	{
		SetFilePointer(hFile, 0, NULL, FILE_END);
		char *buffer = new char[_tcslen(data)+ 1]; 
		int len = HexString2Array(buffer,(LPSTR)data);

		DWORD r = WriteFile(hFile, buffer, len, (LPDWORD)&writeLen, NULL);
		ret.retcode = 0;
		ret.retmsg = "success";
		delete[] buffer;
	}


	CloseHandle(hFile);
	strResult = ret.toJson();
	return strResult.AllocSysString();
}

BOOL COcxFileCtrl::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	logForPrjEx("help");
	return COleControl::OnHelpInfo(pHelpInfo);
}

BOOL COcxFileCtrl::OnQueryEndSession() 
{
	if (!COleControl::OnQueryEndSession())
		return FALSE;
	
	// TODO: Add your specialized query end session code here
	logForPrjEx("help");
	
	return TRUE;
}

void COcxFileCtrl::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	COleControl::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}
