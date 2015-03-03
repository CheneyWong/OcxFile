#include "StdAfx.h"
#include "RetMsg.h"


CRetMsg::CRetMsg(void)
	: retcode(0)
{
	retmsg = "";
}


CRetMsg::~CRetMsg(void)
{
}


// ��ȡ json ��ʽ�ķ���
CString CRetMsg::toJson(void)
{
	CString  ret;
	ret.Format(_T("{\"retcode\":%d,\"retmsg\":%s}"), retcode, retmsg);
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
	ret.Format(_T("{\"type\":%s,\"data\":%s,\"info\":%s}"), type, data, info);
	return ret;
}