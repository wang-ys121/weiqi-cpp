
#include "stdafx.h"
#include "NewSocket.h"


CNewSocket::CNewSocket(void)
: m_nLength(0)
{
	memset(m_szBuffer, 0, sizeof(m_szBuffer));

}


CNewSocket::~CNewSocket(void)
{
	if (m_hSocket != INVALID_SOCKET)
	{
		Close();
	}
}


void CNewSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	//printf("1\n");

	m_nLength = Receive(m_szBuffer, sizeof(m_szBuffer), 0); //接收数据
	m_szBuffer[m_nLength] = '\0';
	//printf("2\n");
	//AfxMessageBox(_T("服务器接收成功!"));

	strcpy_s(m_p->m_szBuffer, m_szBuffer);//将本身所得数据传给另外一个socket
	m_p->AsyncSelect(FD_WRITE);//触发另外一个socket传送数据


	//接收消息后就开始给客户端发相同的消息
	//AsyncSelect(FD_WRITE); //触发OnSend函数
	//printf("%s\n", m_szBuffer);

	memset(m_szBuffer, 0, sizeof(m_szBuffer));
	//继续触发接收数据；
	AsyncSelect(FD_READ);


	CAsyncSocket::OnReceive(nErrorCode);
}


void CNewSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//char m_sendBuf[4096];	//消息缓冲区

	//strcpy_s(m_sendBuf, "server send:");
	//strcat_s(m_sendBuf, m_szBuffer);
	Send(m_szBuffer, strlen(m_szBuffer));

	//AfxMessageBox(_T("服务器发送成功!"));
	
	memset(m_szBuffer, 0, sizeof(m_szBuffer));
	//触发OnReceive函数
	AsyncSelect(FD_READ);
	CAsyncSocket::OnSend(nErrorCode);
}

