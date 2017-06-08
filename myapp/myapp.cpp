
// myapp.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "myapp.h"
//#include "myappDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//����̨�����ͷ�ļ�
#include <io.h>
#include <fcntl.h>


// CmyApp

BEGIN_MESSAGE_MAP(CmyApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CmyApp ����

CmyApp::CmyApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��


}



// Ψһ��һ�� CmyApp ����

CmyApp theApp;


// CmyApp ��ʼ��

BOOL CmyApp::InitInstance()
{
	//InitConsole();
	//�����ӷ�������
	//int k = theApp.client.Connect(8888, "127.0.0.1");
	//if (k == 0) printf("���ӳɹ���");
	//else printf("����ʧ��");

	//����socket
	if (m_socket.m_hSocket == INVALID_SOCKET)
	{
		BOOL bFlag = m_socket.Create(0, SOCK_STREAM, FD_CONNECT); //�����׽���  
		if (!bFlag)
		{
			AfxMessageBox(_T("Socket����ʧ��!"));
			m_socket.Close();
			PostQuitMessage(0);//�˳�
			return false;
		}
	}
	//���ӷ�����  119.29.240.155
	m_socket.Connect(_T("127.0.0.1"), 8888);//�������ӳɹ�ʧ�ܶ��᷵��0�������ȵ�OnConnect��������֪���ǲ��ǳɹ���
	//m_socket.Connect(_T("119.29.240.155"), 8888);

	//���ճ�ʼ���ݣ��ж��Ƿ��ǵڶ����ͻ�������
	//theApp.client.receive(chess.buf);



	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CmyappDlg dlg;
	m_pMainWnd = &dlg;
	p_Dlg = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
		
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

