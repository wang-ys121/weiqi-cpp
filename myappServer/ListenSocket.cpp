
#include "StdAfx.h"
#include "ListenSocket.h"


CListenSocket::CListenSocket(void)
{


	AfxSocketInit();//casyncsocketʹ��ǰ��Ҫ���������
}


CListenSocket::~CListenSocket(void)
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//CNewSocket *pSocket = new CNewSocket();
	int q = p % 2;
	if (Accept(m_Socket[q]))
	{
		m_Socket[q].m_p = &m_Socket[(p + 1) % 2];//������socket�������ָ���Ա㽻������
		
		//AfxMessageBox(_T("���ӳɹ�һ��!"));
		m_Socket[q].AsyncSelect(FD_READ); //����ͨ��socket��Read����������
		p++;
	}
	else
	{
		AfxMessageBox(_T("����Ŀͻ�������ʧ��!"));
	}
	CAsyncSocket::OnAccept(nErrorCode);
}

