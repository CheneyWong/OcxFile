#pragma once

// ��Ϣ��ʽ
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

// �ļ���Ϣ��ʽ
class CFileInfo  
{
public:
	CFileInfo();
	virtual ~CFileInfo();
	// ��ȡ json ��ʽ�ķ���
	CString toJson(void);
	CString type;
	CString data;
	CString info;

};


