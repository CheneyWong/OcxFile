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
	CString opt;
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

// �����߳���Ϣ����
class CWorkInfo
{
// Construction
public:
	CWorkInfo();
	virtual ~CWorkInfo();
	void *who;
	CString para1;
	CString para2;
};

/////////////////////////////////////////////////////////////////////////////
