// OcxFileCtl.cpp : Implementation of the COcxFileCtrl ActiveX Control class.

#include "stdafx.h"
#include "OcxFile.h"
#include "OcxFileCtl.h"
#include "OcxFilePpg.h"
#include "Msg.h"
#include "windows.h"
#include "Winuser.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

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
		buff[i/2] = (unsigned char)(0xFF & strtol(slice, NULL, 16));
	}
	return i/2;
}

// 递归创建文件夹
BOOL CreateDeepDirectory(LPCTSTR lpPathName,        //directory name
LPSECURITY_ATTRIBUTES lpSecurityAttributes  // SD
)
{
	if(PathFileExists(lpPathName))       //如果目录已存在，直接返回
	{
		return TRUE;
	}

	CString strPath = "";
	char pszSrc[MAX_PATH] = {0};
	strcpy(pszSrc, lpPathName);
	char *ptoken = strtok(pszSrc, "\\");
	while(ptoken)
	{
		strPath += ptoken;
		strPath += "\\";
		if(!PathFileExists(strPath))  
		{
			if(!CreateDirectory(strPath, lpSecurityAttributes))
			{
				DWORD dw = GetLastError(); 
				CString strErr;
				strErr.Format("CreateDirectory Failed: %d", dw);
				AfxMessageBox(strErr);
				return FALSE;
			}
		}
		ptoken = strtok(NULL, "\\");
	}
	return TRUE;
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
	CString *pret = (CString *)wParam;
	FireOptDone((*pret));
	return 0;
}

// 创建文件夹 阻塞式
// 递归方式
BSTR COcxFileCtrl::create(LPCTSTR path) 
{
	CString strResult;
	CFileFind cff;
	CRetMsg ret;
	ret.opt = "create";
	
	BOOL b = ::PathFileExists(path);
	if (b)
	{
		ret.retcode = 1;
		ret.retmsg = "path or file is exists";
	}
	else
	{
		b = CreateDeepDirectory(path,NULL);
		if (b)
		{
			ret.retcode = 0;
			ret.retmsg = "create success";
		}
		else
		{
			ret.retcode = GetLastError();
			ret.retmsg = "create fail";
		}
	}
	strResult = ret.toJson();
	return strResult.AllocSysString();
}

// 文件写入线程
UINT COcxFileCtrl::WriteThreadFunction(LPVOID pParam)
{
	CWorkInfo *wi = (CWorkInfo *)pParam;
	COcxFileCtrl *who = (COcxFileCtrl*)wi->who;
	CString file = wi->para1;
	CString data = wi->para2;
	delete wi;

	logForPrjEx("开始任务，写入文件：%s", file );

	HANDLE hFile;
	CRetMsg ret;
	ret.opt = "write hex";

	int writeLen;
	hFile = CreateFile(file, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ret.retcode = GetLastError();
		ret.retmsg = "fail";
	}
	else
	{
		// SetFilePointer(hFile, 0, NULL, FILE_END);
		char *buffer = new char[data.GetLength()]; 
		int len = HexString2Array(buffer,data.GetBuffer(data.GetLength()));

		DWORD r = WriteFile(hFile, buffer, len, (LPDWORD)&writeLen, NULL);
		ret.retcode = 0;
		ret.retmsg = "success";
		delete[] buffer;
	}

	// 释放文件
	CloseHandle(hFile);
	// 触发消息 返回内容
	::PostMessage( who->m_hWnd, MSG_FIRE, (unsigned int)(new CString(ret.toJson())), 0);

	return 0;
}

// 文件读取线程
UINT COcxFileCtrl::ReadThreadFunction(LPVOID pParam)
{
	CWorkInfo *wi = (CWorkInfo *)pParam;
	COcxFileCtrl *who = (COcxFileCtrl*)wi->who;
	CString objfile = wi->para1;
	delete wi;

	logForPrjEx("开始任务，读取文件：%s", objfile );
    HANDLE hFile;
	CRetMsg ret;
	ret.opt = "read hex";

    hFile = ::CreateFile(objfile, GENERIC_READ, 0, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
		ret.retcode = GetLastError();
		ret.retmsg = "fail";
    }
	else
	{	 
		// 文件内容读取
		DWORD filesize = GetFileSize(hFile, NULL);
		char *buffer = new char[filesize+1];
		DWORD readsize;
		ReadFile(hFile, buffer, filesize, &readsize, NULL);
		buffer[filesize] = 0;
		logForPrjEx("内容读取完成");

		// 字符转义
		ret.retmsg = Array2HexString( buffer,filesize);
		ret.retcode = 0;
		logForPrjEx("内容转义完成");

		delete[] buffer;
	}
    
	// 释放文件
	CloseHandle(hFile);
	// 触发消息 返回内容
	::PostMessage( who->m_hWnd, MSG_FIRE, (unsigned int)(new CString(ret.toJson())), 0);
	
	return 0;
} 

// 文件内容读取 HEX字符串 本函数即时返回
// 文件读取完成之后触发事件 OptDone 返回包含文件信息的结构
// 如果是文件夹 返回子目录的结构
BSTR COcxFileCtrl::read(LPCTSTR file) 
{
	CString strResult;
	CRetMsg ret;

	// 开启独立的工作线程
	CWorkInfo *wi = new CWorkInfo;
	wi->who = this;
	wi->para1 = file;
	CWinThread* thread = AfxBeginThread(ReadThreadFunction,wi);
	if(NULL == thread)
	{
		ret.retcode = GetLastError();
		ret.retmsg = "fail";
	}
	else
	{
		ret.retcode = 0;
		ret.retmsg = "success";
	}
	// 即时返回调用情况
	// 不包含数据
	strResult = ret.toJson();
	return strResult.AllocSysString();
}


// 文件内容写入 HEX字符串 本函数即时返回 
// 文件读取完成之后触发事件 OptDone 返回操作信息
BSTR COcxFileCtrl::write(LPCTSTR file, LPCTSTR data) 
{
CString strResult;
	CRetMsg ret;

	// 开启独立的工作线程
	CWorkInfo *wi = new CWorkInfo;
	wi->who = this;
	wi->para1 = file;
	wi->para2 = data;
	CWinThread* thread = AfxBeginThread(WriteThreadFunction,wi);
	if(NULL == thread)
	{
		ret.retcode = GetLastError();
		ret.retmsg = "fail";
	}
	else
	{
		ret.retcode = 0;
		ret.retmsg = "success";
	}
	// 即时返回调用情况
	// 不包含数据
	strResult = ret.toJson();
	return strResult.AllocSysString();
}

