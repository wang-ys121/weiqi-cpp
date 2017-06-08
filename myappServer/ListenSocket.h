#pragma once
#include "stdafx.h"
#include "afxsock.h"
#include "NewSocket.h"
class CListenSocket :
	public CAsyncSocket
{
public:
	CListenSocket(void);
	~CListenSocket(void);



	//CNewSocket *m_pSocket; //指向一个连接的socket对象

	int p = 0;//标志哪一个socket连接
	CNewSocket m_Socket[2]; //两个socket连接
	
	virtual void OnAccept(int nErrorCode);
};

