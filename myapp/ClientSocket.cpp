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
	//连接成功
	if (nErrorCode == 0)
	{
		m_bConnected = TRUE;

		AfxMessageBox(_T("连接服务器成功!"));

		//激活一个网络读取事件,准备接收
		AsyncSelect(FD_READ);

	}
	else
	{
		AfxMessageBox(_T("连接服务器失败!"));
	}
	CAsyncSocket::OnConnect(nErrorCode);
}


void ClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//获取socket数据
	m_nLength = Receive(m_szBuffer, sizeof(m_szBuffer));

	//AfxMessageBox(_T("客户端接收成功!"));
	//printf("%s\n", m_szBuffer);
	m_szBuffer[m_nLength] = '\0';
	
	//获取主窗口  
	//CmyappDlg *pAppDlg = (CmyappDlg*)AfxGetMainWnd;
	

	//得到窗口画柄
	CDC *pDC;
	pDC = theApp.p_Dlg->GetDC();
	
	strcpy_s(theApp.chess.buf, m_szBuffer);//拷贝数据到棋盘
	theApp.chess.update(pDC);//更新棋盘及其数据
	

	theApp.p_Dlg->ReleaseDC(pDC); //及时释放pDC，防止内存泄漏


	theApp.p_Dlg->kk = 1;//恢复下棋控制，此时可以下棋

	memset(m_szBuffer, 0, sizeof(m_szBuffer));

	AsyncSelect(FD_READ);//继续触发接收数据
	CAsyncSocket::OnReceive(nErrorCode);
}


void ClientSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//发送数据
	Send(m_szBuffer, m_nLength, 0);
	m_nLength = 0;
	//AfxMessageBox(_T("客户端发送成功!"));
	memset(m_szBuffer, 0, sizeof(m_szBuffer));

	//继续提请一个读的网络事件,接收socket消息
	AsyncSelect(FD_READ);
	CAsyncSocket::OnSend(nErrorCode);
}
