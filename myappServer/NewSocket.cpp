
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

	m_nLength = Receive(m_szBuffer, sizeof(m_szBuffer), 0); //��������
	m_szBuffer[m_nLength] = '\0';
	//printf("2\n");
	//AfxMessageBox(_T("���������ճɹ�!"));

	strcpy_s(m_p->m_szBuffer, m_szBuffer);//�������������ݴ�������һ��socket
	m_p->AsyncSelect(FD_WRITE);//��������һ��socket��������


	//������Ϣ��Ϳ�ʼ���ͻ��˷���ͬ����Ϣ
	//AsyncSelect(FD_WRITE); //����OnSend����
	//printf("%s\n", m_szBuffer);

	memset(m_szBuffer, 0, sizeof(m_szBuffer));
	//���������������ݣ�
	AsyncSelect(FD_READ);


	CAsyncSocket::OnReceive(nErrorCode);
}


void CNewSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//char m_sendBuf[4096];	//��Ϣ������

	//strcpy_s(m_sendBuf, "server send:");
	//strcat_s(m_sendBuf, m_szBuffer);
	Send(m_szBuffer, strlen(m_szBuffer));

	//AfxMessageBox(_T("���������ͳɹ�!"));
	
	memset(m_szBuffer, 0, sizeof(m_szBuffer));
	//����OnReceive����
	AsyncSelect(FD_READ);
	CAsyncSocket::OnSend(nErrorCode);
}

