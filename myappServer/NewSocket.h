
#pragma once
#include "stdafx.h"
#include "afxsock.h"
//����ר��������ͻ��˽���socketͨ��
class CNewSocket :
	public CAsyncSocket
{
public:
	CNewSocket(void);
	~CNewSocket(void);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	// ��Ϣ����
	UINT m_nLength;
	//��Ϣ������
	char m_szBuffer[4096];

public:
	CNewSocket *m_p;
};