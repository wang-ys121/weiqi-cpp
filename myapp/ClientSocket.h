
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
	// �Ƿ�����
	bool m_bConnected;
	// ��Ϣ����
	UINT m_nLength;
	//��Ϣ������
	char m_szBuffer[5];
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

public:
	//CDialogEx *p_Dlg;
};


