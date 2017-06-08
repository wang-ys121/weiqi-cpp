#include "stdafx.h"
#include "ClientSocket.h"
#include "myapp.h"
//#include <cstring>
//#include <string>
//#include <string.h>
//#include <iostream>
//using namespace std;

ClientSocket::ClientSocket(void)
: m_bConnected(false)
, m_nLength(0)
{
	memset(m_szBuffer, 0, sizeof(m_szBuffer));
	AfxSocketInit();
}


ClientSocket::~ClientSocket(void)
{
	if (m_hSocket != INVALID_SOCKET)
	{
		Close();
	}
}


void ClientSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//���ӳɹ�
	if (nErrorCode == 0)
	{
		m_bConnected = TRUE;

		AfxMessageBox(_T("���ӷ������ɹ�!"));

		//����һ�������ȡ�¼�,׼������
		AsyncSelect(FD_READ);

	}
	else
	{
		AfxMessageBox(_T("���ӷ�����ʧ��!"));
	}
	CAsyncSocket::OnConnect(nErrorCode);
}


void ClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//��ȡsocket����
	m_nLength = Receive(m_szBuffer, sizeof(m_szBuffer));

	//AfxMessageBox(_T("�ͻ��˽��ճɹ�!"));
	//printf("%s\n", m_szBuffer);
	m_szBuffer[m_nLength] = '\0';
	
	//��ȡ������  
	//CmyappDlg *pAppDlg = (CmyappDlg*)AfxGetMainWnd;
	

	//�õ����ڻ���
	CDC *pDC;
	pDC = theApp.p_Dlg->GetDC();
	
	strcpy_s(theApp.chess.buf, m_szBuffer);//�������ݵ�����
	theApp.chess.update(pDC);//�������̼�������
	

	theApp.p_Dlg->ReleaseDC(pDC); //��ʱ�ͷ�pDC����ֹ�ڴ�й©


	theApp.p_Dlg->kk = 1;//�ָ�������ƣ���ʱ��������

	memset(m_szBuffer, 0, sizeof(m_szBuffer));

	AsyncSelect(FD_READ);//����������������
	CAsyncSocket::OnReceive(nErrorCode);
}


void ClientSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//��������
	Send(m_szBuffer, m_nLength, 0);
	m_nLength = 0;
	//AfxMessageBox(_T("�ͻ��˷��ͳɹ�!"));
	memset(m_szBuffer, 0, sizeof(m_szBuffer));

	//��������һ�����������¼�,����socket��Ϣ
	AsyncSelect(FD_READ);
	CAsyncSocket::OnSend(nErrorCode);
}
