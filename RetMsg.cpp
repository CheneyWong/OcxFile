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


// 获取 json 格式的返回
CString CRetMsg::toJson(void)
{
	CString  ret;
	ret.Format(_T("{\"retcode\":%d,\"retmsg\":%s}"), retcode, retmsg);
	return ret;
}
