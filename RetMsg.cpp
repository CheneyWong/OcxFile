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
