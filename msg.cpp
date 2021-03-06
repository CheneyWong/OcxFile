#include "StdAfx.h"
#include "Msg.h"


CRetMsg::CRetMsg(void)
	: retcode(0)
{
	retmsg = "";
	opt = "";
}


CRetMsg::~CRetMsg(void)
{
}


// 获取 json 格式的返回
CString CRetMsg::toJson(void)
{
	CString  ret;
	ret.Format(_T("{\"opt\":\"%s\",\"retcode\":\"%d\",\"retmsg\":\"%s\"}"),
		opt, retcode, retmsg);
	return ret;
}

//////////////////////////////////////////////////////////////////////
// CFileInfo Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileInfo::CFileInfo()
{
	type = "";
	data = "";
	info = "";
}

CFileInfo::~CFileInfo()
{

}

// 获取 json 格式
CString CFileInfo::toJson(void)
{
	CString  ret;
	ret.Format(_T("{\"type\":\"%s\",\"data\":\"%s\",\"info\":\"%s\"}"),
		type, data, info);
	return ret;
}/////////////////////////////////////////////////////////////////////////////
// CWorkInfo

CWorkInfo::CWorkInfo()
{
}

CWorkInfo::~CWorkInfo()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkInfo message handlers
