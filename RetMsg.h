#pragma once

// 消息格式
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

// 文件信息格式
class CFileInfo  
{
public:
	CFileInfo();
	virtual ~CFileInfo();
	// 获取 json 格式的返回
	CString toJson(void);
	CString type;
	CString data;
	CString info;

};


