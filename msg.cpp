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


// ��ȡ json ��ʽ�ķ���
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

// ��ȡ json ��ʽ
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
