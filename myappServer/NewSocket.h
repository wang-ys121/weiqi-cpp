
#pragma once
#include "stdafx.h"
#include "afxsock.h"
//此类专门用来与客户端进行socket通信
class CNewSocket :
	public CAsyncSocket
{
public:
	CNewSocket(void);
	~CNewSocket(void);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	// 消息长度
	UINT m_nLength;
	//消息缓冲区
	char m_szBuffer[4096];

public:
	CNewSocket *m_p;
};