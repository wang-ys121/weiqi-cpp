
#include "StdAfx.h"
#include "ListenSocket.h"


CListenSocket::CListenSocket(void)
{


	AfxSocketInit();//casyncsocket使用前需要先运行这个
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
		m_Socket[q].m_p = &m_Socket[(p + 1) % 2];//将两个socket互相关联指向；以便交互数据
		
		//AfxMessageBox(_T("连接成功一个!"));
		m_Socket[q].AsyncSelect(FD_READ); //触发通信socket的Read函数读数据
		p++;
	}
	else
	{
		AfxMessageBox(_T("请求的客户端连接失败!"));
	}
	CAsyncSocket::OnAccept(nErrorCode);
}

