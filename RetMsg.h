#pragma once
class CRetMsg
{
public:
	CRetMsg(void);
	~CRetMsg(void);
	// 获取 json 格式的返回
	CString toJson(void);
	DWORD retcode;
	CString retmsg;
};

