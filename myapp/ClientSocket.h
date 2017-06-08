
#pragma once
//#include "stdafx.h"
#include "afxsock.h"
//#include "myappDlg.h"
//#include "myapp.h"

class ClientSocket :
	public CAsyncSocket
{
public:
	ClientSocket(void);
	~ClientSocket(void);
	// 是否连接
	bool m_bConnected;
	// 消息长度
	UINT m_nLength;
	//消息缓冲区
	char m_szBuffer[5];
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

public:
	//CDialogEx *p_Dlg;
};


