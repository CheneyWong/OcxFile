#pragma once
class CRetMsg
{
public:
	CRetMsg(void);
	~CRetMsg(void);
	// ��ȡ json ��ʽ�ķ���
	CString toJson(void);
	DWORD retcode;
	CString retmsg;
};

