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



	//CNewSocket *m_pSocket; //ָ��һ�����ӵ�socket����

	int p = 0;//��־��һ��socket����
	CNewSocket m_Socket[2]; //����socket����
	
	virtual void OnAccept(int nErrorCode);
};

